#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "slists.h"
#include "printing.h"
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
            people = insert_start(people, names[i], ages[i], person_type[i], info[i]);
        }
    }
    else if(strcmp(argv[1], "insert_end") == 0)
    {
        for (int i = 0; i < HOW_MANY; i++)
        {
            //call insert function and pass the address of nextinsert
            people = insert_end(people, names[i], ages[i], person_type[i], info[i]);
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
            people = insert_sorted(people, names[i], ages[i], person_type[i], info[i],compare_people);
        }
    }
    /* print the people array here*/
    person* p = people;
    while(p != NULL)
    {
        printData(p);
        p = p->next;
    }

    //free malloc memory
    p = people;
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