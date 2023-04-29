#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ui.h"

int main(int argc, char *argv[])
{
  int choice;
  while (choice != 7)
  {
    int choice = show_menu();

    switch(choice) 
    {
    case 1:
      input_new_thing_data();
      break;
    case 2:
      input_edit_thing_data();
      break;
    case 3:
      input_remove_thing_data();
      break;
    case 4:
      show_all_records();
      break;
    case 5:
      display_max_power_thing();
      break;
    case 6:
      display_by_power_in_range();
      break;
    case 7:
      exit_message();
      break;
    default:
      printf("Invalid choice.\n");
    }
  }

  return 0;
}
