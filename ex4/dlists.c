#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlists.h"

//add a new person's info in the front
person* insert_start(person *people, char* name, int age, int pt, char* info)
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
    if(people!=NULL)
    {
        people->prior = new;
    }
    new->prior = NULL; //the first node's prior should be null
    new->staff_or_student = pt;
    if(pt == student)
    {
        strcpy(new->extraInfo.programme_name, info);
    }
    else if(pt == staff)
    {
        strcpy(new->extraInfo.room_number, info);
    }
    return new;
}

//add a new person's info from the back
person* insert_end(person *people, char* name, int age, int pt, char* info)
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
    new->staff_or_student = pt;
    if(pt == student)
    {
        strcpy(new->extraInfo.programme_name, info);
    }
    else if(pt == staff)
    {
        strcpy(new->extraInfo.room_number, info);
    }
    if(people == NULL)
    {
        //do as insert_start
        new->next = people;
        new->prior = NULL;
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
        new->prior = p;//new node's prior point to the last node
        return people;
    }
}

//add a new person's info into the sorted place
person* insert_sorted(person *people, char* name, int age, int pt, char* info, int (*compare_people)(person* p1, person* p2))
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
    new->staff_or_student = pt;
    if(pt == student)
    {
        strcpy(new->extraInfo.programme_name, info);
    }
    else if(pt == staff)
    {
        strcpy(new->extraInfo.room_number, info);
    }
    if(people == NULL || compare_people(new, people) < 0)
    {
        //do as insert_start
        new->next = people;
        new->prior = NULL;
        if(people != NULL)
        {
            people->prior = new;
        }
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
        if(p->next!=NULL)
        {
            p->next->prior = new;//p->next's prior node is new
        }
        p->next = new;
        new->prior = p;//new node's prior node is p
        return people;
    }
}

//find a node
person* find_node(person* people, char* name)
{
    person *p = people;
    while(p != NULL)
    {
        if(strcmp(p->name, name) == 0)
        {
            printf("%s\n", p->name);
            return p;
        }
        p = p->next;
    }
    return NULL;
}
//delete a node
void delete_node(person* people, char* name)
{
    person* p = find_node(people, name);
    if(p == NULL)
    {
        return;
    }
    //p is at the start
    if(p->prior == NULL)
    {
        people = p->next;
    }
    //p is at the end
    if(p->next == NULL)
    {
        p->prior->next = p->next;
    }
    //p is in the middle
    if(p->prior!= NULL && p->next!= NULL)
    {
        p->prior->next = p->next;
        p->next->prior = p->prior;
    }
    free(p);
}