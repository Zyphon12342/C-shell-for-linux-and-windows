#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <array>
#include <sstream>
#include <vector>
#include <algorithm>
#pragma once

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