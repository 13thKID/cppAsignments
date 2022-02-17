#include <iostream>
#include <vector>

#include "functions.h"

int main()
{

  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<std::vector<int>> vec2 = {
      {1, 2, 3, 4, 5},
      {6, 7, 8, 9}};

  print_vector(vec);
  print_vector(vec2);

  return 0;
}