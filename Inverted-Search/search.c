#include "inverted_search.h"
extern int database_created;
int search (hash_t *hashtable, main_t *mainnode, sub_t *subnode)
{
	/* Definition here */
	if(database_created == 0)
	{
		printf(BRED"Database is Empty\nCan't perform search DATABASE operation\n"RESET);
		return FAILURE;
	}
	char word[50];
	printf("Enter the word to search : ");
	scanf("%49s", word);
	printf("\n");
	int index = -1;
	if(word[0] >= 'a' && word[0] <= 'z')
	{
		index = word[0] - 'a';
	}
	else if(word[0] >= 'A' && word[0] <= 'Z')
	{
		index = word[0] - 'A';
	}
	else if(isdigit(word[0]) || ispunct(word[0]))
	{
		index = 26;
	}

	main_t *maintemp = hashtable[index].hashmainlink;
	if(maintemp == NULL)
	{
		printf(RED "Hash Table Empty for this word Index\n" RESET);
		return FAILURE;
	}

	while (maintemp != NULL)
	{
		/* code */
		if(strcmp(maintemp->word, word) == 0)
		{
			printf(BGREEN"Word %s is present in %d file/s\n"RESET, word, maintemp->file_count);
			sub_t *subtemp = maintemp->mainsublink;
			while (subtemp != NULL)
			{
				/* code */
				printf(BCYAN"In File: %s %d time/s\n"RESET, subtemp->f_name, subtemp->word_count);
				subtemp = subtemp->sublink;
			}
			return SUCCESS;
		}
		maintemp = maintemp->mainlink;
	}
	printf(RED "Word %s is not found in Database\n" RESET, word);
	return FAILURE;
}

