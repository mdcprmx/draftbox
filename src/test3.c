#include <stdio.h>

struct student {
    char name[50];
    int roll;
    float marks;
};

void display(struct student* student_obj) {
    printf("Name: %s\n", student_obj->name);
    printf("Roll: %d\n", student_obj->roll);
    printf("Marks: %.2f\n", student_obj->marks);
}

int main() {
    struct student peremennaya = {"Boiiii", 25, 3.7};
    struct student obj2 = {"Petrovich", 54, 1.2};
    display(&peremennaya);
    printf("\n");
    display(&obj2);
    return 0;
}