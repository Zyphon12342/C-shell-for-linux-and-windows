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

bool isPWD(std::string input) {
    if(input.size() == 3 && input == "pwd") {
      return true;
    }
    return false;
}
void pwd() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    char buffer[1024];
    char* path = getcwd(buffer, 1024);
    if(path != nullptr) {
      std::cout << buffer << '\n';
    }
}
  