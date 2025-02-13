#include "inverted_search.h"

int main(int argc, char *argv[])
{
	/* Define the main function here */
	v_files flist;
	sub_t subnode;
	main_t mainnode;
	hash_t hashtable[27];
	create_HT(hashtable);
	//print_ht(hashtable);
	v_files *head = NULL;
	v_files *update_oper_head = NULL;
	if(read_validate(argc, argv, &flist, &head) == FAILURE)
	{
		printf(RED"Validation Failed\n"RESET);
		return FAILURE;
	}

	char ch;

	do
	{
		/* code */
		int option;
		printf("\n1.Create Database\n2.Display Database\n3.Update Database\n4.Search\n5.Save Database\n6.EXIT\nEnter your choice: ");
		scanf("%d", &option);
		printf("\n");
		switch (option)
		{
		case 1:
			/* code */
			create_database(&flist, &head, &subnode, &mainnode, hashtable);
			//print_ht(hashtable);
			break;
		case 2:
			printf("\n");
			display_output(&subnode, &mainnode, hashtable);
			break;
		case 3:
			if(update(&flist, &update_oper_head, &mainnode, &subnode, hashtable) == SUCCESS)
			{
				//print_ht(hashtable);
				delete_node(&head, &update_oper_head);
				print_Flist(head);
			}
			break;
		case 4:
			search(hashtable, &mainnode, &subnode);
			printf("\n");
			break;
		case 5:
			save_database(&mainnode, &subnode, hashtable);
			break;
		case 6:
			return SUCCESS;
		default:
			printf("Invaild Choice\n");
			break;
		}
reenter:
		printf("\nDo you want to continue ?\nEnter y/Y to continue and n/N to discontinue\n");
		getchar();
		scanf("%c", &ch);
		if(ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
		{
			printf("Invalid Input\n");
			goto reenter;
		}
	} while (ch == 'y' || ch == 'Y');
}

int print_ht(hash_t *hashtable)
{
	for(int i = 0; i < 27; i++)
	{
		printf("-------------------------------------\n");
		printf("|Index : %d	|	Link: %p|\n", hashtable[i].index, hashtable[i].hashmainlink);
		printf("-------------------------------------\n");
	}
}

