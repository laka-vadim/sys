#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structManipulation.h"

/// @brief Append item to array of structs
/// @param things Array of structs
/// @param count Counter of records
/// @param name Name of thing
/// @param type Type of thing
/// @param power Power of thing
void add_thing (struct thing *things,
  int *count,
  char name[10],
  char type[10],
  int power
)
{
  struct thing new_thing;

  strcpy (new_thing.name, name);
  strcpy (new_thing.type, type);
  new_thing.power = power;

  things[*count] = new_thing;
  (*count)++;
};

/// @brief Show things with maximal power
/// @param things Array of structs
/// @param count Counter of records
void display_max_power_thing (struct thing *things, int count)
{
  int max_power = 0;

  for (int i = 0; i < count; i++)
    {
      if (things[i].power > max_power)
        {
          max_power = things[i].power;
        }
    }

  printf ("Select by max power\n");
  for (int i = 0; i < count; i++)
    {
      if (things[i].power == max_power)
        {
          printf ("%s\t%s\t%d\n", things[i].name, things[i].type,
                  things[i].power);
        }
    }
};

/// @brief Show list of records with power in selected range
/// @param things Array of structs
/// @param count Counter of records
/// @param min_power Range start from this value
/// @param max_power Range end on this value
void display_power_range (struct thing *things,
  int count,
  int min_power,
  int max_power
)
{
  printf ("Select in range from %d to %d\n", min_power, max_power);
  for (int i = 0; i < count; i++)
    {
      if (things[i].power >= min_power && things[i].power <= max_power)
        {
          printf ("%s\t%s\t%d\n", things[i].name, things[i].type,
                  things[i].power);
        }
    }
};
