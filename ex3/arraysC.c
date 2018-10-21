#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrays.h"

/* declare your struct for a person here */
typedef struct person{
  char *name;
  int age;
} person;

static void insert(person* people[], char *name, int age) 
{
  static int nextfreeplace = 0;
  /* put name and age into the next free place in the array parameter here */
  people[nextfreeplace]->name = (char*)malloc(strlen(name)+1);
  if(people[nextfreeplace]->name == NULL)
  {
    printf("not enough memory\n");
    exit(-1);
  }
  strcpy(people[nextfreeplace]->name, name);
  people[nextfreeplace]->age = age;
  /* modify nextfreeplace here */
  nextfreeplace++;
}

int main(int argc, char **argv) 
{

  /* declare the people array here */
  person *people[HOW_MANY];

  for (int i = 0; i < HOW_MANY; i++ ) 
  {
    people[i] = (person*)malloc(sizeof(person));
    if(people[i] == NULL)
    {
      printf("not enough memory\n");
      return -1;
    }
    insert (people, names[i], ages[i]);
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
