#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <algorithm> // std::sort
#include <numeric>   // std::accumulate
#include <math.h>    // pow

class DB
{
private:
  std::string default_file_name = "courselist.dat";
  std::string filename_regex = "^[1-9]+[0-9]+\\.[0-9]+\\s[0-9]{5}\\s[A-Z]+.*$";

public:
  struct Course
  {
    float mark;
    int code;
    std::string name;
  };

  std::vector<Course> courses;
  std::vector<Course> courses_query;
  std::string file_name = "";
  int table_length = {0};

  bool verify_file(std::string file_name = "")
  {
    // No filename give
    if (file_name == "")
    {
      if (!file_exists(this->default_file_name))
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
    }
    else
    {
      if (!file_exists(file_name))
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
      if (!regex_match(line, std::regex(this->filename_regex)))
      {
        std::cout << "The format of the line:  " << table_length << "  is not valid.\n"
                  << "Check the file and restart the program." << std::endl;
        return 0;
      }
      // Define, fill and push the record to the table
      Course record;
      line_ss >> record.mark >> record.code;
      line_ss.ignore(1); // Necessary to avoid space before the course name
      getline(line_ss, record.name);
      this->courses.push_back(record);
    }

    input_file.close();

    return true;
  }

  std::vector<Course> pick_year(int year, bool add_query = false)
  {
    if (!add_query)
      this->courses_query.clear();
    for (Course &record : this->courses)
    {
      if ((record.code / 10000) == year)
      {
        this->courses_query.push_back(record);
      }
    }

    return this->courses_query;
  }

  void show_table()
  {
    std::cout << "TOTAL: " << this->table_length << std::endl;
    for (Course &record : this->courses)
    {
      std::cout << std::fixed << std::setprecision(2) << record.mark << "\t"
                << record.code << "\t"
                << record.name << std::endl;
    }
    std::cout << "TOTAL: " << this->table_length << std::endl;
  }

  void show_query()
  {
    std::cout << "TOTAL: " << this->query_length() << std::endl;
    for (Course &record : this->courses_query)
    {
      std::cout << std::fixed << std::setprecision(2) << record.mark << "\t"
                << record.code << "\t"
                << record.name << std::endl;
    }
    std::cout << "TOTAL: " << this->query_length() << std::endl;
  }

  void show_course(Course course)
  {
    std::cout << std::fixed << std::setprecision(2) << course.mark << "\t"
              << course.code << "\t"
              << course.name << std::endl;
  }

  int query_length()
  {
    return this->courses_query.size();
  }

  float mean()
  {
    double sum{0};
    for (Course &course : this->courses_query)
    {
      sum += course.mark;
    }
    return sum / this->query_length();
  }

  void add_course()
  {
    Course new_course;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
      std::cout << "Enter the name of the course: ";
      getline(std::cin, new_course.name);

      if (!regex_match(new_course.name, std::regex("^[A-Z][a-zA-Z0-9\\s]{10,}$"))) // At least 10 characters
      {
        std::cout << "Entered name for the course is invalid. Press Enter and try again";
        getchar();
        continue;
      }
      break;
    }

    while (true)
    {
      std::string *code = new std::string;
      std::cout << "Enter the code of the course: ";
      getline(std::cin, *code);

      if (!regex_match(*code, std::regex("^[1-3][0-9]{4,}$")))
      {
        std::cout << "You've typed the wrong course code. Press Enter and try again";
        getchar();
        continue;
      }
      new_course.code = stoi(*code);
      delete code;

      break;
    }

    while (true)
    {
      std::string *mark = new std::string;
      std::cout << "Enter the mark of the course: ";
      getline(std::cin, *mark);

      if (!regex_match(*mark, std::regex("^[1-9][0-9]\\.[0-9]$")))
      {
        std::cout << "You've typed the wrong course mark. Press Enter and try again";
        getchar();
        continue;
      }
      new_course.mark = stof(*mark);
      delete mark;

      break;
    }

    this->courses.push_back(new_course);

    sep();
    std::cout << "You've added the following course:" << std::endl;
    this->show_course(new_course);

    this->table_length++;
  }

  float *std_dev()
  {
    double *sum = new double{0};
    float *mean = new float{this->mean()};
    float *results = new float[2];

    for (Course &course : this->courses_query)
    {
      *sum += pow((course.mark - *mean), 2);
    }

    results[0] = sqrt(*sum / (this->query_length() - 1));
    results[1] = results[0] / sqrt(this->query_length());

    delete mean;
    delete sum;

    return results;
  }
  // Sorting
  struct
  {
    bool operator()(Course lhs, Course rhs) const { return lhs.code < rhs.code; }
  } by_codes;
  struct
  {
    bool operator()(Course lhs, Course rhs) const { return lhs.mark < rhs.mark; }
  } by_marks;
  struct
  {
    bool operator()(Course lhs, Course rhs) const { return lhs.name < rhs.name; }
  } by_names;

  void sort(std::string by = "marks", bool sort_query = true)
  {
    std::vector<Course> *table = &this->courses;
    if (sort_query)
      table = &this->courses_query;

    if (by == "codes")
    {
      std::sort((*table).begin(), (*table).end(), by_codes);
    }
    else if (by == "marks")
    {
      std::sort((*table).begin(), (*table).end(), by_marks);
    }
    else if (by == "names")
    {
      std::sort((*table).begin(), (*table).end(), by_names);
    }
    else
    {
      std::cout << "Unknown column name!" << std::endl;
    }
  }
};