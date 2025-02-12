#include "inverted_search.h"
extern int database_created;
int save_database(main_t *mainnode, sub_t *subnode, hash_t *hashtable)
{
    if(database_created == 0)
	{
		printf(BRED"Database is Empty\nCan't perform save DATABASE operation\n"RESET);
		return FAILURE;
	}
    char filename[50];
    printf("Enter the file name to save database : ");
    scanf("%s", filename);

    if(validate_savefile(filename) == FAILURE)
    {
        return FAILURE;
    }

    FILE *file = database_file(filename);
    if(file == NULL)
    {
        return FAILURE;
    }

    for(int i = 0; i < 27; i++)
    {
        if(hashtable[i].hashmainlink != NULL)
        {
            fprintf(file, "#%d;", i);
            main_t *maintemp = hashtable[i].hashmainlink;
            while(maintemp != NULL)
            {
                sub_t *subtemp = maintemp->mainsublink;
                fprintf(file, "%s;%d;", maintemp->word, maintemp->file_count);
                while(subtemp != NULL)
                {
                    fprintf(file, "%s;%d;", subtemp->f_name, subtemp->word_count);
                    subtemp = subtemp->sublink;
                }
                if(maintemp->mainlink != NULL)
                {
                    fprintf(file, "\n");
                }
                maintemp = maintemp->mainlink;
            }
            fprintf(file, "#\n");
        }
    }
    return SUCCESS;

}

int validate_savefile(char *filename)
{
    char *delim = strstr(filename, ".");
    if(delim == NULL)
    {
        printf(BRED"%s File has Invalid Extension\n"RESET, filename);
        return FAILURE;
    }
    else if(strcmp(delim, ".txt") != 0)
    {
        printf(BRED"%s File Format is not .txt\n"RESET, filename);
        return FAILURE;
    }
    return SUCCESS;
}


FILE *database_file(char *filename)
{
    FILE *fptr = fopen(filename, "w");

    if(fptr == NULL)
    {
        printf(BRED"Failed to open the file %s\n"RESET, filename);
        return NULL;
    }

    return fptr;
}