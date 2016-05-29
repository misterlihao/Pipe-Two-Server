#include <cstdio>

#include "ProgramMode.h"
#include "util.h"

using namespace std;

void ExecuteMode::run() {
    if (tryInitSocketLib() == FAIL) {
        PRINT_LOG("WSAStartup failed: \n");
        return ;
    }

    while (true) {
        PRINT_LOG("connect to both server\n");
        connectBothServer();
        PRINT_LOG("keep piping between server\n");
        keepPiping();
        PRINT_LOG("connection over\n");

        closesocket(local_sock_);
        closesocket(redir_sock_);
    }

    WSACleanup();
}

void ExecuteMode::keepPiping() {
    fd_set read_sock_set;
    static char buffer[1024];

    while (true) {
        FD_ZERO(&read_sock_set);
        FD_SET(local_sock_, &read_sock_set);
        FD_SET(redir_sock_, &read_sock_set);
        int const iResult = select(2, &read_sock_set, NULL, NULL, NULL);
        if (iResult == SOCKET_ERROR) {
            PRINT_LOG("select failed. GetLastError: %lu\n", GetLastError());
            return;
        }

        // TODO : recv, send error handling
        if (FD_ISSET(local_sock_, &read_sock_set)) {
            int const cnt = recv(local_sock_, buffer, sizeof(buffer), 0);
            if (cnt > 0) {
                send(redir_sock_, buffer, cnt, 0);
            }
            else {
                PRINT_LOG("localhost:%d closed.\n", service_port_);
                return;
            }
        }
        if (FD_ISSET(redir_sock_, &read_sock_set)) {
            int const cnt = recv(redir_sock_, buffer, sizeof(buffer), 0);
            if (cnt > 0)
                send(local_sock_, buffer, cnt, 0);
            else {
                PRINT_LOG("%s:%d closed.\n", redir_ip_.c_str(), redir_port_);
                return;
            }
        }
    }
}
void ExecuteMode::connectBothServer() {
    if (connect_socket(redir_ip_.c_str(), redir_port_, redir_sock_) == FAIL) {
        PRINT_LOG("connect %s : %d failed.\n", redir_ip_.c_str(), redir_port_);
        return ;
    }

    char c;
    recv(redir_sock_, &c, 1, 0); // block until got one char, and discard it
    if (connect_socket("127.0.0.1", service_port_, local_sock_) == FAIL)
        PRINT_LOG("connect localhost : %d failed.\n", service_port_);
}

