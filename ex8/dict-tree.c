#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

#define WORD_SIZE 50

typedef struct node *tree_ptr;
struct node 
{
  Key_Type element; // only data is the key itself
  tree_ptr left, right;
  // add anything else that you need
  tree_ptr parent;
  int avl_height; // height info needed by avl
};

struct table 
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
};

void free_tree (tree_ptr p);
int calDepth(tree_ptr p);

int max(int a, int b)
{
	if(a >= b)
		return a;
	else
		return b;
}

Table initialize_table(/*ignore parameter*/) 
{
	//initialize the pointer to the root node
	Table root = (Table)malloc(sizeof(struct table));
	root->head = NULL;
	return root;
}

// avl tree rotation
tree_ptr left_left_rotation(tree_ptr parent)
{
	tree_ptr new_parent = parent->left;
	// adjust parent pointers
	new_parent->parent = parent->parent;
	new_parent->right->parent = parent;
	parent->parent = new_parent;
	// adjust children pointers
	parent->left = new_parent->right; // parent->left points to new->right
	new_parent->right = parent; // let new be the parent
	// adjust height
	parent->avl_height = max(parent->left->avl_height, parent->right->avl_height) + 1;
	new_parent->avl_height = max(new_parent->left->avl_height, new_parent->right->avl_height) + 1;
	return new_parent;
}

tree_ptr right_right_rotation(tree_ptr parent)
{
	tree_ptr new_parent = parent->right;
	// adjust parent pointers
	new_parent->parent = parent->parent;
	new_parent->left->parent = parent;
	parent->parent = new_parent;
	// adjust children pointers
	parent->right = new_parent->left;
	new_parent->left = parent;
	// adjust height
	parent->avl_height = max(parent->left->avl_height, parent->right->avl_height) + 1;
	new_parent->avl_height = max(new_parent->left->avl_height, new_parent->right->avl_height) + 1;
	return new_parent;
}

tree_ptr left_right_rotation(tree_ptr parent)
{
	parent->left = right_right_rotation(parent->left);
	return left_left_rotation(parent);
}

tree_ptr right_left_rotation(tree_ptr parent)
{
	parent->right = left_left_rotation(parent->right);
	return right_right_rotation(parent);
}

Table insert(Key_Type new_key,Table root) 
{
	/* you can define and call another function  
	 that passes and returns the head of the tree*/

	// if Table is empty
	if(root->head == NULL)
	{
		tree_ptr new = (tree_ptr)malloc(sizeof(struct node));
		if(new == NULL) exit(-1);
		new->element = (char*)malloc(WORD_SIZE);
		if(new->element == NULL) exit(-1);
		strcpy(new->element, new_key);
		// create NULL_NODE objects
		tree_ptr new_empty1 = (tree_ptr)malloc(sizeof(struct node));
		if(new_empty1 == NULL) exit(-1);
		new_empty1->element = NULL;
		new_empty1->left = NULL;
		new_empty1->right = NULL;
		new_empty1->parent = new;
		tree_ptr new_empty2 = (tree_ptr)malloc(sizeof(struct node));
		if(new_empty2 == NULL) exit(-1);
		new_empty2->element = NULL;
		new_empty2->left = NULL;
		new_empty2->right = NULL;
		new_empty2->parent = new;
		new->left = new_empty1;
		new->right = new_empty2;
		new->parent = NULL;
		// cal height
		new->avl_height = 1;
		new_empty1->avl_height = 0;
		new_empty2->avl_height = 0;
		root->head = new;
		return root;
	}

	// check duplicate
	if(find(new_key, root))
	{
		return root;
	}
	// find the right place(a NULL_NODE node) for new_key
	tree_ptr p = root->head;
	while(p->element != NULL)
	{
		if(strcmp(new_key, p->element) > 0)
		{
			p = p->right;
		}
		else
		{
			p = p->left;
		}
	}
	// set the new node
	p->element = (char*)malloc(WORD_SIZE);
	if(p->element == NULL) exit(-1);
	strcpy(p->element, new_key);
	tree_ptr new_empty1 = (tree_ptr)malloc(sizeof(struct node));
	if(new_empty1 == NULL) exit(-1);
	new_empty1->element = NULL;
	new_empty1->left = NULL;
	new_empty1->right = NULL;
	new_empty1->parent = p;
	new_empty1->avl_height = 0;
	tree_ptr new_empty2 = (tree_ptr)malloc(sizeof(struct node));
	if(new_empty2 == NULL) exit(-1);
	new_empty2->element = NULL;
	new_empty2->left = NULL;
	new_empty2->right = NULL;
	new_empty2->parent = p;
	new_empty1->avl_height = 0;
	p->left = new_empty1;
	p->right = new_empty2;
	if(mode == 1)
	{
		// ordered balanced tree / binary search tree
		return root;
	}
	else if(mode == 2)
	{
		tree_ptr parent = p;
		tree_ptr last_parent; 
		while(parent != NULL)
		{
			// avl tree auto balance
			if(strcmp(new_key, parent->element) <= 0)
			{
				// insert into left child
				if(parent->left->avl_height-parent->right->avl_height > 1)
				{
					// lose balance
					if(strcmp(new_key, parent->left->element) < 0)
					{
						// left left rotation
						parent = left_left_rotation(parent);
					}
					else
					{
						// left right rotation
						parent = left_right_rotation(parent);
					}
					if(parent->parent != NULL)
					{
						if(strcmp(parent->element, parent->parent->element) > 0)
							parent->parent->right = parent;
						else
							parent->parent->left = parent;
					}
				}
			}
			else
			{
				// insert into right child
				if(parent->right->avl_height-parent->left->avl_height > 1)
				{
					// lose balance
					if(strcmp(new_key, parent->right->element) > 0)
					{
						// right right rotation
						parent = right_right_rotation(parent);
					}
					else
					{
						// right left rotation
						parent = right_left_rotation(parent); 
					}
					if(parent->parent != NULL)
					{
						if(strcmp(parent->element, parent->parent->element) > 0)
							parent->parent->right = parent;
						else
							parent->parent->left = parent;
					}
				}
			}
			last_parent = parent;
			parent->avl_height = max(parent->left->avl_height, parent->right->avl_height) + 1;
			parent = parent->parent;
		}
		if(parent == NULL)
		{
			root->head = last_parent;
		}
		return root;
	}
	else
	{
		printf("mode error.\n");
		exit(-1);
	}
}

