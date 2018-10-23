#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

/* declare your struct for a person here */
typedef struct person{
    char name[20];
    int age;
    struct person *next;
} person;

//function: printdata
void printData(person* people)
{
    int i = 0;
    while(people != NULL)
    {
        printf("Name: %s, age: %d\n", people->name, people->age);
        people = people->next;
        i++;
    }
}

//add a new person's info in the front
static person* insert_start(person *people, char* name, int age)
{
    person* new = (person*)malloc(sizeof(person));
    if(new == NULL)
    {
        //not enough space
        exit(-1);
    }
    strcpy(new->name, name);
    new->age = age;
    new->next = people;
    return new;
}

//add a new person's info from the back
static person* insert_end(person *people, char* name, int age)
{
    person* new = (person*)malloc(sizeof(person));
    person* p = NULL;
    if(new == NULL)
    {
        //not enough space
        exit(-1);
    }
    strcpy(new->name, name);
    new->age = age;
    if(people == NULL)
    {
        //do as insert_start
        new->next = people;
        return new;
    }
    else
    {
        p = people;
        while(p->next!=NULL)
        {
            p = p->next;
        }
        p->next = new;
        return people;
    }
}

//function pointer
int (*compare_people)(person* p1, person* p2);
//compare the name of two person
int compare_people_by_name(person* p1, person* p2)
{
    return strcmp(p1->name, p2->name);
}
//compare the age of two person
int compare_people_by_age(person* p1, person* p2)
{
    if(p1->age > p2->age)
    {
        return 1;
    }
    else if(p1->age < p2->age)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
//add a new person's info into the sorted place
static person* insert_sorted(person *people, char* name, int age, int (*compare_people)(person* p1, person* p2))
{
    person* new = (person*)malloc(sizeof(person));
    person* p = NULL;
    if(new == NULL)
    {
        //not enough space
        exit(-1);
    }
    strcpy(new->name, name);
    new->age = age;
    if(people == NULL || compare_people(new, people) < 0)
    {
        //do as insert_start
        new->next = people;
        return new;
    }
    else
    {
        p = people;
        while(p->next!=NULL && compare_people(p->next, new) <= 0)
        {
            p = p->next;
        }
        new->next = p->next;
        p->next = new;
        return people;
    }
}

int main(int argc, char **argv)
{
    //take command line arguments
    if(argc > 3)
    {
        //number of parameters is wrong
        return -1;
    }
    if(argc == 2)
    {
        if(strcmp(argv[1], "insert_start") != 0
           && strcmp(argv[1], "insert_end") != 0
           && strcmp(argv[1], "insert_sorted") != 0)
        {
            //input error
            return -1;
        }
    }
    if(argc == 3)
    {
        if(strcmp(argv[1], "insert_sorted") != 0)
        {
            //input error
            return -1;
        }
        if(strcmp(argv[2], "name") != 0 && strcmp(argv[2], "age") != 0)
        {
            //input error
            return -1;
        }
    }
    /* declare the people list here */
    person *people = NULL;
    if(argc == 1 || strcmp(argv[1], "insert_start") == 0)
    {
        for (int i = 0; i < HOW_MANY; i++)
        {
            //call insert function and pass the address of nextinsert
            people = insert_start(people, names[i], ages[i]);
        }
    }
    else if(strcmp(argv[1], "insert_end") == 0)
    {
        for (int i = 0; i < HOW_MANY; i++)
        {
            //call insert function and pass the address of nextinsert
            people = insert_end(people, names[i], ages[i]);
        }
    }
    else if(strcmp(argv[1], "insert_sorted") == 0)
    {
        if(argc==2 || strcmp(argv[2], "name") == 0)
        {
            compare_people = &compare_people_by_name;
        }
        else
        {
            compare_people = &compare_people_by_age;
        }
        for (int i = 0; i < HOW_MANY; i++ )
        {
            //call insert function and pass the address of nextinsert
            people = insert_sorted(people, names[i], ages[i], compare_people);
        }
    }
    /* print the people array here*/
    printData(people);

    //free malloc memory
    person* p = people;
    person* p_free = NULL;
    while(p != NULL)
    {
        //have to free p after store the next, or you may lose the address of next
        p_free = p;
        p = p->next;
        free(p_free);
    }
    return 0;
}
