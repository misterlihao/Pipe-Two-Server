#ifndef __UTIL_H__
#define __UTIL_H__

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <cstdio>

#define PRINT_LOG(...) fprintf(stdout, __VA_ARGS__);fflush(stdout);

enum UTIL_RESULT {SUCCESS, FAIL};

UTIL_RESULT connect_socket(char const* ip, int port, SOCKET &sock) {
    using namespace std;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr = {};
    addr.sin_family       = AF_INET;
    addr.sin_addr.s_addr  = inet_addr(ip);
    addr.sin_port         = htons(port);

    int iResult = connect(sock, (SOCKADDR*)&addr, sizeof(addr));
    if (iResult == SOCKET_ERROR) {
        closesocket(sock);
        return FAIL;
    }


    return SUCCESS;
}

UTIL_RESULT tryInitSocketLib() {
    WSADATA wsaData;

    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult == 0)
        return SUCCESS;
    else
        return FAIL;
}
#endif
