#include <iostream>

int main()
{
  int *p = new int;

  *p = 5;

  std::cout << *p << std::endl;

  delete p;

  std::cout << *p << std::endl;

  return 0;
}