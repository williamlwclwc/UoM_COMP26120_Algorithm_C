#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrays.h"

/* declare your struct for a person here */
typedef struct person{
  char *name;
  int age;
} person;

static void insert(person* people[], char *name, int age, int *nextinsert) 
{
  /* put name and age into the next free place in the array parameter here */
  people[*nextinsert]->name = (char*)malloc(strlen(name)+1);
  if(people[*nextinsert]->name == NULL)
  {
    printf("not enough memory\n");
    exit(-1);
  }
  strcpy(people[*nextinsert]->name, name);
  people[*nextinsert]->age = age;
  /* modify nextfreeplace here */
  (*nextinsert)++;
}

int main(int argc, char **argv) 
{

  /* declare the people array here */
  person *people[HOW_MANY];
  int nextinsert = 0;
  for (int i = 0; i < HOW_MANY; i++ ) 
  {
    people[i] = (person*)malloc(sizeof(person));
    if(people[i] == NULL)
    {
      printf("not enough memory\n");
      return -1;
    }
    insert (people, names[i], ages[i], &nextinsert);
  }

  /* print the people array here*/
  for(int i = 0; i < HOW_MANY; i++)
  {
    printf("No.%d: name: %s age: %d\n", 
            i+1, people[i]->name, people[i]->age);
  }

  //free malloc memory
  for(int i = 0; i < HOW_MANY; i++)
  {
    free(people[i]->name);
    free(people[i]);
  }
  return 0;
}
