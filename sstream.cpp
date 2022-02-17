#include <iostream>
#include <string>
#include <sstream>

#include "functions.h"

int main()
{
  std::vector<std::stringstream *> vec;
  vec.push_back(new std::stringstream{"65.6 10071 Mathematics 1"});
  vec.push_back(new std::stringstream{"66.7 10101 Dynamics"});

  float mark;
  int code;
  for (auto &elem : vec)
  {
    std::cout << elem->str() << std::endl;
  }

  // print_vector(vec);

  return 0;
}