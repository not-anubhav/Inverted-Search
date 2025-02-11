#include "inverted_search.h"

int insert_at_last(v_files **head, char data[])
{
        v_files *new = malloc(sizeof(v_files)); /*Allocate the memory*/
        if(new == NULL)
        {
                return FAILURE; /* If memory Allocation Failed return FAILURE*/
        }
        /* Update data and link part of new node */
        strcpy(new->filename, data);
        new->link = NULL;
        /* List is Empty */
        if(*head == NULL)
        {
                *head = new;
                return SUCCESS;
        }
        /* List not Empty */
        v_files *temp = *head;
        while(temp->link!= NULL)
        {
                temp = temp->link;
        }
        temp->link = new;
        return SUCCESS;
}