#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

#define WORD_SIZE 50

typedef struct 
{   // hash-table entry
    Key_Type element; // only data is the key itself
    enum {empty, in_use, deleted} state;
} cell;

typedef unsigned int Table_size; // type for size-of or index-into hash table

struct table 
{
    cell *cells; Table_size table_size; // cell cells [table_size];
    Table_size num_entries; // number of cells in_use
    // add anything else that you need
	int collisions;
};

// hash function
int hash_func (Key_Type key)
{
	// polynomial-evaluation
	int result = 0;
	int a = 33; // 33, 37, 39, 41 are better according to textbook
	// Horner's rule
	for(int i = 0; i < strlen(key); i++)
	{
		result = i + a * result;
	}
	return result;
}

Table initialize_table (Table_size size) 
{
	Table head = (Table)malloc(sizeof(struct table));
	head->cells = (cell*)malloc(size * sizeof(cell));
	for(int i = 0; i < size; i++)
	{
		head->cells[i].element = NULL;
		head->cells[i].state = empty;
	}
	head->table_size = size;
	head->num_entries = 0;
	head->collisions = 0;
	return head;
}

Table insert (Key_Type new_key, Table head) 
{
	if(head->num_entries == head->table_size)
	{
		printf("Hash table is full.\n");
		return head;
	}
	cell* p = head->cells;
	int index = hash_func(new_key);
	index = index % head->table_size;
	while(p[index].state == in_use)
	{
		index++;
		head->collisions++;
		if(index > head->table_size)
		{
			index = 0;
		}
	}
	p[index].element = (char*)malloc(WORD_SIZE);
	strcpy(p[index].element, new_key);
	p[index].state = in_use;
	head->num_entries++;
	return head;
}

Boolean find (Key_Type new_key, Table head) 
{
	cell* p = head->cells;
	int index = hash_func(new_key);
	index = index % head->table_size;
	int start_point = index;
	while(strcmp(p[index].element, new_key) != 0)
	{
		index++;
		if(index > head->table_size)
		{
			index = 0;
		}
		if(index == start_point)
		{
			return FALSE;
		}
	}
	return TRUE;
}

void print_table (Table head) 
{
	cell* p = head->cells;
	for(int i = 0; i < head->table_size; i++)
	{
		if(p[i].state == in_use)
		{
			printf("index: %d, key: %s\n", i, p[i].element);
		}
	}
}

void print_stats (Table head) 
{
	int avr_collision = head->collisions / head->num_entries;
	printf("total collisions: %d\n", head->collisions);
	printf("average collision per access: %d\n", avr_collision);
}

void tidy (Table head)
{
	cell* p = head->cells;
	for(int i = 0; i < head->table_size; i++)
	{
		if(p[i].state == in_use)
		{
			free(p[i].element);
		}
	}
	free(p);
	free(head);
}