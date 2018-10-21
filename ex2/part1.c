#include <stdio.h>
#include <ctype.h>
#define MAX_FILENAME_LENGTH 20
int main()
{
    char filename_input[MAX_FILENAME_LENGTH]; //name string of input file
    char filename_output[MAX_FILENAME_LENGTH]; //name string of output file
    scanf("%s", filename_input); //input input_file name from standard input
    scanf("%s", filename_output); //input output_file name from standard input

    //read string from file
    FILE *fp_read = NULL, *fp_out = NULL;
    fp_read = fopen(filename_input, "r");
    if(fp_read == NULL)
    {
        return 0;
    }

    //output to file
    fp_out = fopen(filename_output, "w");
    if(fp_out == NULL)
    {
        return 0;
    }
    
    int i = 0, to_up = 0, to_low = 0; //set up counters
    char c;
    c = fgetc(fp_read);
    while(c != EOF)
    {
        if(c>= 'a' && c<= 'z')
        {
            //to upper case
            c = toupper(c);
            fprintf(fp_out, "%c", c);
            to_up++;
        }
        else if(c>= 'A' && c<= 'Z')
        {
            //to lower case
            c = tolower(c);
            fprintf(fp_out, "%c", c);
            to_low++;
        }
        else
        {
            fprintf(fp_out, "%c", c);
        }
        i++;
        c = fgetc(fp_read);
    }

    printf("Read %d characters in total, %d converted to upper-case, %d to lower-case\n", i, to_up, to_low);

    //fprintf(fp, "Read %d characters in total, %d converted to upper-case, %d to lower-case", i, to_up, to_low);
    fclose(fp_read);
    fclose(fp_out);
}
