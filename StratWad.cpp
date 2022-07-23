#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "StratWad.hpp"

bool StratWad::readStratWad(std::ifstream &fs) {
    size_t header = 0;

    fs.read(reinterpret_cast<char *>(&header), 0x04);

    if (header != this->header) {
        return false;
    }

    fs.read(reinterpret_cast<char *>(&ptrToData), 0x04);
    fs.read(reinterpret_cast<char *>(&wadVersion), 0x04);
    fs.read(reinterpret_cast<char *>(&unknown), 0x04);

    std::getline(fs, description, '\0');
    fs.seekg(0x50, std::ios::beg);
    std::getline(fs, signature, '\0');
    fs.seekg(0x78, std::ios::beg);

    for (int i = 0; i < 2; i++) {
        size_t segmentSize = 0;

        fs.read(reinterpret_cast<char *>(&segmentSize), 0x04);
        secondarySizes.push_back(segmentSize);
    }

    for (int i = 0; i < 3; i++) {
        size_t segmentSize = 0;

        fs.read(reinterpret_cast<char *>(&segmentSize), 0x04);
        primarySizes.push_back(segmentSize);
    }

    fs.seekg(ptrToData & 0x0F, std::ios::cur);
    std::getline(fs, arguments, '\0');
    fs.seekg(ptrToData + 0x0C, std::ios::beg);

    for (int i = 0; i < 3; i++) {
        std::vector<unsigned char> segment(primarySizes.at(i), 0x00);

        if (!segment.empty()) {
            fs.read(reinterpret_cast<char *>(segment.data()), primarySizes.at(i));
        }

        primary.push_back(segment);
    }

    for (int i = 0; i < 2; i++) {
        std::vector<unsigned char> segment(secondarySizes.at(i), 0x00);

        if (!segment.empty()) {
            size_t offset = fs.tellg();
            size_t secondaryAlign = 0x800;
            size_t paddingSize = ((offset + secondaryAlign - 0x01) / secondaryAlign * secondaryAlign) - offset;

            fs.seekg(paddingSize, std::ios::cur);
            fs.read(reinterpret_cast<char *>(segment.data()), secondarySizes.at(i));
        }

        secondary.push_back(segment);
    }
    return true;
}

size_t StratWad::getWadVersion() const {
    return wadVersion;
}

const std::string &StratWad::getDescription() const {
    return description;
}

const std::string &StratWad::getSignature() const {
    return signature;
}

size_t StratWad::getSegmentSize(int segment, bool secondary) const {
    return secondary ? secondarySizes.at(segment) : primarySizes.at(segment);
}

size_t StratWad::getSegmentCount(bool secondary) const {
    return secondary ? this->secondary.size() : primary.size();
}

const std::string &StratWad::getArguments() const {
    return arguments;
}

const std::vector<unsigned char> &StratWad::getSegment(int segment, bool secondary) const {
    return secondary ? this->secondary.at(segment) : primary.at(segment);
}
