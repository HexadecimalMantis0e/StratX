#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include "StratWad.hpp"
#include "Util.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        return 0;
    }

    std::ifstream fs;

    fs.open(argv[1], std::ios::in | std::ios::binary);

    if (!fs) {
        std::cout << "Could not open file!" << std::endl;
        return 1;
    }

    StratWad sw;

    if (sw.readStratWad(fs)) {
        printInfo(sw);
        dumpSegments(sw, false);
        dumpSegments(sw, true);
        std::cout << "Done!" << std::endl;
    }
    else {
        usage();
    }
    return 0;
}
