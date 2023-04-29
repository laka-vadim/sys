#include <stdio.h>

#define TEXTFIELD_LENGTH 10
#define SEEK_DATA_SET sizeof(int)

struct thing {
  char name[TEXTFIELD_LENGTH];
  char type[TEXTFIELD_LENGTH];
  int power;
};

void add_thing(int file_desc);
void display_all_things(int file_desc);
void edit_thing(int file_desc);
void remove_thing(int file_desc);
void set_record_size(int file_desc);
void display_things_by_maxpower(int file_desc);
void display_things_in_range(int file_desc);
