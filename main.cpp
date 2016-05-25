#include <string>
#include <cstdlib>

#include "ProgramMode.h"

using namespace std;

ProgramMode* GetProgramMode(int argc, char **argv) {
    if (argc == 5) {
        // TODO : *minor* abort when argv are not valid
        string ip1   = argv[1];
        string ip2   = argv[3];
        int    port1 = atoi(argv[2]);
        int    port2 = atoi(argv[4]);

        return new ExecuteMode(ip1, port1, ip2, port2);
    }

    return new UsageMode();
}

int main(int argc, char **argv) {
    ProgramMode *mode = GetProgramMode(argc, argv);
    mode->run();
}

