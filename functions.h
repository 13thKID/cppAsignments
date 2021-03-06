#include <vector>
#include <math.h>
#include <numeric>
#include <sys/stat.h>

void sep()
{
  std::cout << "-----------------------------------------------------------" << std::endl;
}

std::vector<int> nth_year_courses_indices(std::vector<int> codes, int year)
{
  std::vector<int> indices;
  // for (std::vector<int>::iterator it = codes.begin(); it != codes.end(); ++it)
  for (std::vector<int>::size_type i = 0; i != codes.size(); i++)
  {
    if ((codes[i] / 10000) == year)
    {
      indices.push_back(i);
    }
  }

  return indices;
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

int get_integer()
{
  double input;

  std::cin >> input;

  if (std::cin.fail() || input - std::floor(input))
  {
    std::cout << "Provided input was incorrect. Try again. The input must be an integer.";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  return (int)input;
}

float get_mean(std::vector<float> data)
{
  float sum_of_elems = std::accumulate(data.begin(), data.end(), 0);
  return sum_of_elems / data.size();
}

float *get_std_dev(std::vector<float> data)
{
  float val{0};
  float mean = get_mean(data);
  float std_dev, err_in_mean;
  float *results = new float[2];

  for (auto &elem : data)
  {
    val += pow((elem - mean), 2);
  }

  results[0] = sqrt(val / (data.size() - 1));
  results[1] = results[0] / sqrt(data.size());

  return results;
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