/* declare your struct for a person here */
typedef struct person{
    char name[20];
    int age;
    struct person *next;
} person;

extern person* insert_start(person *people, char* name, int age);
extern person* insert_end(person *people, char* name, int age);
extern person* insert_sorted(person *people, char* name, int age, int (*compare_people)(person* p1, person* p2));