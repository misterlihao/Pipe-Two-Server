#ifndef __PROGRAMMODE_H__
#define __PROGRAMMODE_H__
#include <cstdio>
#include <string>

#include <winsock2.h>

struct ProgramMode {
    virtual void run() = 0;
    virtual ~ProgramMode(){}
};

struct UsageMode : public ProgramMode {
    virtual void run(){
        std::printf ("command service_port ip port\n");
    }
};

struct ExecuteMode : public ProgramMode {
    ExecuteMode(int service_port, std::string ip, int port) :
        service_port_(service_port), redir_port_(port),
        local_sock_(INVALID_SOCKET), redir_sock_(INVALID_SOCKET),
        redir_ip_(ip)
        {}
    virtual void run();
private:
    int          service_port_, redir_port_;
    SOCKET       local_sock_, redir_sock_;
    std::string    redir_ip_;

    void connectBothServer();
    void keepPiping();
};
#endif

