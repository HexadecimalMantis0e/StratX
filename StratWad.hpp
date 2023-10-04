#ifndef STRATWAD_HPP
#define STRATWAD_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

class StratWad {
    private:
        const std::uint32_t header = 0x42474942;
        std::uint32_t ptrToData = 0;
        std::uint32_t wadVersion = 0;
        std::uint32_t unknown = 0;

        std::string description;
        std::string signature;

        std::vector<std::uint32_t> secondarySizes;
        std::vector<std::uint32_t> primarySizes;

        std::string arguments;

        std::vector<std::vector<std::uint8_t>> primary;
        std::vector<std::vector<std::uint8_t>> secondary;

    public:
        bool readStratWad(std::ifstream &fs);
        std::uint32_t getWadVersion() const;
        const std::string &getDescription() const;
        const std::string &getSignature() const;
        std::uint32_t getSegmentSize(int segment, bool secondary) const;
        std::uint32_t getSegmentCount(bool secondary) const;
        const std::string &getArguments() const;
        const std::vector<std::uint8_t> &getSegment(int segment, bool secondary) const;
};

#endif
