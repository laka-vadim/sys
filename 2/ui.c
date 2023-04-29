#include <string.h>
#include <stdio.h>
#include "struct.h"
#include "ui.h"

int show_menu()
{
  int choice;
  printf("\nMenu:\n");
  printf("1. Add thing\n");
  printf("2. Edit thing\n");
  printf("3. Remove thing\n");
  printf("4. Display all things\n");
  printf("5. Display by max power\n");
  printf("6. Display in min/max range\n");
  printf("7. Exit\n");
  printf("Enter choice: ");
  scanf("%d", &choice);

  return choice;
};

void input_new_thing_data()
{
  int power;
  char name[10], type[10];

  printf("Enter name (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", name);

  printf("Enter type (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", type);

  printf("Enter power: ");
  scanf("%d", &power);

  add_new_thing(name, type, power);
  printf("Created successfully!\n");
}

void input_edit_thing_data()
{
  int power, index;
  char name[10], type[10];

  printf("Enter index to change: ");
  scanf("%d", &index);

  printf("Enter name (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", name);

  printf("Enter type (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", type);

  printf("Enter power: ");
  scanf("%d", &power);

  update_thing(index, name, type, power);
  printf("Changed successfully!\n");
}

void input_remove_thing_data()
{
  int index;

  printf("Enter index to remove: ");
  scanf("%d", &index);

  remove_thing(index);
  printf("Removed successfully!\n");
}

void show_all_records()
{
  printf("All records\n");
  printf("Index | Name | Type | Power\n");
  for(int index = 0; index < get_amount_of_records(); index++)
  {
    struct thing curr = get_thing_by_id(index);
    printf("%d.\t%s\t%s\t%d\n",
      index,
      curr.name,
      curr.type,
      curr.power
      );
  }
};

void display_max_power_thing()
{
  int max_power = 0;

  for(int i = 0; i < get_amount_of_records(); i++)
  {
    int curr_power = get_thing_by_id(i).power;

    if (curr_power > max_power)
    {
      max_power = curr_power;
    }
  }

  printf ("Select by max power\n");
  for(int i = 0; i < get_amount_of_records(); i++)
  {
    struct thing curr_thing = get_thing_by_id(i);

    if (curr_thing.power == max_power)
    {
      printf("%d.\t%s\t%s\t%d\n",
        i,
        curr_thing.name,
        curr_thing.type,
        curr_thing.power
        );
    }
  }
};

void display_by_power_in_range()
{
  int min_power, max_power;

  printf("Enter min power: ");
  scanf("%d", &min_power);

  printf("Enter max power: ");
  scanf("%d", &max_power);

  printf("Select in range from %d to %d\n", min_power, max_power);
  for(int i = 0; i < get_amount_of_records(); i++)
  {
    struct thing curr_thing = get_thing_by_id(i);

    if(curr_thing.power >= min_power && curr_thing.power <= max_power)
    {
      printf("%d.\t%s\t%s\t%d\n",
        i,
        curr_thing.name,
        curr_thing.type,
        curr_thing.power
        );
    }
  }
};

void exit_message()
{
  printf("Goodbye!\n");
  free_memory();
}
