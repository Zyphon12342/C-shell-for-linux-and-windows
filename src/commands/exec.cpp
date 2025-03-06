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

bool isExe(std::string input) {
    std::string filename = firstWord(input);
  #ifdef _WIN32
    if (filename.find(".exe") == std::string::npos) {
        filename += ".exe";
    }
  #endif
    char* pathEnv = getenv("PATH");
    if (!pathEnv) return false;
    std::string pathStr = pathEnv;
  #ifdef _WIN32
    char separator = ';';
  #else
    char separator = ':';
  #endif
    size_t start = 0, pos;
    while ((pos = pathStr.find(separator, start)) != std::string::npos) {
        std::string dir = pathStr.substr(start, pos - start);
        std::string fullPath = dir + "/" + filename;
        if (access(fullPath.c_str(), X_OK) == 0) return true;
        start = pos + 1;
    }
    std::string dir = pathStr.substr(start);
    std::string fullPath = dir + "/" + filename;
    return access(fullPath.c_str(), X_OK) == 0;
  }
  
  
  void executeexe(std::string command) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run command.\n";
        return;
    }
    std::array<char, 128> buffer;
    std::string result = "";
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
      result += buffer.data();
    }
    pclose(pipe);
    std::cout << result;
  }
  