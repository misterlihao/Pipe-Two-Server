#include <string>
#include <cstdlib>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>

using namespace std;

int get_listen_socket(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(port);  
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  

    if (bind(sock,(struct sockaddr *)&addr,sizeof(addr)) < 0)
        exit(1);
    listen(sock, SOMAXCONN);
    return sock;
}
void fd_copy(int srcfd, int dstfd) {
    static unsigned char buf[1024];
    int cnt = read(srcfd, buf, sizeof(buf));

    if (cnt <= 0)
        exit(0);
    while (cnt) {
        int cnt2 = write(dstfd, buf, cnt);
        cnt -= cnt2;
    }
}
int main(int argc, char **argv) {
    int listen_sock1 = get_listen_socket(atoi(argv[1]));
    int listen_sock2 = get_listen_socket(atoi(argv[2]));
    int sock1 = accept(listen_sock1, NULL, NULL);
    int sock2 = accept(listen_sock2, NULL, NULL);
    write(sock1, "A", 1); // inform first client

    while (true) {
        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(sock1, &read_set);
        FD_SET(sock2, &read_set);

        select(sock2+1, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(sock1, &read_set))
            fd_copy(sock1, sock2);
        if (FD_ISSET(sock2, &read_set))
            fd_copy(sock2, sock1);
    }
    close(sock1);
    close(sock2);
    close(listen_sock1);
    close(listen_sock2);
    return 0;
}
