#include <stdio.h>

#define MAX_NAME_LEN 10
#define MAX_TYPE_LEN 10

struct thing {
  char name[MAX_NAME_LEN];
  char type[MAX_TYPE_LEN];
  int power;
};

void add_thing(FILE* file);
void display_all_things(FILE* file);
void remove_thing(FILE* file);