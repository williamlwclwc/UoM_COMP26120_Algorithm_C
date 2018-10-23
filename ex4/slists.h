enum staff_or_student
{
    staff = 0,
    student = 1,
    neither = 2
};

union info
{
    char room_number[40];
    char programme_name[40];
};

/* declare your struct for a person here */
typedef struct person{
    char name[20];
    int age;
    int staff_or_student;
    union info extraInfo;
    struct person *next;
} person;


extern person* insert_start(person *people, char* name, int age, int pt, char* info);
extern person* insert_end(person *people, char* name, int age, int pt, char* info);
extern person* insert_sorted(person *people, char* name, int age, int pt, char* info, int (*compare_people)(person* p1, person* p2));