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
#include "echo.cpp"
#include "cd.cpp"
#include "exit.cpp"
#include "pwd.cpp"
#include "exec.cpp"
#include "exit.cpp"
#pragma once

bool isType(std::string input) {
    if(input.size() >= 4 && input.substr(0,4) == "type") return true;
    return false;
}


void type(std::string input) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::string cmd = removeFirstWord(input);
    if(isEcho(cmd) || isType(cmd) || isExit(cmd) || isPWD(cmd) || isCD(cmd)) {
      std::cout << cmd << " is a shell builtin" << '\n';
    } else {
      char* pathEnv = getenv("PATH");
      bool found = false;
      if(pathEnv != nullptr) {
        std::string pathStr = pathEnv;
  #ifdef _WIN32
        char separator = ';';
  #else
        char separator = ':';
  #endif
        size_t start = 0;
        size_t pos;
        while((pos = pathStr.find(separator, start)) != std::string::npos) {
          std::string dir = pathStr.substr(start, pos - start);
          std::string fullPath = dir + "/" + cmd;
          if(access(fullPath.c_str(), X_OK) == 0) {
            std::cout << cmd << " is " << fullPath << '\n';
            found = true;
            break;
          }
          start = pos + 1;
        }
        if(!found) {
          std::string dir = pathStr.substr(start);
          std::string fullPath = dir + "/" + cmd;
          if(access(fullPath.c_str(), X_OK) == 0) {
            std::cout << cmd << " is " << fullPath << '\n';
            found = true;
          }
        }
      }
      if(!found) {
        std::cout << cmd << ": " << "not found" << '\n';
      }
    }
}