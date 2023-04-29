#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "manipulation.h"

int main(int argc, char* argv[]) {
  int file_desc = open("data.dat", O_CREAT | O_RDWR, S_IRWXU);

  if (file_desc == -1)
  {
    printf("Error opening/creating file.\n");
    return 1;
  }

  set_record_size(file_desc);

  int choice;
  while (choice != 7)
  {
    printf("\nMenu:\n");
    printf("1. Add thing\n");
    printf("2. Display all things\n");
    printf("3. Edit thing\n");
    printf("4. Remove thing\n");
    printf("5. Display things by max power\n");
    printf("6. Display things by max/min range\n");
    printf("7. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) 
    {
    case 1:
      add_thing(file_desc);
      break;
    case 2:
      display_all_things(file_desc);
      break;
    case 3:
      edit_thing(file_desc);
      break;
    case 4:
      remove_thing(file_desc);
      break;
    case 5:
      display_things_by_maxpower(file_desc);
      break;
    case 6:
      display_things_in_range(file_desc);
      break;
    case 7:
      break;
    default:
      printf("Invalid choice.\n");
    }
  }

  close(file_desc);
  return 0;
};
