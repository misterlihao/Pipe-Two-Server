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

        closesocket(sock1_);
        closesocket(sock2_);
    }

    WSACleanup();
}

void ExecuteMode::keepPiping() {
    fd_set read_sock_set;
    static char buffer[1024];

    while (true) {
        FD_ZERO(&read_sock_set);
        FD_SET(sock1_, &read_sock_set);
        FD_SET(sock2_, &read_sock_set);
        int const iResult = select(2, &read_sock_set, NULL, NULL, NULL);
        if (iResult == SOCKET_ERROR) {
            PRINT_LOG("select failed. GetLastError: %lu\n", GetLastError());
            return;
        }

        // TODO : recv, send error handling
        if (FD_ISSET(sock1_, &read_sock_set)) {
            int const cnt = recv(sock1_, buffer, sizeof(buffer), 0);
            if (cnt > 0) {
                send(sock2_, buffer, cnt, 0);
            }
            else {
                PRINT_LOG("%s:%d closed.\n", ip1_.c_str(), port1_);
                return;
            }
        }
        if (FD_ISSET(sock2_, &read_sock_set)) {
            int const cnt = recv(sock2_, buffer, sizeof(buffer), 0);
            if (cnt > 0)
                send(sock1_, buffer, cnt, 0);
            else {
                PRINT_LOG("%s:%d closed.\n", ip2_.c_str(), port2_);
                return;
            }
        }
    }
}
void ExecuteMode::connectBothServer() {
    if (connect_socket(ip1_.c_str(), port1_, sock1_) == FAIL)
        PRINT_LOG("connect %s : %d failed.\n", ip1_.c_str(), port1_);

    if (connect_socket(ip2_.c_str(), port2_, sock2_) == FAIL)
        PRINT_LOG("connect %s : %d failed.\n", ip2_.c_str(), port2_);
}

