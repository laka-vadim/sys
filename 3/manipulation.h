#include <stdio.h>

#define TEXTFIELD_LENGTH 10

struct thing {
  char name[TEXTFIELD_LENGTH];
  char type[TEXTFIELD_LENGTH];
  int power;
};

void add_thing(FILE* file);
void display_all_things(FILE* file);
void remove_thing(FILE* file);