#include "manipulation.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int get_record_size(int file_desc)
{
  int size;
  lseek(file_desc, 0, SEEK_SET);
  read(file_desc, &size, sizeof(int));
  return size;
}

int get_data_size(int file_desc)
{
  int size;
  lseek(file_desc, 0, SEEK_SET);
  read(file_desc, &size, sizeof(int));
  return size;
}

void set_record_size(int file_desc)
{
  int size_of_record = sizeof(struct thing);
  lseek(file_desc, 0, SEEK_SET);
  write(file_desc, &size_of_record, sizeof(int));

  printf("Fixed record size is %d\n\n", get_record_size(file_desc));
};

int get_record_amount(int file_desc)
{
  struct stat file_info;
  fstat(file_desc, &file_info);
  return (file_info.st_size - SEEK_DATA_SET) / get_record_size(file_desc);
}

struct thing* get_data(int file_desc)
{
  struct stat file_info;
  fstat(file_desc, &file_info);

  int records_amount = (file_info.st_size - SEEK_DATA_SET) / get_record_size(file_desc);
  struct thing* things = malloc(file_info.st_size - SEEK_DATA_SET);

  lseek(file_desc, SEEK_DATA_SET, SEEK_SET);
  read(file_desc, things, file_info.st_size - SEEK_DATA_SET);

  return things;
}

void add_thing(int file_desc)
{
  struct thing new_thing;

  printf("Enter name (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", new_thing.name);

  printf("Enter type (max length %d): ", TEXTFIELD_LENGTH);
  scanf("%s", new_thing.type);

  printf("Enter power: ");
  scanf("%d", &new_thing.power);

  lseek(file_desc, 0, SEEK_END);
  ssize_t write_status = write(file_desc, &new_thing, get_record_size(file_desc));

  if(write_status == -1)
  {
    perror("write");
  }
  printf("Record created successfully\n");
};

void display_all_things(int file_desc)
{
  struct thing* things = get_data(file_desc);

  printf("All things in file:\n");

  for(int index = 0; index < get_record_amount(file_desc); ++index)
  {
    printf("%d. %s\t%s\t%d\n", index, things[index].name, things[index].type,
             things[index].power);
  }
  free(things);
};

void display_things_by_maxpower(int file_desc)
{
  struct thing* things = get_data(file_desc);

  printf("Things by max power in file:\n");

  int max_power = 0;

  for(int index = 0; index < get_record_amount(file_desc); ++index)
  {
    if(max_power < things[index].power) max_power = things[index].power;
  }

  for(int index = 0; index < get_record_amount(file_desc); ++index)
  {
    if(things[index].power == max_power)
    {
    printf("%d. %s\t%s\t%d\n", index, things[index].name, things[index].type,
             things[index].power);
    }
  }
  free(things);
};

void display_things_in_range(int file_desc)
{
  struct thing* things = get_data(file_desc);
  int min_power, max_power;

  printf("Enter min power: ");
  scanf("%d", &min_power);

  printf("Enter max power: ");
  scanf("%d", &max_power);

  for(int index = 0; index < get_record_amount(file_desc); ++index)
  {
    if(things[index].power >= min_power && things[index].power <= max_power)
    {
    printf("%d. %s\t%s\t%d\n", index, things[index].name, things[index].type,
             things[index].power);
    }
  }
  free(things);
}

void edit_thing(int file_desc)
{
  int index;

  printf("Enter the index of the thing to edit: ");
  scanf("%d", &index);

  lseek(file_desc, get_record_size(file_desc) * index + SEEK_DATA_SET, SEEK_SET);
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

  int records_amount = file_info.st_size / get_record_size(file_desc);
  int records_to_rewrite = records_amount - index - 1;
  int rewriting_bytes = records_to_rewrite * get_record_size(file_desc);

  struct thing* things = malloc(rewriting_bytes);
  lseek(file_desc, (index + 1) * get_record_size(file_desc) + SEEK_DATA_SET, SEEK_SET);
  read(file_desc, things, rewriting_bytes);

  lseek(file_desc, index * get_record_size(file_desc) + SEEK_DATA_SET, SEEK_SET);
  write(file_desc, things, rewriting_bytes);

  ftruncate(file_desc, (records_amount - 1) * get_record_size(file_desc));

  printf("Thing removed successfully.\n");
  free(things);
};
