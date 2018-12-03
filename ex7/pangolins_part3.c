#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 80

typedef struct node
{
    int type; // 0 for question, 1 for object
    char *obj;
    char *question;
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

void nodePrintToFile(FILE* fp, node *p)
{
    if(p->type == 0)
    {
        // it is a question node
        fprintf(fp, "%d\n", p->type);
        fprintf(fp, "%s\n", p->question);
    }
    else
    {
        // it is a object node
        fprintf(fp, "%d\n", p->type);
        fprintf(fp, "%s\n", p->obj);
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

// print a tree into a txt file
void treePrintToFile(FILE* fp, node *p)
{
    if(p != NULL)
    {
        nodePrintToFile(fp, p);
        if(p->type != 1)
        {
            treePrintToFile(fp, p->yes);
            treePrintToFile(fp, p->no);
        }
    }
}

// load a tree from a file
node* treeLoadFromFile(FILE *fp)
{
    int type = -1;
    int len = 0;
    if(fscanf(fp, "%d", &type) == 0)
    {
        return NULL;
    }
    fgetc(fp);
    node* root = (node*)malloc(sizeof(node));
    if(type == 0)
    {
        root->type = 0;
        root->question = (char*)malloc(MAX_LEN);
        fgets(root->question, MAX_LEN, fp);
        len = strlen(root->question);
        if(root->question[len-1] == '\n')
        {
            root->question[len-1] = '\0';
        }
        root->obj = NULL;
        root->yes = treeLoadFromFile(fp);
        root->no = treeLoadFromFile(fp);
    }
    else
    {
        root->type = 1;
        root->obj = (char*)malloc(MAX_LEN);
        fgets(root->obj, MAX_LEN, fp);
        len = strlen(root->obj);
        if(root->obj[len-1] == '\n')
        {
            root->obj[len-1] = '\0';
        }
        root->question = NULL;
        root->yes = NULL;
        root->no = NULL;
    }
    return root;
}

// free a tree node memory
void freeTree(node *p)
{
    node* temp_yes = NULL;
    node* temp_no = NULL;
    if(p != NULL)
    {
        if(p->type == 0)
        {
            temp_yes = p->yes;
            temp_no = p->no;
            free(p->question);
            free(p);
            freeTree(temp_yes);
            freeTree(temp_no);
        }
        else
        {
            free(p->obj);
            free(p);
        }
    }
}

// check if answer is Yes
int check_yes(char* reply)
{
    if(strcmp(reply, "Yes") == 0 || \
    strcmp(reply, "yes") == 0 || \
    strcmp(reply, "y") == 0 || \
    strcmp(reply, "correct") == 0 || \
    strcmp(reply, "Correct") == 0 || \
    strcmp(reply, "absolutely") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// check if answer is No
int check_no(char* reply)
{
    if(strcmp(reply, "No") == 0 || \
    strcmp(reply, "no") == 0 || \
    strcmp(reply, "n") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// when program starts
node* on_start()
{
    char reply[MAX_LEN];
    char filename[MAX_LEN];
    int len = 0;
    FILE *fp;
    node *root = NULL;
    while(1)
    {
        printf("Do you wish to load the game?\n");
        fgets(reply, MAX_LEN, stdin);
        len = strlen(reply);
        if(reply[len-1] == '\n')
        {
            reply[len-1] = '\0';
        }
        if(check_yes(reply))
        {
            printf("Input the name of the file:\n");
            fgets(filename, MAX_LEN, stdin);
            fp = fopen(filename, "r");
            if(fp != NULL)
            {
                root = treeLoadFromFile(fp);
                fclose(fp);
                if(root != NULL)
                {
                    break; // file is not empty
                }
            }
            printf("The file is not working, please try again.\n");
        }
        else if(check_no(reply))
        {
            // initialise the tree: one object
            root = (node*)malloc(sizeof(node));
            root->type = 1;
            root->obj = (char*)malloc(MAX_LEN);
            strcpy(root->obj, "pangolin");
            root->question = NULL;
            root->yes = NULL;
            root->no = NULL;
            break;
        }
        else
        {
            printf("Reply error. You should answer Yes or No.\n");
        }
    }
    return root;
}

// when program ends
void on_end(node *current)
{
    char reply[MAX_LEN];
    char filename[MAX_LEN];
    FILE *fp;
    int len = 0;
    while(1)
    {
        printf("Do you wish to save your game?\n");
        fgets(reply, MAX_LEN, stdin);
        len = strlen(reply);
        if(reply[len-1] == '\n')
        {
            reply[len-1] = '\0';
        }
        if(check_yes(reply))
        {
            printf("Input the name of the file:\n");
            fgets(filename, MAX_LEN ,stdin);
            fp = fopen(filename, "w+");
            if(fp != NULL)
            {
                treePrintToFile(fp, current);
                fclose(fp);
                printf("Progress saved. Bye.\n");
                break;
            }
            printf("The file is not working, please try again. \n");
        }
        else if(check_no(reply))
        {
            printf("Ok. Bye.\n");
            break;
        }
        else
        {
            printf("Reply error. You should answer Yes or No.\n");
        }
    }
}

int main()
{
    node* first_question = NULL;
    char reply[MAX_LEN];
    int len = 0;
    int game_continue = 1; // 1 for another round
    int pre_index = 0; // find previous node: 0 for no, 1 for yes
    node* previous = NULL; 

    // program starts
    node* current = on_start();
    if(current->type == 0)
    {
        first_question = current;
    }
    printf("OK, please think of something.\n");
    // while not finished
    while(game_continue)
    {
        while(1)
        {
            // is leaf node(object)?
            if(current->type == 1)
            {
                // make the guess
                printf("Is is a %s?\n", current->obj);
                while(1)
                {
                    fgets(reply, MAX_LEN, stdin);
                    len = strlen(reply);
                    if(reply[len-1] == '\n')
                    {
                        reply[len-1] = '\0';
                    }
                    if(check_yes(reply))
                    {
                        // computer has won
                        printf("Good. That was soooo easy.\n");
                        if(first_question != NULL)
                        {
                            current = first_question;
                        }
                        break;
                    }
                    else if(check_no(reply))
                    {
                        // user has won
                        printf("Oh. Well, you win then -- What were you thinking of?\n");
                        // ask obj-name & question and create new nodes
                        node* obj = (node*)malloc(sizeof(node));
                        if(obj == NULL)
                        {
                            exit(-1);
                        }
                        obj->type = 1;
                        obj->obj = (char*)malloc(MAX_LEN);
                        if(obj->obj == NULL)
                        {
                            exit(-1);
                        }
                        fgets(obj->obj, MAX_LEN, stdin);
                        len = strlen(obj->obj);
                        if(obj->obj[len-1] == '\n')
                        {
                            obj->obj[len-1] = '\0';
                        }
                        obj->question = NULL;
                        obj->yes = NULL;
                        obj->no = NULL;
                        printf("Please give me a question about %s?\n", obj->obj);
                        node* question = (node*)malloc(sizeof(node));
                        if(question == NULL)
                        {
                            exit(-1);
                        }
                        question->type = 0;
                        question->question = (char*)malloc(MAX_LEN);
                        if(question->question == NULL)
                        {
                            exit(-1);
                        }
                        fgets(question->question, MAX_LEN, stdin);
                        len = strlen(question->question);
                        if(question->question[len-1] == '\n')
                        {
                            question->question[len-1] = '\0';
                        }
                        question->obj = NULL;
                        question->yes = NULL;
                        question->no = NULL;
                        printf("What is the answer for %s?\n", obj->obj);
                        while(1)
                        {
                            fgets(reply, MAX_LEN, stdin);
                            len = strlen(reply);
                            if(reply[len-1] == '\n')
                            {
                                reply[len-1] = '\0';
                            }
                            // insert new obj node
                            if(check_yes(reply))
                            {
                                question->yes = obj;
                                question->no = current;
                                break;
                            }
                            else if(check_no(reply))
                            {
                                question->no = obj;
                                question->yes = current;
                                break;
                            }
                            else
                            {
                                printf("Reply error. You should answer Yes or No.\n");
                            }
                        }
                        // insert new question node
                        if(previous != NULL)
                        {
                            if(pre_index == 1)
                            {
                                previous->yes = question;
                            }
                            else
                            {
                                previous->no = question;
                            }
                        }
                        else
                        {
                            // the first time user win, record the new root
                            first_question = question;
                        }
                        printf("Thanks.\n");
                        current = first_question; // ready for another round
                        break;
                    }
                    else
                    {
                        printf("Reply error. You should answer Yes or No.\n");
                    }
                }
                // finished
                break;
            }
            else
            {
                // question mode
                // ask the question
                printf("%s\n", current->question);
                // set current node to yes/no
                while(1)
                {
                    fgets(reply, MAX_LEN, stdin);
                    len = strlen(reply);
                    if(reply[len-1] == '\n')
                    {
                        reply[len-1] = '\0';
                    }
                    if(check_yes(reply))
                    {
                        previous = current;
                        pre_index = 1;
                        current = current->yes;
                        break;
                    }
                    else if(check_no(reply))
                    {
                        previous = current;
                        pre_index = 0;
                        current = current->no;
                        break;
                    }
                    else
                    {
                        printf("Reply error. You should answer Yes or No.\n");
                    }
                }
            }
        }
        // another round?
        printf("Would you like to play again?\n");
        while(1)
        {
            fgets(reply, MAX_LEN, stdin);
            len = strlen(reply);
            if(reply[len-1] == '\n')
            {
                reply[len-1] = '\0';
            }
            if(check_yes(reply))
            {
                printf("OK. Let's play another round.\n");
                break;
            }
            else if(check_no(reply))
            {
                game_continue = 0;
                printf("See you then.\n");
                break;
            }
            else
            {
                printf("Reply error. You should answer Yes or No.\n");
            }
        }
    }
    on_end(current);
    // free the tree memory
    freeTree(current);
    return 0;
}