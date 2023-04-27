#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "manipulation.h"

int main(int argc, char* argv[]) {
  // FILE* file = fopen("things.dat", "ab+");
  int file_desc = open("data.dat", O_CREAT | O_RDWR, S_IRWXU);

  if (file_desc == -1)
  {
    printf("Error opening/creating file.\n");
    return 1;
  }

  int choice;
  while (choice != 5)
  {
    printf("\nMenu:\n");
    printf("1. Add thing\n");
    printf("2. Display all things\n");
    printf("3. Edit thing\n");
    printf("4. Remove thing\n");
    printf("5. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) 
    {
    case 1:
      lseek(file_desc, 0, SEEK_END);
      add_thing(file_desc);
      break;
    case 2:
      lseek(file_desc, 0, SEEK_SET);
      display_all_things(file_desc);
      break;
    case 3:
      edit_thing(file_desc);
      break;
    case 4:
      remove_thing(file_desc);
      break;
    case 5:
      break;
    default:
      printf("Invalid choice.\n");
    }
  }

  close(file_desc);
  return 0;
};
