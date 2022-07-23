#ifndef STRATWAD_HPP
#define STRATWAD_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class StratWad {
    private:
        const size_t header = 0x42474942;
        size_t ptrToData = 0;
        size_t wadVersion = 0;
        size_t unknown = 0;

        std::string description;
        std::string signature;

        std::vector<size_t> secondarySizes;
        std::vector<size_t> primarySizes;

        std::string arguments;

        std::vector<std::vector<unsigned char>> primary;
        std::vector<std::vector<unsigned char>> secondary;

    public:
        bool readStratWad(std::ifstream &fs);
        size_t getWadVersion() const;
        const std::string &getDescription() const;
        const std::string &getSignature() const;
        size_t getSegmentSize(int segment, bool secondary) const;
        size_t getSegmentCount(bool secondary) const;
        const std::string &getArguments() const;
        const std::vector<unsigned char> &getSegment(int segment, bool secondary) const;
};

#endif
