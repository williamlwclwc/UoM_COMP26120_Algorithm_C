#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
    if(argc <= 1)
    {
        //not enough command-line parameters
        printf("Error: expected some command-line parameters\n");
        return 0;
    }
    //currently max length of the parameters, its index in argv, a temporary variable respectively
    int max_len = 0, max_index = 1, temp = 0;
    for(int i = 1; i < argc; i++)
    {
        temp = strlen(argv[i]); //temp to store current argv length
        if(temp > max_len)
        {
            //if current length is longer, assign it(and its index) to max_len(max_index)
            max_len = temp;
            max_index = i;
        }
    }
    printf("%s\n", argv[max_index]);
    return 0;
}
