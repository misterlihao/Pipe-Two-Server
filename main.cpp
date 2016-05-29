#include <string>
#include <cstdlib>

#include "ProgramMode.h"

using namespace std;

ProgramMode* GetProgramMode(int argc, char **argv) {
    if (argc == 4) {
        // TODO : *minor* abort when argv are not valid
        string ip2   = argv[2];
        int    port1 = atoi(argv[1]);
        int    port2 = atoi(argv[3]);

        return new ExecuteMode(port1, ip2, port2);
    }

    return new UsageMode();
}

int main(int argc, char **argv) {
    ProgramMode *mode = GetProgramMode(argc, argv);
    mode->run();
}