Boolean find(Key_Type target, Table root) 
{
	/* you can define and call another function  
	 that passes the head of the tree*/
	
	// ordered balanced tree / binary search tree
	if(root == NULL || root->head == NULL)
	{
		return FALSE;
	}
	tree_ptr p = root->head;
	while(p->element != NULL)
	{
		if(strcmp(target, p->element) > 0)
		{
			p = p->right;
		}
		else if(strcmp(target, p->element) < 0)
		{
			p = p->left;
		}
		else
		{
			return TRUE;
		}
	}
	return FALSE;
}

void print_table(Table root) 
{
	/* you can define and call another function
	 that passes the head of the tree*/

	// preorder
	if(root == NULL || root->head == NULL)
	{
		printf("Table is empty\n");
		return;
	}
	tree_ptr p = root->head;
	if(p->element != NULL)
	{
		printf("%s\n", p->element);
		Table left = (Table)malloc(sizeof(struct table));
		if(left == NULL) exit(-1);
		left->head = p->left;
		Table right = (Table)malloc(sizeof(struct table));
		if(right == NULL) exit(-1);
		right->head = p->right;
		print_table(left);
		free(left);
		print_table(right);
		free(right);
	}
}

int calDepth(tree_ptr p)
{
	int leftDepth = 0, rightDepth = 0;
	if(p == NULL)
	{
		return -1;
	}
	if(p->left == NULL)
	{
		leftDepth = -1;
	}
	else
	{
		leftDepth = calDepth(p->left);
	}
	if(p->right == NULL)
	{
		rightDepth = -1;
	}
	else
	{
		rightDepth = calDepth(p->right);
	}
	if(leftDepth >= rightDepth)
	{
		return leftDepth + 1;
	}
	else
	{
		return rightDepth + 1;
	}
}

void print_stats (Table root) 
{
	// calculate depth of the binary tree
	if(root == NULL)
	{
		printf("Table has not initialized.\n");
		return;
	}
	int depth = calDepth(root->head);
	depth--; // reduce NULL_NODE level
	printf("The depth of the tree is %d.\n", depth);
}

void tidy (Table root)
{
	if(root == NULL)
	{
		printf("Table is empty\n");
		return;
	}
	tree_ptr p = root->head;
	free_tree(p);
	free(root);
}

void free_tree(tree_ptr p)
{
	if(p != NULL)
	{
		free_tree(p->left);
		free_tree(p->right);
		if(p->element != NULL)
		{
			free(p->element);
		}
		free(p);
	}
}