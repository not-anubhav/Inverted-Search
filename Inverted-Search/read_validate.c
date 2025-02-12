#include "inverted_search.h"

int read_validate(int argc, char *argv[], v_files *flist, v_files **head)
{
    
    if(argc < 2)
    {
        printf(BRED"Invalid Number of Arguments Passed\n[Usage] ./outputfile file1.txt file2.txt file3.txt\n"RESET);
        return FAILURE;
    }

    for(int i = 1; i < argc; i++)
    {
        int dup = 0;
        char *delim = strstr(argv[i], ".");
        if(delim == NULL)
        {
            printf(BRED"%s File has Invalid Extension\n"RESET, argv[i]);
            continue;
        }
        else if(strcmp(delim, ".txt") != 0)
        {
            printf(BRED"%s File Format is not .txt\n"RESET, argv[i]);
            continue;
        }

        if(validate_file(&argv[i]) == FAILURE)
        {
            continue;
        }

        if(*head == NULL)
        {
            insert_at_last(head, argv[i]);
            printf(BMAGENTA"\nSuccessfull inserting filename: %s into file linked list\n"RESET, argv[i]);
        }
        else
        {
            v_files *temp = *head;
            while(temp != NULL)
            {
                if(strcmp(temp->filename, argv[i]) == 0)
                {
                    printf(BYELLOW"%s Duplicate Files Found\n"RESET, argv[i]);
                    dup = 1;
                    break;
                }
                temp = temp->link;
            }
            if(dup == 1)
            {
                continue;
            }
            else
            {
                insert_at_last(head, argv[i]);
                printf(BMAGENTA"Successfull inserting filename: %s into file linked list\n"RESET, argv[i]);
            }
        }
    }
    print_Flist(*head);
    if(*head == NULL)
    {
        return FAILURE;
    }
    else
    {
        return SUCCESS;
    }
}

int validate_file(char *filename[])
{
    FILE *file = fopen(*filename, "r");
    if(file == NULL)
    {
        printf(BYELLOW"%s File Does Not Exists\n"RESET, *filename);
        return FAILURE;
    }
    fseek(file, 0, SEEK_END);
    int pos = ftell(file);
    if(pos == 0)
    {
        printf(BYELLOW"%s File is Empty\n"RESET, *filename);
        return FAILURE;
    }
    fclose(file);
    return SUCCESS;
}