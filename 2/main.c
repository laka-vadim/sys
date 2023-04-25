#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct thing {
  char name[10];
  char type[10];
  int power;
};

void addThing(struct thing* things, int* count, char name[10], char type[10], int power) {
    struct thing newThing;

    strcpy(newThing.name, name);
    strcpy(newThing.type, type);
    newThing.power = power;

    things[*count] = newThing;
    (*count)++;
};

void displayMaxPowerThing(struct thing* things, int count) {
    int max_power = 0;

    for (int i = 0; i < count; i++) {
        if (things[i].power > max_power) {
            max_power = things[i].power;
        }
    }

    for (int i = 0; i < count; i++) {
        if (things[i].power == max_power) {
            printf("%s\t%s\t%d\n", things[i].name, things[i].type, things[i].power);
        }
    }
};

void displayPowerRange(struct thing* things, int count, int minPower, int maxPower) {
    for (int i = 0; i < count; i++) {
        if (things[i].power >= minPower && things[i].power <= maxPower) {
            printf("%s\t%s\t%d\n", things[i].name, things[i].type, things[i].power);
        }
    }
}

int main(int argc, char *argv[]) {
    int count = 0;
    struct thing things[5];

    addThing(things, &count, "firstN", "firstT", 10);
    addThing(things, &count, "secondN", "secondT", 20);
    addThing(things, &count, "thirdN", "thirdT", 30);
    addThing(things, &count, "fourthN", "fourthT", 40);
    addThing(things, &count, "fifthN", "fifthT", 40);

    displayMaxPowerThing(things, count);
    printf("-----------\n");
    displayPowerRange(things, count, 20, 50);
}
