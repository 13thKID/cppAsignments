#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

// #include "functions.h"

class DB
{
private:
  std::string default_file_name = "courselist.dat";
  std::string filename_regex = "^[1-9]+[0-9]+\\.[0-9]+\\s[0-9]{5}\\s[A-Z]+.*$";

public:
  struct Record
  {
    float mark;
    double code;
    std::string name;
  };

  std::string file_name = "";
  int line_number = {0};
  std::vector<Record> table;

  bool verify_file(std::string file_name = "")
  {
    // No filename give
    if (file_name == "" && !file_exists(default_file_name))
    {
      std::cout << "There is no file \"" << default_file_name << "\" in current directory"
                << "Press ENTER and try again";
      getchar();
      return false;
    }
    else
    {
      this->file_name = this->default_file_name;
      return true;
    }
    if (file_name != "" && !file_exists(file_name)) // Filename given
    {
      std::cout << "There is no file \"" << file_name << "\" in current directory"
                << "Press ENTER and try again";
      getchar();
      return false;
    }
    else
    {
      this->file_name = file_name;
      return true;
    }
  }

  bool read_db_file(std::string file_name = "")
  {
    if (!verify_file(file_name))
      return 0;

    std::fstream input_file;
    input_file.open(this->file_name);

    // Unknown problem with opening the file
    if (!input_file.is_open())
    {
      std::cout << "File is not opened from unknown reasons. Try again" << std::endl;
      return 0;
    }

    // Reading file line by line
    std::string line;
    std::stringstream line_ss;

    while (getline(input_file, line, '\n'))
    {
      this->line_number++;
      line_ss = std::stringstream(line);
      if (regex_match(line, std::regex(this->filename_regex)) == 0)
      {
        std::cout << "The format of the line:  " << line_number << "  is not valid.\n"
                  << "Check the file and restart the program." << std::endl;
        return 0;
      }
      // Define, fill and push the record to the table
      Record record;
      line_ss >> record.mark >> record.code;
      line_ss.ignore(1); // Necessary to avoid space before the course name
      getline(line_ss, record.name);
      this->table.push_back(record);
    }

    return true;
  }

  void status()
  {
    std::cout << "DB is ready to serve you" << std::endl;
  }
};