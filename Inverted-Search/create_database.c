#include "inverted_search.h"
int database_created = 0;
int create_database(v_files *flist, v_files **head, sub_t *subnode, main_t *mainnode, hash_t *hashtable)
{
	/* Definition here */
	if(database_created == 1)
	{
		printf(BRED"Files Passed through command line are already added into the database\nCan't create DATABASE again\n"RESET);
		return FAILURE;
	}
	v_files *file_temp = *head;
	if(*head == NULL)
	{
		printf(BRED"File List is Empty\nCannot create DATABASE\n"RESET);
		return FAILURE;
	}
	char word[50];
	int index = -1;
	while(file_temp != NULL)
	{
		FILE *fptr = fopen(file_temp->filename, "r");
		if(fptr == NULL)
		{
			printf(BYELLOW"Failed to Open File %s"RESET, file_temp->filename);
			continue;
		}
		
		while(fscanf(fptr, "%49s", word) == 1)
		{
			if (word[0] >= 'a' && word[0] <= 'z')
			{
				index = word[0] - 'a';
			}
			else if (word[0] >= 'A' && word[0] <= 'Z')
			{
				index = word[0] - 'A';
			}
			else if (isdigit(word[0]) || ispunct(word[0]))
			{
				index = 26;
			}
			if(hashtable[index].hashmainlink == NULL)
			{
				sub_t *newsub = create_subnode(subnode);
				if(newsub == NULL)
				{
					printf(RED"Subnode Creation Failed\n"RESET);
					return FAILURE;
				}
				main_t *newmain = create_mainnode(mainnode);
				if(newmain == NULL)
				{
					printf(RED"Main Node Creation Failed\n"RESET);
					return FAILURE;
				}
				hashtable[index].hashmainlink = newmain;
				newmain->file_count = 1;
				strcpy(newmain->word, word);
				newmain->mainsublink = newsub;
				newmain->mainlink = NULL;
				newsub->word_count = 1;
				strcpy(newsub->f_name, file_temp->filename);
				newsub->sublink = NULL;
			}
			else
			{
				int word_matched = 0;
				main_t *main_temp = hashtable[index].hashmainlink;
				main_t *prev_main_temp = NULL;
				while(main_temp != NULL)
				{
					prev_main_temp = main_temp;
					if(strcmp(main_temp->word, word) == 0)
					{
						word_matched = 1;
						break;
					}
					else
					{
						main_temp = main_temp->mainlink;
					}
				}
				if(word_matched == 0)
				{
					sub_t *newsub = create_subnode(subnode);
					if (newsub == NULL)
					{
						printf(RED"Subnode Creation Failed\n"RESET);
						return FAILURE;
					}
					main_t *newmain = create_mainnode(mainnode);
					if (newmain == NULL)
					{
						printf(RED"Main Node Creation Failed\n"RESET);
						return FAILURE;
					}
					prev_main_temp->mainlink = newmain;
					newmain->file_count = 1;
					strcpy(newmain->word, word);
					newmain->mainlink = NULL;
					newmain->mainsublink = newsub;
					newsub->word_count = 1;
					strcpy(newsub->f_name, file_temp->filename);
					newsub->sublink = NULL;
				}
				else if(word_matched == 1)
				{
					int same_file = 0;
					sub_t *subtemp = main_temp->mainsublink;
					sub_t *prev_subtemp = NULL;
					while(subtemp != NULL)
					{
						prev_subtemp = subtemp;
						if(strcmp(file_temp->filename, subtemp->f_name) == 0)
						{
							same_file = 1;
							break;
						}
						else
						{
							subtemp = subtemp->sublink;
						}
					}
					if(same_file == 1)
					{
						subtemp->word_count++;
					}
					else if(same_file == 0)
					{
						sub_t *newsub = create_subnode(subnode);
						if (newsub == NULL)
						{
							printf(RED"Subnode Creation Failed\n"RESET);
							return FAILURE;
						}
						main_temp->file_count++;
						prev_subtemp->sublink = newsub;
						newsub->word_count = 1;
						strcpy(newsub->f_name, file_temp->filename);
						newsub->sublink = NULL;
					}
				}
			}
		}
		printf(BBLUE"Successfull : Creation of DATABASE for file: %s\n"RESET, file_temp->filename);
		file_temp = file_temp->link;
	}
	database_created = 1;
}

void create_HT(hash_t *hashtable)
{
	for(int i = 0; i < 27; i++)
	{
		hashtable[i].index = i;
		hashtable[i].hashmainlink = NULL;
	}
}

sub_t *create_subnode(sub_t *subnode)
{
	sub_t *new = malloc(sizeof(sub_t));
	if(new == NULL)
	{
		return NULL;
	}
	new->word_count = 0;
	strcpy(new->f_name, " ");
	new->sublink = NULL;
	return new;
}

main_t *create_mainnode(main_t *mainnode)
{
	main_t *new = malloc(sizeof(main_t));
	if(new == NULL)
	{
		return NULL;
	}
	new->file_count = 0;
	strcpy(new->word, " ");
	new->mainlink = NULL;
	new->mainsublink = NULL;
	return new;
}