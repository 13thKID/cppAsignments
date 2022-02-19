#include <iostream>
#include <string>
#include <vector>

#include "functions.h"
#include "db.h"

int main()
{
  std::string file_name;
  DB *my_db = new DB;

  std::cout << "Each line of the file MUST be provided in the following form:"
            << "\n\n"
            << "##.# \\s ##### \\s <name-of-the-course>"
            << "\n\n"
            << "\t# \t: integer number\n"
            << "\t\\s \t: single space"
            << "\n\n";

  std::cout << "Provide the name of the file or press ENTER to proceed with the name 'courserlist.dat:'";
  std::getline(std::cin, file_name, '\n');

  my_db->read_db_file(file_name);

  char action;
  while (true)
  {
    action = '0';
    sep();

    std::cout << "Choose action: "
              << "\n"
              << "(q) - new query"
              << "\n"
              << "(Q) - add another query"
              << "\n"
              << "(s) - show query"
              << "\n"
              << "(S) - show whole table"
              << "\n"
              << "(n) - show statistics for the last query"
              << "\n"
              << "(c) - sort the last query"
              << "\n"
              << "(!) - quit"
              << "\n"
              << "action: ";
    std::cin >> action;

    switch (action)
    {
    case 'q':
    {
      sep();
      int *year = new int;

      std::cout << "Which courses should be included in the NEW query:"
                << "\n"
                << "(1) - first year courses"
                << "\n"
                << "(2) - second year courses"
                << "\n"
                << "(3) - third year courses"
                << "\n"
                << "(4) - all courses"
                << "\n"
                << "year: ";
      std::cin >> *year;

      my_db->pick_year(*year);
      delete year;

      my_db->show_query();
      continue;
    };
    case 'Q':
    {
      sep();
      int *year = new int;

      std::cout << "Which courses should be ADDED to the last query:"
                << "\n"
                << "(1) - first year courses"
                << "\n"
                << "(2) - second year courses"
                << "\n"
                << "(3) - third year courses"
                << "\n"
                << "(4) - all courses"
                << "\n"
                << "year: ";
      std::cin >> *year;

      my_db->pick_year(*year, true);
      delete year;

      my_db->show_query();
      continue;
    };

    case 's':
    {
      sep();
      my_db->show_query();
      continue;
    }

    case 'S':
    {
      sep();
      my_db->show_table();
      continue;
    }

    case 'n':
    {
      sep();

      float *std_dev = new float;
      std_dev = my_db->std_dev();
      std::cout << "Mean: " << my_db->mean() << std::endl;
      std::cout << "Standard devaition: " << std_dev[0] << std::endl;
      std::cout << "Standard error in the mean: " << std_dev[1] << std::endl;

      delete std_dev;
      continue;
    }

    case 'c':
    {
      sep();
      char *column = new char;

      std::cout << "Which column should be used for sorting:"
                << "\n"
                << "(1) - marks"
                << "\n"
                << "(2) - codes"
                << "\n"
                << "column: ";

      std::cin >> column;

      switch (*column)
      {
      case '1':
        my_db->sort("marks");
        break;
      case '2':
        my_db->sort("codes");
        break;

      default:
        break;
      }

      sep();
      my_db->show_query();

      continue;
    }
    case '!':
      return 0;

    default:
      break;
    }
  }

  // my_db->pick_year(2);
  // my_db->sort("marks");
  // sep();
  // my_db->show_query();
  // std::cout << my_db->mean() << std::endl;

  // float *std_dev = my_db->std_dev();

  // std::cout << std_dev[0] << std::endl;
  // std::cout << std_dev[1] << std::endl;

  // my_db->add_record();
  // my_db->show_table();
  return 0;
}