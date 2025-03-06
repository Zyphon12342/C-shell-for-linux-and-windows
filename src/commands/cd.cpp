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

bool isCD(std::string input) {
    if(firstWord(input).size() == 2 && firstWord(input) == "cd") {
      return true;
    }
    return false;
}

void cd(const std::string& input) {
    std::string path = removeFirstWord(input);
    if (path == "~") {
        const char* homedir = getenv("HOME");
        if (homedir == nullptr) {
            std::cout << "Error: can't find Home Directory" << '\n';
            return;
        } else {
            path = homedir;
        }
    }
    const char* target = path.c_str();
    if (chdir(target) != 0) {
        std::cout << "cd: " << path << ": No such file or directory" << '\n';
    }
}