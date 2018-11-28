#include <stdio.h>
#include <string.h>
#define MAX_LEN 80

typedef struct node
{
    int type; // 0 for question, 1 for object
    char obj[MAX_LEN];
    char question[MAX_LEN];
    struct node *yes, *no;
} node;

// (diagnostic) print out status of a single node
void nodePrint(node *p)
{
    if(p->type == 0)
    {
        // it is a question node
        printf("Qbject: \n");
        printf("Question: %s\n", p->question);
        if(p->yes->type == 0)
        {
            printf("Yes: %s\n", p->yes->question);
        }
        else
        {
            printf("Yes: %s\n", p->yes->obj);
        }
        if(p->no->type == 0)
        {
            printf("No: %s\n", p->no->question);
        }
        else
        {
            printf("No: %s\n", p->no->obj);
        }
    }
    else
    {
        // it is a object node
        printf("Object: %s\n", p->obj);
        printf("Question: \n");
    }
}

// print a tree based on root node
void treePrint(node *p)
{
    if(p != NULL)
    {
        nodePrint(p);
        if(p->type != 1)
        {
            treePrint(p->yes);
            treePrint(p->no);
        }
    }
}

int main()
{
    // build a 7 nodes tree for part1
    node part1[7];
    // int num;
    // for(int i = 0; i < 7; i++)
    // {
    //     scanf("%d", &part1[i].type);
    //     getchar();
    //     printf("%d\n", part1[i].type);
    //     gets(part1[i].obj);
    //     printf("%s\n", part1[i].obj);
    //     gets(part1[i].question);
    //     printf("%s\n", part1[i].question);
    //     scanf("%d", &num);
    //     getchar();
    //     if(num != -1)
    //     {
    //         part1[i].yes = &part1[num];
    //     }
    //     scanf("%d", &num);
    //     getchar();
    //     if(num != -1)
    //     {
    //         part1[i].no = &part1[num];
    //     }
    // }
    part1[0].type = 0;
    strcpy(part1[0].obj, "");
    strcpy(part1[0].question, "Does it have a tail?");
    part1[0].yes = &part1[1];
    part1[0].no = &part1[2];

    part1[1].type = 1;
    strcpy(part1[1].obj, "pangolin");
    strcpy(part1[1].question, "");
    
    part1[2].type = 0;
    strcpy(part1[2].obj, "");
    strcpy(part1[2].question, "Is it flat, round and edible？");
    part1[2].yes = &part1[3];
    part1[2].no = &part1[4];

    part1[3].type = 0;
    strcpy(part1[3].obj, "");
    strcpy(part1[3].question, "Can you dip it in your tea?");
    part1[3].yes = &part1[5];
    part1[3].no = &part1[6];

    part1[4].type = 1;
    strcpy(part1[4].obj, "Pete");
    strcpy(part1[4].question, "");
    
    part1[5].type = 1;
    strcpy(part1[5].obj, "a biscuit");
    strcpy(part1[5].question, "");
    
    part1[6].type = 1;
    strcpy(part1[6].obj, "a pizza");
    strcpy(part1[6].question, "");
    
    treePrint(part1);
    return 0;
}