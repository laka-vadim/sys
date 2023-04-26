#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structManipulation.h"

#define INITIAL_AMOUNT_OF_RECORDS 0

int main(int argc, char *argv[])
{
  int count = INITIAL_AMOUNT_OF_RECORDS;
  struct thing things[5];

  add_thing(things, &count, "firstN", "firstT", 10);
  add_thing(things, &count, "secondN", "secondT", 20);
  add_thing(things, &count, "thirdN", "thirdT", 30);
  add_thing(things, &count, "fourthN", "fourthT", 40);
  add_thing(things, &count, "fifthN", "fifthT", 40);

  display_max_power_thing(things, count);
  printf("-----------\n");
  display_power_range(things, count, 20, 50);
}
