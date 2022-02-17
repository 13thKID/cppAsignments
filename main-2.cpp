#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

// Custom headers
#include "functions.h" // requires: <sys/stat.h>

int main()
{
  std::string input = "";

  std::fstream input_file;
  std::string file_name = "courselist.dat";

  while (true)
  {
    std::cout << "Each line of the file MUST be provided in the following form:"
              << "\n\n"
              << "<float>\n\n";

    std::cout << "Provide the name of the file or press ENTER to proceed with the name 'courserlist.dat: ";

    std::getline(std::cin, input, '\n');
    if (input.length() != 0)
    {
      file_name = input;
    }

    if (!file_exists(file_name))
    {
      std::cout << "File with a given name does not exists" << std::endl;
      continue;
    }

    break;
  }

  return 0;
}