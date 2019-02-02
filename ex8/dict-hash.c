#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

#define WORD_SIZE 50
#define AUTO_REHASH 1
enum {poly, lin_hash};
enum {linear, quadratic, clear, double_hash};

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
	float collisions;
};

Table_size hash_func (Key_Type key, int type);
Table_size compress_func (Table_size index, Table_size table_size);
Table_size collision_func(Table_size index, int type, Table_size hash2);

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
	// select the hash and probing method
	int hash_type = poly, probing_type = double_hash;
	if(mode == 4)
	{
		hash_type = lin_hash;
		probing_type = quadratic;
	}
	else if(mode == 3)
	{
		hash_type = poly;
		probing_type = linear;
	}
	else if(mode == 2)
	{
		hash_type = poly;
		probing_type = quadratic;
	}
	else if(mode == 1)
	{
		hash_type = poly;
		probing_type = double_hash;
	}
	if(head->num_entries == head->table_size)
	{
		printf("Hash table is full.\n");
		// exit or rehash
		exit(0);
	}
	cell* p = head->cells;
	Table_size index = hash_func(new_key, hash_type);
	// cal double hash
	Table_size index0 = index;
	int q = 7;
	if(head->table_size <= 5) q = 2;
	if(head->table_size <= 7) q = 5;
	index0 = q - index0 % q;
	index = compress_func(index, head->table_size);
	// clear static variable before probing
	if(probing_type == quadratic || probing_type == double_hash)
	{
		collision_func(index, clear, index0);
	}
	while(p[index].state == in_use)
	{
		// check duplicate
		if(strcmp(p[index].element, new_key) == 0)
		{
			return head;
		}
		index = collision_func(index, probing_type, index0);
		head->collisions++;
		if(index >= head->table_size)
		{
			index = compress_func(index, head->table_size);
		}
	}
	p[index].element = (char*)malloc(WORD_SIZE);
	strcpy(p[index].element, new_key);
	p[index].state = in_use;
	head->num_entries++;
	// check rehash
	if(AUTO_REHASH && (double)head->num_entries / head->table_size > 0.75)
	{
		// rehash when used / total > 0.75
		Table_size new_size = head->table_size * 2;
		Table new_head = initialize_table(new_size);
		int i = 0, cnt = 0;
		p = head->cells;
		while(cnt < head->num_entries)
		{
			if(p[i].state == in_use)
			{
				new_head = insert(p[i].element, new_head);
				cnt++;
			}
			i++;
		}
		tidy(head);
		head = new_head;
	}
	return head;
}

Boolean find (Key_Type new_key, Table head) 
{
	int hash_type = poly, probing_type = double_hash;
	if(mode == 4)
	{
		hash_type = lin_hash;
		probing_type = quadratic;
	}
	else if(mode == 3)
	{
		hash_type = poly;
		probing_type = linear;
	}
	else if(mode == 2)
	{
		hash_type = poly;
		probing_type = quadratic;
	}
	else if(mode == 1)
	{
		hash_type = poly;
		probing_type = double_hash;
	}
	cell* p = head->cells;
	Table_size index = hash_func(new_key, hash_type);
	// cal double hash
	Table_size index0 = index;
	int q = 7;
	if(head->table_size <= 5) q = 2;
	if(head->table_size <= 7) q = 5;
	index0 = q - index0 % q;
	index = compress_func(index, head->table_size);
	Table_size start_point = index;
	// if hash result is empty, then not found
	if(p[index].state == empty)
	{
		return FALSE;
	}
	while(strcmp(p[index].element, new_key) != 0)
	{
		index = collision_func(index, probing_type, index0);
		if(index >= head->table_size)
		{
			index = compress_func(index, head->table_size);
		}
		// probing all or reach empty
		if(index==start_point || p[index].state == empty)
		{
			if(probing_type == quadratic || probing_type == double_hash)
			{
				collision_func(index, clear, index0);
			}
			return FALSE;
		}
	}
	// found a match
	if(probing_type == quadratic || probing_type == double_hash)
	{
		collision_func(index, clear, index0);
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
	float avr_collision = head->collisions / head->num_entries;
	printf("current table size: %d\n", head->table_size);
	printf("total collisions: %.0f\n", head->collisions);
	printf("average collision per access: %.3f\n", avr_collision);
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

// hash function
Table_size hash_func (Key_Type key, int type)
{
	// polynomial-evaluation
	int result = 0;
	if(type == poly)
	{
		int a = 33; // 33, 37, 39, 41 are better according to textbook
		// Horner's rule
		for(int i = 0; i < strlen(key); i++)
		{
			result = (int)key[i] + a * result;
		}
	}
	if(type == lin_hash)
	{
		int a = 33, b = 37;
		for(int i = 0; i < strlen(key); i++)
		{
			result = (int)key[i];
		}
		result = a*result+b;
	}
	return result;
}

// compress function
Table_size compress_func (Table_size index, Table_size table_size)
{
	// modular division
	index = index % table_size;
	return index;
}

// collision handle function
Table_size collision_func(Table_size index, int type, Table_size hash2)
{
	static int j; // for quadratic & double hash
	static int index2;
	//int q = 5; // a prime number
	// linear probing
	if(type == linear)
	{
		index++;
	}
	// quadratic probing
	else if(type == quadratic)
	{
		j++;
		index = index - index2;
		index2 = j*j;
		index = index + index2;
	}
	else if(type == clear)
	{
		j = 0;
		index2 = 0;
	}
	else if(type == double_hash)
	{
		j++;
		index = index - index2;
		// double hash
		//index2 = j*(q-(index0 % q));
		index2 = j * hash2;
		index = index + index2;
	}
	return index;
}