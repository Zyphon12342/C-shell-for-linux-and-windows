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

std::string firstWord(std::string input) {
  std::istringstream iss(input);
  std::string word;
  iss >> word;
  return word;
}
std::string removeFirstWord(const std::string& input) {
  std::istringstream iss(input);
  std::string first;
  if (!(iss >> first)) {
      return "";
  }
  std::string rest;
  std::getline(iss, rest);
  rest.erase(0, rest.find_first_not_of(" \t"));
  return rest;
}

bool isCD(std::string input) {
  if(firstWord(input).size() == 2 && firstWord(input) == "cd") {
    return true;
  }
  return false;
}
bool isEcho(std::string input) {
  if(input.size() >= 4 && input.substr(0,4) == "echo") return true;
  return false;
}
bool isType(std::string input) {
  if(input.size() >= 4 && input.substr(0,4) == "type") return true;
  return false;
}
bool isExit(std::string input) {
  if(input.size() >= 4 && input.substr(0,5) == "exit") return true;
  return false;
}
bool iscommand(std::string input) {
  if(input.size() >= 5 && input[4] == ' ' &&
    (isEcho(input.substr(0,4)) || isType(input.substr(0,4)) || isExit(input.substr(0,4)))){
      return true;
    }
  return false;
}
bool isPWD(std::string input) {
  if(input.size() == 3 && input == "pwd") {
    return true;
  }
  return false;
}
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

void echo(std::string input) {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::cout << removeFirstWord(input) << '\n';
}

void executeCommand(std::string command) {
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

void pwd() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  char buffer[1024];
  char* path = getcwd(buffer, 1024);
  if(path != nullptr) {
    std::cout << buffer << '\n';
  }
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
      executeCommand(input);
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
