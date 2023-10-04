#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include "StratWad.hpp"
#include "Util.hpp"

void usage() {
    std::cout << "StratX: Dump segments from Xbox Strat Wads" << std::endl;
    std::cout << "Usage: StratX path/to/Xbox/Strat/Wad" << std::endl;
}

void printInfo(const StratWad &sw) {
    std::cout << "Wad version: 0x" << std::hex << sw.getWadVersion() << std::endl;
    std::cout << "Description: " << sw.getDescription() << std::endl;
    std::cout << "Signature: " << sw.getSignature() << std::endl;
    std::cout << "Arguments: " << sw.getArguments() << std::endl;
    std::cout << std::endl;
}

void dumpSegments(const StratWad &sw, bool secondary) {
    std::string pre = "dump";

    if (secondary) {
        pre += "UC";
    }

    for (int i = 0; i < static_cast<int>(sw.getSegmentCount(secondary)); i++) {
        std::uint32_t segmentSize = sw.getSegmentSize(i, secondary);
        const std::vector<std::uint8_t> &segment = sw.getSegment(i, secondary);

        if (!segment.empty()) {
            std::string name = pre + '0' + std::to_string(i) + ".bin";
            std::ofstream fs;

            fs.open(name, std::ios::out | std::ios::binary);
            std::cout << "Segment size: 0x" << std::hex << segmentSize << std::endl;
            std::cout << "Writing " << name << "..." << std::endl;
            fs.write(reinterpret_cast<const char *>(segment.data()), segmentSize);
        }
    }
}
