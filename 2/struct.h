#define TEXTFIELD_LENGTH 10

struct thing
{
  char name[TEXTFIELD_LENGTH];
  char type[TEXTFIELD_LENGTH];
  int power;
};

int add_new_thing(
  char name[TEXTFIELD_LENGTH],
  char type[TEXTFIELD_LENGTH],
  int power
  );
int update_thing(
  int index,
  char name[TEXTFIELD_LENGTH],
  char type[TEXTFIELD_LENGTH],
  int power
  );
int remove_thing(int index);
struct thing get_thing_by_id(int index);
int get_amount_of_records();
void free_memory();
