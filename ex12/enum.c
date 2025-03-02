
// enum - full enumeration of knapsack solutions
// (C) Joshua Knowles

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

FILE *fp;  // file pointer for reading the input files
int Capacity;     // capacity of the knapsack (total weight that can be stored)
int Nitems;    // number of items available
int *item_weights;  // vector of item weights
int *item_values;  // vector of item profits or values
int *temp_indexes;  // list of temporary item indexes for sorting items by value/weight
int QUIET=0; // this can be set to 1 to suppress output

extern void read_knapsack_instance(char *filename);
extern void print_instance();
extern void sort_by_ratio();
extern int check_evaluate_and_print_sol(int *sol,  int *total_value, int *total_weight);
void enumerate();
int next_binary(int *str, int Nitems);

int main(int argc, char *argv[])
{
  read_knapsack_instance(argv[1]);
  print_instance();
  enumerate();
  return(0);
}

void enumerate()
{
  // Do an exhaustive search (aka enumeration) of all possible ways to pack
  // the knapsack.
  // This is achieved by creating every binary solution vector of length Nitems.
  // For each solution vector, its value and weight is calculated.


  int i;  // item index
  int solution[Nitems+1];   // (binary) solution vector representing items packed
  int best_solution[Nitems+1];  // (binary) solution vector for best solution found
  int best_value; // total value packed in the best solution
  int best_weight;
  double j=0;
  float cnt = 1;
  int condition = pow(2, Nitems) / 100 ;
  int total_value, total_weight; // total value and total weight of current knapsack solution
  int infeasible;  // 0 means feasible; -1 means infeasible (violates the capacity constraint)

  // set the knapsack initially empty
  for(i=1;i<=Nitems;i++)
  {
    solution[i]=0;
  }
  QUIET=1;
  best_value=0;
  best_weight=0;

  while(!(next_binary(&solution[1], Nitems)))
  {
    /* ADD CODE IN HERE TO KEEP TRACK OF FRACTION OF ENUMERATION DONE */
    cnt++;
    printf("\r%.0f / %.0f, ", cnt, pow(2, Nitems));
    j = cnt / pow(2, Nitems) * 100;
    if((int)cnt % condition == 0)
    {
      if(round(j) == 100)
      {
        printf("Progress: 100%%, Completed.");
      }
      else
      {
        printf("Progress: %.0f%% [", j);
        for(i = 1; i <= 10; i++)
        {
          if(i > j/10 && i < j/10 + 1)
          {
            printf(">");
          }
          else
          {
            printf("=");
          }
        }
        printf("]\r");
        fflush(stdout);
      }
    }
    // calculates the value and weight and feasibility:
    infeasible=check_evaluate_and_print_sol(solution, &total_value, &total_weight);  
    /* ADD CODE IN HERE TO KEEP TRACK OF BEST SOLUTION FOUND*/

    // check if current solution is the best if it is feasible
    if(!infeasible && total_value > best_value)
    {
      best_value = total_value;
      best_weight = total_weight;
      for(i = 1; i <= Nitems; i++)
      {
        best_solution[i] = solution[i];
      }
    }
  }
  /* ADD CODE TO PRINT OUT BEST SOLUTION */
  printf("\nBest solution is: ");
  for(i = 1; i <= Nitems; i++)
  {
    if(best_solution[i] != 0)
    {
      printf("%d ", i);
    }
  }
  printf("\n");
  printf("Best value is: %d\n", best_value);
  printf("Weight is: %d <= Capacity: %d\n", best_weight, Capacity);

}


int next_binary(int *str, int Nitems)
{
  // Called with a binary string of length Nitems, this 
  // function adds "1" to the string, e.g. 0001 would turn to 0010.
  // If the string overflows, then the function returns 1, else it returns 0.
  int i=Nitems-1;
  while(i>=0)
    {
      if(str[i]==1)
	{
    str[i]=0;
    i--;
	}
      else
	{
    str[i]=1;
    break;
	}
    }
  if(i==-1)
    {
      return(1);
    }
  else
    {
      return(0);
    }
}
