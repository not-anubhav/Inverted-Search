#include "inverted_search.h"
extern int database_created;
int display_output(sub_t *subnode, main_t *mainnode, hash_t *hashtable)
{
	/* Definition here */
	if(database_created == 0)
	{
		printf(BRED"Database is Empty\nNothing to Display\n"RESET);
		return FAILURE;
	}
	int not_null = 0, index_printed = 0;
    printf("-----------------------------------------------------------------------------------------\n");
    printf(BBLUE "%-10s %-10s %-15s %-10s %-10s %-10s %-12s\n" RESET, "Index", "Word", "File Count", "Files/s", "File:", "Filename", "Word Count");
    printf("-----------------------------------------------------------------------------------------\n");
	for(int i = 0; i < 27; i++)
	{
		if(hashtable[i].hashmainlink != NULL)
		{
			printf(BRED"%-10d"RESET, hashtable[i].index);
			index_printed = 1;
			main_t *maintemp = hashtable[i].hashmainlink;
			while (maintemp != NULL)
			{
				/* code */
				sub_t *subtemp = maintemp->mainsublink;
				if(index_printed == 0)
				{
					printf("%-10s", " ");
				}
				index_printed = 0;
				printf(BRED"%-15s "RESET, maintemp->word);
				printf(BRED"%-12d%-11s"RESET, maintemp->file_count, "file/s:");
				int count = 0;
				while (subtemp != NULL)
				{
					/* code */
					if(count >= 1)
					{
						printf(BRED"%49s%-10s %-15s"RESET, " ", "File:", subtemp->f_name);
						printf(BRED"%d"RESET, subtemp->word_count);
					}
					else
					{
						printf(BRED"%-10s %-15s"RESET, "File:", subtemp->f_name);
						printf(BRED"%d"RESET, subtemp->word_count);
						printf("\n");
					}
					count++;
					subtemp = subtemp->sublink;
				}
				maintemp = maintemp->mainlink;
				printf("\n");
				not_null++;
			}
			printf("\n");
		}
	}
	if(not_null == 0)
	{
		printf(BYELLOW"\n[Hash Table is Empty]\n\n"RESET);
	}
}

