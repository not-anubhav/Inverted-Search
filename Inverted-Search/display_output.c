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
	int not_null = 0;
	printf(BBLUE"[Index]   [Word]   [File Count]   [Files/s]   [File:]   [Filename]   [Word Count]\n"RESET);
	for(int i = 0; i < 27; i++)
	{
		if(hashtable[i].hashmainlink != NULL)
		{
			printf(BRED"[%d]"RESET, hashtable[i].index);
			main_t *maintemp = hashtable[i].hashmainlink;
			while (maintemp != NULL)
			{
				/* code */
				sub_t *subtemp = maintemp->mainsublink;
				printf(BRED"	  [ %s ]"RESET, maintemp->word);
				printf(BRED"	%d	   file/s:"RESET, maintemp->file_count);
				int count = 0;
				while (subtemp != NULL)
				{
					/* code */
					if(count >= 1)
					{
						printf(BRED"%47sFile:%4s%s"RESET, " ", " ",subtemp->f_name);
						printf(BRED"	  %d	"RESET, subtemp->word_count);
					}
					else
					{
						printf(BRED"     File:    %s"RESET, subtemp->f_name);
						printf(BRED"	  %d	"RESET, subtemp->word_count);
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

