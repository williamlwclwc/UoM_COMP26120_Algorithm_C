#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// A struct to record pairs of strings
typedef struct pair {
  char* first;
  char* second;
} pair;


// processes a work pair by first storing in
// temp a version of work.first that is all
// lowercase and then storing in work.second
// a version where the first character is
// made uppercase 
void process(pair work)
{
  //char* temp = work.first;
  char *temp = (char*)malloc(sizeof(char)*
                             strlen(work.first)+1);
  if(temp == NULL)
  {
    exit(-1);
  }
  // for(int i=0;i<=strlen(work.first)+1;i++){
  //   char c = work.first[i];
  //   if(islower(c)){
  //     temp[i] = c; 
  //   }
  //   if(isupper(c)){
  //     temp[i] = tolower(c);
  //   }
  // }
  int i;
  for(i=0;i<=strlen(work.first);i++){
    char c = work.first[i];
    if(isupper(c)){
      temp[i] = tolower(c);
    }
    else{
      temp[i] = c;                  
    }
  }

  //work.second = (char*)malloc(sizeof(work.first));
  strcpy(work.second,temp);
  int last_space = 1;
  char* ptr = work.second;
  while(*ptr){
    if(last_space){
      *ptr = toupper(*ptr);
    }
    last_space = *ptr == ((char) ' '); 
    ptr++;
  }
  free(temp);
}

// Takes a single string and writes the result to stdout
int main(int argc, char **argv)
{
  if(argc != 2)
  {
    return -1;
  }
  pair work;
  work.first = argv[1];
  work.second = (char*)malloc(sizeof(char)*
                              strlen(work.first)+1);
  if(work.second == NULL)
  {
    return -1;
  }

  process(work);
  
  printf("%s becomes %s\n",work.first,work.second);
  free(work.second);
  
  return 0;
}
