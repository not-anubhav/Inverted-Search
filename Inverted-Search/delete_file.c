#include "inverted_search.h"

int delete_node(v_files **head, v_files **update_oper_head)
{
    v_files *temp1 = *head;
    v_files *temp2 = *update_oper_head;

    while(temp2 != NULL)
    {
        temp1 = *head;
        while(temp1 != NULL)
        {
            v_files *prev = temp1;
            if(strcmp(temp2->filename, temp1->filename) == 0)
            {
                if(prev == temp1)
                {
                    *head = temp1->link;
                    free(temp1);
                }
                else
                {
                    prev->link = temp1->link;
                    free(temp1);
                }
            }
            temp1 = temp1->link;
        }
        temp2 = temp2->link;
    }

    while(*update_oper_head != NULL)
    {
        v_files *temp = *update_oper_head;
        *update_oper_head = temp->link;  
        free(temp);
    }
}