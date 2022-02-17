#include <iostream>

template <typename T>

void to_int(double *x, T)
{
  std::cout << (T)*x << std::endl;
}

int main()
{
  double x{2.5};
  to_int(&x, template <int>);

  return 0;
}