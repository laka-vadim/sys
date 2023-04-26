#include <stdio.h>
#include <unistd.h>
#include "manipulation.h"

int main(int argc, char* argv[]) {
  FILE* file = fopen("things.dat", "ab+");

  if (!file)
  {
    printf("Error opening file.\n");
    return 1;
  }

  int choice;
  while (choice != 4)
  {
    printf("\nMenu:\n");
    printf("1. Add thing\n");
    printf("2. Display all things\n");
    printf("3. Remove thing\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) 
    {
    case 1:
      add_thing(file);
      break;
    case 2:
      display_all_things(file);
      break;
    case 3:
      remove_thing(file);
      break;
    case 4:
      break;
    default:
      printf("Invalid choice.\n");
    }
  }

  fclose(file);
  return 0;
};
