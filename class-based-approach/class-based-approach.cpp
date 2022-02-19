#include <iostream>
#include <string>

// Custom
#include "functions.h"
#include "db.h"

int main()
{
  bool db_opened = false;
  std::string file_name;
  DB *my_db = new DB;

  while (true)
  {
    std::cout << "Each line of the file MUST be provided in the following form:"
              << "\n\n"
              << "##.# \\s ##### \\s <name-of-the-course>"
              << "\n\n"
              << "\t# \t: integer number\n"
              << "\t\\s \t: single space"
              << "\n\n";

    std::cout << "Provide the name of the file or press ENTER to proceed with the name 'courserlist.dat': ";
    std::getline(std::cin, file_name, '\n');

    db_opened = my_db->read_db_file(file_name);

    char action;
    while (db_opened)
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
                << "(a) - add record to the table"
                << "\n"
                << "(e) - export query to the file"
                << "\n"
                << "(D) - open another database"
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
                  << "(3) - names"
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
        case '3':
          my_db->sort("names");
          break;

        default:
          break;
        }

        sep();
        my_db->show_query();

        continue;
      }

      case 'a':
      {
        sep();
        my_db->add_course();

        continue;
      }
      case 'e':
      {
        sep();
        my_db->save_query();

        continue;
      }
      case 'D':
      {
        db_opened = false;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
      }
      case '!':
        return 0;

      default:
        break;
      }
    }
  }

  return 0;
}