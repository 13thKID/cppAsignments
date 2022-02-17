#include <vector>
#include <sys/stat.h>

void sep()
{
  std::cout << "-----------------------------------------------------------" << std::endl;
}

std::vector<std::vector<int>::iterator> nth_year_courses_iterators(std::vector<int> codes, int year)
{
  std::vector<std::vector<int>::iterator> iterators;
  for (std::vector<int>::iterator it = codes.begin(); it != codes.end(); ++it)
  {
    if ((*it / 10000) == year)
    {
      iterators.push_back(it);
      std::cout << *it << std::endl;
    }
  }

  return iterators;
}

inline bool file_exists(const std::string &name)
{
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

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

/** -------------------------------------------------------------------------------
 * print_vector
 * */
void print_vector(std::vector<std::string> vec)
{
  for (auto &elem : vec)
  {
    std::cout << elem << std::endl;
  };
}
void print_vector(std::vector<std::stringstream *> vec)
{
  for (auto &elem : vec)
  {
    std::cout << elem->str() << std::endl;
  };
}
void print_vector(std::vector<int> vec)
{
  for (auto &elem : vec)
  {
    std::cout << elem << std::endl;
  };
}
void print_vector(std::vector<std::vector<std::string>> vec)
{
  for (auto &line : vec)
  {
    for (auto &elem : line)
    {
      std::cout << elem;
      if (elem != *line.end())
      {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  };
}