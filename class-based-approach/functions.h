#include <string>
#include <fstream>
#include <sys/stat.h>

void sep()
{
  std::cout << "-----------------------------------------------------------" << std::endl;
}

inline bool file_exists(const std::string &name)
{
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

// inline bool file_exists(const std::string &name)
// {
//   std::ifstream f(name.c_str());
//   return f.good();
// }