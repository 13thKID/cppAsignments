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
    int code;
    std::string name;
  };

  std::string file_name = "";
  std::vector<Record> table;
  int table_length = {0};
  // last query
  std::vector<Record> last_query;

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
      this->table_length++;
      line_ss = std::stringstream(line);
      if (regex_match(line, std::regex(this->filename_regex)) == 0)
      {
        std::cout << "The format of the line:  " << table_length << "  is not valid.\n"
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

  std::vector<Record> pick_year(int year)
  {
    for (Record &record : this->table)
    {
      if ((record.code / 10000) == year)
      {
        this->last_query.push_back(record);
      }
    }

    return this->last_query;
  }

  void print_table()
  {
    for (Record &record : this->table)
    {
      std::cout << std::fixed << std::setprecision(2) << record.mark << "\t"
                << record.code << "\t"
                << record.name << std::endl;
    }
  }

  void print_last_query()
  {
    for (Record &record : this->last_query)
    {
      std::cout << std::fixed << std::setprecision(2) << record.mark << "\t"
                << record.code << "\t"
                << record.name << std::endl;
    }
  }
  int last_query_length()
  {
    return this->last_query.size();
  }
};