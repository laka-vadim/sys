#include <stdio.h>

#define TEXTFIELD_LENGTH 10

struct thing {
  char name[TEXTFIELD_LENGTH];
  char type[TEXTFIELD_LENGTH];
  int power;
};

void add_thing(int file_desc);
void display_all_things(int file_desc);
void edit_thing(int file_desc);
void remove_thing(int file_desc);