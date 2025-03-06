#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <array>
#include <sstream>
#include <vector>
#include <algorithm>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define access _access
#define chdir _chdir
#define getcwd _getcwd
#else
#include <unistd.h>
#endif
#include "../utility/stringchange.cpp"
#pragma once

bool isEcho(std::string input) {
    if(input.size() >= 4 && input.substr(0,4) == "echo") return true;
    return false;
}

void echo(std::string input) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::cout << removeFirstWord(input) << '\n';
}
  