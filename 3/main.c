#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NAME_LEN 10
#define MAX_TYPE_LEN 10

struct thing {
  char name[MAX_NAME_LEN];
  char type[MAX_TYPE_LEN];
  int power;
};

void addThing(FILE* file) {
    struct thing newThing;

    printf("Enter name (max length %d): ", MAX_NAME_LEN);
    scanf("%s", newThing.name);

    printf("Enter type (max length %d): ", MAX_TYPE_LEN);
    scanf("%s", newThing.type);

    printf("Enter power: ");
    scanf("%d", &newThing.power);

    fwrite(&newThing, sizeof(struct thing), 1, file);
};

void displayAllThings(FILE* file) {
    struct thing currThing;
    int index = 0;

    fseek(file, 0, SEEK_SET);

    printf("All things in file:\n");

    while(fread(&currThing, sizeof(struct thing), 1, file)) {
        printf("%d. %s\t%s\t%d\n", index, currThing.name, currThing.type, currThing.power);
        index++;
    }
};

void removeThing(FILE* file) {
    int index;
    struct thing currThing, nextThing;

    printf("Enter the index of the thing to remove: ");
    scanf("%d", &index);

    fseek(file, index * sizeof(struct thing), SEEK_SET);

    if(fread(&currThing, sizeof(struct thing), 1, file)) {
        fseek(file, (index + 1) * sizeof(struct thing), SEEK_SET);
        
        while(fread(&nextThing, sizeof(struct thing), 1, file)) {
            fseek(file, -2 * sizeof(struct thing), SEEK_CUR);
            fwrite(&nextThing, sizeof(struct thing), 1, file);
            fseek(file, sizeof(struct thing), SEEK_CUR);
        }
        
        int numThings = ftell(file) / sizeof(struct thing);
        ftruncate(fileno(file), (numThings - 1) * sizeof(struct thing));
        
        printf("Thing removed successfully.\n");
    } else {
        printf("Invalid index.\n");
    }
}

int main(int argc, char *argv[]) {
    FILE* file = fopen("things.dat", "ab+");

    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add thing\n");
        printf("2. Display all things\n");
        printf("3. Remove thing\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addThing(file);
                break;
            case 2:
                displayAllThings(file);
                break;
            case 3:
                removeThing(file);
                break;
            case 4:
                fclose(file);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    fclose(file);
    return 0;
};
