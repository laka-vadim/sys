struct thing
{
  char name[10];
  char type[10];
  int power;
};

void add_thing (struct thing *things,
  int *count,
  char name[10],
  char type[10],
  int power
);
void display_max_power_thing (struct thing *things, int count);
void display_power_range (struct thing *things,
  int count,
  int min_power,
  int max_power
);