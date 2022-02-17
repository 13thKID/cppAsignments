#include <iostream>
#include <string>
#include <vector>

#include "functions.h"

std::vector<std::string> str_split(std::string str, std::string delim = " ")
{
  std::vector<std::string> pieces;
  size_t first_delim;

  while ((first_delim = str.find(delim)) != std::string::npos)
  {
    pieces.push_back(
        str.substr(0, first_delim));
    str.erase(0, first_delim + 1);
  }
  pieces.push_back(str);

  return pieces;
}

int main()
{
  std::string str = "Hello my dear friend!";

  std::cout << str << std::endl;

  std::vector<std::string> vec = str_split(str);

  print_vector(vec);

  return 0;
}