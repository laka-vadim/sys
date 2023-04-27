#include "manipulation.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void add_thing(int file_desc)
{
  struct thing new_thing;

  printf("Enter name (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", new_thing.name);

  printf("Enter type (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", new_thing.type);

  printf("Enter power: ");
  scanf("%d", &new_thing.power);

  ssize_t write_status = write(file_desc, &new_thing, sizeof(struct thing));

  if(write_status == -1)
  {
    perror("write");
  }
  printf("Record created successfully\n");
};

void display_all_things(int file_desc)
{
  struct stat file_info;
  fstat(file_desc, &file_info);

  int records_amount = file_info.st_size / sizeof(struct thing);
  struct thing* things = malloc(file_info.st_size);

  read(file_desc, things, file_info.st_size);

  printf("All things in file:\n");

  for(int index = 0; index < records_amount; ++index)
  {
    printf("%d. %s\t%s\t%d\n", index, things[index].name, things[index].type,
             things[index].power);
  }
};

void edit_thing(int file_desc)
{
  int index;

  printf("Enter the index of the thing to edit: ");
  scanf("%d", &index);

  lseek(file_desc, sizeof(struct thing) * index, SEEK_SET);
  add_thing(file_desc);
  printf("Record successfully edited\n");
};

void remove_thing(int file_desc)
{
  int index;

  printf("Enter the index of the thing to remove: ");
  scanf("%d", &index);

  struct stat file_info;
  fstat(file_desc, &file_info);

  int records_amount = file_info.st_size / sizeof(struct thing);
  int records_to_rewrite = records_amount - index - 1;
  int rewriting_bytes = records_to_rewrite * sizeof(struct thing);

  struct thing* things = malloc(rewriting_bytes);
  lseek(file_desc, (index + 1) * sizeof (struct thing), SEEK_SET);
  read(file_desc, things, rewriting_bytes);

  lseek(file_desc, index * sizeof (struct thing), SEEK_SET);
  write(file_desc, things, rewriting_bytes);

  ftruncate(file_desc, (records_amount - 1) * sizeof (struct thing));

  printf("Thing removed successfully.\n");
}