#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
} node;

/* 
	Traverse the linked list to get the data stored in each node for further manipulation
	e.g., display the node information. 
*/
typedef void (*callback) (node* data);

void traverse(node *head, callback f)
{
    node *cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}

void display(node* n)
{
    if(n != NULL)
    {
        printf("%d ", n->data);
    }
}

/* 
	Use the same traversing technique to count the number of elements in a linked list.
*/
void count(node *head)
{
    node *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
}

/* 
	Create a new node
*/
node* create(int data, node* next)
{
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("%s\n", "Error creating new node...");
        exit(0);
    }

    new_node->data = data;
    new_node->next = next;

    return new_node;
}

/* 
	Adds a new node at the begining of the linked list. 
	Point the next pointer of the new node to the head pointer and point the head pointer to the new node
*/
node* prepend(node* head, int data)
{
    node* new_node = create(data, head);
    head = new_node;

    return head;
}

/* 
	Adds a new node at the end of the linked list. 
*/
node* append(node* head, int data)
{
    /* go to the last node */
    node *cursor = head;
    while(cursor->next != NULL)
    {
        cursor = cursor->next;
    }

    /* create a new node */
    node* new_node = create(data, NULL);
    cursor->next = new_node;

    return head;
}

/*
    Insert a new node after the prev node
*/
node* insert_after(node *head, int data, node *prev)
{
	/* find the prev node, starting from the first node */
    node *cursor = head;
    while(cursor != prev)
    {
        cursor = cursor->next;
    }
    
    if(cursor != NULL)
    {
        node* new_node = create(data, cursor->next);
        cursor->next = new_node;

        return head;
    }
    else
    {
        return NULL;
    }
}

/*
    Insert a new node before the next node
*/
node* insert_before(node *head, int data, node *nxt)
{
    if (head == nxt)
    {
        head = prepend(head, data);
        return head;
    }

    node *cursor = head;
    while(cursor->next != nxt)
    {
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        node *new_node = create(data, cursor->next);
        cursor->next = new_node;

        return head;
    }
    else
    {
        return NULL;
    }
}

/*
	Search for a node that stores a given data
*/
node* search(node *head, int data)
{
    node *cursor = head;
    while(cursor != NULL)
    {
        if (cursor->data == data)
        {
            return cursor;
        }
        cursor = cursor->next;
    }
    return NULL;
}

/*
	Delete a node from the front of the linked list
*/
node* remove_front(node* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    node *front = head;
    head = head->next;
    front->next = NULL;
    if(front == head)
    {
        head = NULL;
    }
    free(front);

    return head;
}

/*
	Delete a node from the back of the linked list
*/
node* remove_back(node* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    
    node *cursor = head;
    node *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }
    if(back != NULL)
    {
        back->next = NULL;
    }
    
    if(cursor == head)
    {
        head = NULL;
    }
    
    free(cursor);
    
    return head;
}

/*
	Delete a node in the middle of the linked list
*/
node* remove_any(node* head, node* nd)
{
    /* if the node is the first node */
    if(nd == head)
    {
        head = remove_front(head);
        return head;
    }
    
    /* if the node is the last node */
    if(nd->next == NULL)
    {
        head = remove_back(head);
        return head;
    }
    
    /* if the node is in the middle */
    node* cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next = nd)
            break;
        cursor = cursor->next;
    }
    
    if(cursor != NULL)
    {
        node* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;
}


int main()
{	
    node *head = NULL;
    callback disp = display;

    printf("\nCreating linked list with 10 values...\n");
    for (int i = 0; i < 10; ++i)
    {
        head = create(i, head);
    }
    traverse(head, disp);

    printf("\nRemove first element...\n");
    head = remove_front(head);
    traverse(head, disp);

    printf("\nRemove last element...\n");
    head = remove_back(head);
    traverse(head, disp);

    return 0;
}