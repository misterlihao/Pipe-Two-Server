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
        std::printf ("command ip1 port1 ip2 port2\n");
    }
};

struct ExecuteMode : public ProgramMode {
    ExecuteMode(std::string ip1, int port1, std::string ip2, int port2) :
        port1_(port1), port2_(port2),
        sock1_(INVALID_SOCKET), sock2_(INVALID_SOCKET),
        ip1_(ip1), ip2_(ip2)
        {}
    virtual void run();
private:
    int          port1_, port2_;
    SOCKET       sock1_, sock2_;
    std::string    ip1_,   ip2_;

    void connectBothServer();
    void keepPiping();
};
#endif

