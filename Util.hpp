#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "StratWad.hpp"

void usage();
void printInfo(const StratWad &sw);
void dumpSegments(const StratWad &sw, bool secondary);

#endif
