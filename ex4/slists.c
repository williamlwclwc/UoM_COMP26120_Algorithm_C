#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slists.h"

//add a new person's info in the front
person* insert_start(person *people, char* name, int age) 
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
person* insert_end(person *people, char* name, int age) 
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

//add a new person's info into the sorted place
person* insert_sorted(person *people, char* name, int age, int (*compare_people)(person* p1, person* p2)) 
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
        while(p->next!=NULL && compare_people(p->next, new) < 0)
        {
            p = p->next;
        }
        new->next = p->next;
        p->next = new;
        return people;
    }
}