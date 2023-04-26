#include "manipulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void add_thing(FILE* file)
{
  struct thing new_thing;

  printf("Enter name (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", new_thing.name);

  printf("Enter type (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", new_thing.type);

  printf("Enter power: ");
  scanf("%d", &new_thing.power);

  fwrite(&new_thing, sizeof (struct thing), 1, file);
};

void display_all_things(FILE* file)
{
  struct thing curr_thing;
  int index = 0;

  fseek(file, 0, SEEK_SET);

  printf("All things in file:\n");

  while (fread(&curr_thing, sizeof (struct thing), 1, file))
  {
    printf("%d. %s\t%s\t%d\n", index, curr_thing.name, curr_thing.type,
            curr_thing.power);
    index++;
  }
};

void remove_thing(FILE* file)
{
  int index;
  struct thing curr_thing, next_thing;

  printf("Enter the index of the thing to remove: ");
  scanf("%d", &index);

  fseek(file, index * sizeof (struct thing), SEEK_SET);

  if (fread(&curr_thing, sizeof (struct thing), 1, file))
  {
    fseek(file, (index + 1) * sizeof (struct thing), SEEK_SET);

    while (fread(&next_thing, sizeof (struct thing), 1, file))
    {
      fseek(file, -2 * sizeof (struct thing), SEEK_CUR);
      fwrite(&next_thing, sizeof (struct thing), 1, file);
      fseek(file, sizeof (struct thing), SEEK_CUR);
    }

    int num_things = ftell(file) / sizeof (struct thing);
    ftruncate(fileno(file), (num_things - 1) * sizeof (struct thing));

    printf("Thing removed successfully.\n");
  }
  else
  {
    printf("Invalid index.\n");
  }
}