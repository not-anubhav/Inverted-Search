#include "inverted_search.h"

void print_Flist(v_files *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
        printf(BCYAN"\n[File Linked List]\n"RESET);
	    while (head)		
	    {
		    printf(BYELLOW"%s -> "RESET, head->filename);
		    head = head -> link;
	    }

	    printf(BYELLOW"NULL\n"RESET);
    }
}