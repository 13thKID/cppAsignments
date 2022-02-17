#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

// Custom headers
#include "functions.h"

#define DEFAULT_FILE_NAME "courselist.dat";

int main()
{
  std::string input = "";

  std::fstream input_file;
  std::string file_name = DEFAULT_FILE_NAME;

  /** -------------------------------------------------------------------------------
   * Getting the file name
   * */

  while (true)
  {
    std::cout << "Each line of the file MUST be provided in the following form:"
              << "\n\n"
              << "##.# \\s ##### \\s <name-of-the-course>"
              << "\n\n"
              << "\t# \t: integer number\n"
              << "\t\\s \t: single space"
              << "\n\n";

    std::cout << "Provide the name of the file or press ENTER to proceed with the name 'courserlist.dat:'";

    std::getline(std::cin, input, '\n');
    if (input.length() != 0)
    {
      file_name = input;
    }

    if (!file_exists(file_name))
    {
      std::cout << "File with a given name does not exists. Press ENTER to try again" << std::endl;
      // Must be resetted to enable continuing with a default file name
      std::getchar(); // Wait for the user to press
      input = "";
      file_name = DEFAULT_FILE_NAME;
      continue;
    }

    break;
  }

  /** -------------------------------------------------------------------------------
   * Reading the file
   * */

  input_file.open(file_name);

  if (!input_file.is_open())
  {
    std::cout << "File is not opened from unknown reasons. Try again" << std::endl;
    return 0;
  }

  // variables
  std::string line = "";
  std::stringstream line_ss;
  int line_number{0};
  std::vector<std::string> course_names;
  std::vector<float> course_marks;
  std::vector<int> course_codes;
  // Regexp for testing the line format: ##.# \s ##### \s \s \s <name-of-the-course>
  std::regex str_expr("^[1-9]+[0-9]+\\.[0-9]+\\s[0-9]{5}\\s+[A-Z]+.*$");

  std::cout << "File was opened correctly!" << std::endl;
  sep();

  // temporary variables
  int *code = new int;
  float *mark = new float;
  std::string *name = new std::string;

  while (getline(input_file, line, '\n'))
  {
    line_number++;
    line_ss = std::stringstream(line);
    if (std::regex_match(line, str_expr) == 0)
    {
      std::cout << "The format of the line:  " << line_number << "  is not valid.\n"
                << "Check the file and restart the program." << std::endl;
      return 0;
    }

    line_ss >> *mark >> *code;
    getline(line_ss, *name);

    course_marks.push_back(*mark);
    course_codes.push_back(*code);
    course_names.push_back(*name);
  }
  delete mark;
  delete code;
  delete name;

  std::cout << "Your file contains " << line_number << " lines."
            << "\n\n";

  /** -------------------------------------------------------------------------------
   * Operations on the data
   * */

  int mode;
  int total_courses;
  std::vector<int> selected_courses_indices;

  std::cout << "Which courses should be included in the calculations"
            << "\n"
            << "(1) - first year courses"
            << "\n"
            << "(2) - second year courses"
            << "\n"
            << "(3) - third year courses"
            << "\n"
            << "(4) - all courses";
  while (true)
  {
    std::cout << "\nChoose: ";

    if (!(mode = get_integer()))
      continue;

    if (mode <= 3)
    {
      selected_courses_indices = nth_year_courses_indices(course_codes, mode);
    }
    else if (mode == 4)
    {
      for (int i = 0; i != course_codes.size(); i++)
        selected_courses_indices.push_back(i);
    }
    else
    {
      std::cout << "There are no courses for " << mode << " year. Try again!";
      continue;
    }
    break;
  }

  // Assigning total number of the courses found
  total_courses = selected_courses_indices.size();

  // Printing out the selected courses
  sep();
  std::cout << "Total courses: " << total_courses << "\n\n";
  for (auto i : selected_courses_indices)
  {
    std::cout << std::fixed << std::setprecision(1) << course_marks[i] << "\t"
              << course_codes[i] << "\t"
              << course_names[i] << std::endl;
  }

  return 0;
}