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

  my_db->pick_year(1);
  my_db->show_query();
  my_db->sort("marks", false);
  sep();
  my_db->show_table();

  return 0;
}