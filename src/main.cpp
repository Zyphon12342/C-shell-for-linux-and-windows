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
#include "utility/stringchange.cpp"
#include "commands/cd.cpp"
#include "commands/pwd.cpp"
#include "commands/echo.cpp"
#include "commands/type.cpp"
#pragma once

bool iscommand(std::string input) {
  if(input.size() >= 5 && input[4] == ' ' &&
    (isEcho(input.substr(0,4)) || isType(input.substr(0,4)) || isExit(input.substr(0,4)))){
      return true;
    }
  return false;
}


int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  while(true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);
    if(input == "exit 0") {
      break;
    } else if(isEcho(input) && iscommand(input)) {
      echo(input);
    } else if(isType(input) && iscommand(input)) {
      type(input);
    } else if(isExe(input)) {
      executeexe(input);
    } else if(isPWD(input)) {
      pwd();
    } else if(isCD(input)) {
      cd(input);
    } else {
      std::cout << input << ": " << "command not found" << '\n';
    }
  }
  return 0;
}
