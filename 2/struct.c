#include <stdio.h>   
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"

int g_amount_of_records = 0;
struct thing* g_thing_records;

void write_thing_by_index(int index, char name[10], char type[10], int power)
{
  strcpy(g_thing_records[index].name, name);
  strcpy(g_thing_records[index].type, type);
  g_thing_records[index].power = power;
};

int get_amount_of_records()
{
  return g_amount_of_records;
}

int get_new_size()
{
  return sizeof(struct thing) * g_amount_of_records;
};

bool check_index(int index)
{
  if(index < 0 || index > g_amount_of_records - 1) return false;
  return true;
}

int add_new_thing(char name[10], char type[10], int power)
{
  g_amount_of_records++;

  if(g_amount_of_records == 0)
  {
    g_thing_records = malloc(sizeof(struct thing));
  }
  else
  {
    g_thing_records = realloc(g_thing_records, get_new_size());
  }

  if(g_thing_records == NULL) return -1;

  write_thing_by_index(g_amount_of_records - 1, name, type, power);

  return 0;
};

int update_thing(int index, char name[10], char type[10], int power)
{
  if(!check_index(index)) return -1;

  write_thing_by_index(index, name, type, power);

  return 0;
};

int remove_thing(int index)
{
  if(!check_index(index)) return -1;
  
  for(int i = index; i < g_amount_of_records - 1; i++)
  {
    g_thing_records[index] = g_thing_records[index + 1];
  }

  g_amount_of_records--;
  g_thing_records = realloc(g_thing_records, get_new_size());

  if(g_thing_records == NULL) return -1;
  return 0;
};

struct thing get_thing_by_id(int index)
{
  if(check_index(index)) return g_thing_records[index];
  exit(-1);
}

void free_memory()
{
  free(g_thing_records);
}
