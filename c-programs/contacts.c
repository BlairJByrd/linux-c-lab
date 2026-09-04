#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
};

int main() {
    struct Person p;
    printf("Enter name: ");
    scanf("%s", p.name);
    printf("Enter age: ");
    scanf("%d", &p.age);

    FILE *file = fopen("contacts.txt", "a");
    fprintf(file, "%s, %d\n", p.name, p.age);
    fclose(file);

    printf("Contact added. Current contacts:\n");
    FILE *readFile = fopen("contacts.txt", "r");
    char line[100];
    while (fgets(line, sizeof(line), readFile)) {
        printf("%s", line);
    }
    fclose(readFile);
    return 0;
}
