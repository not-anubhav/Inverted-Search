#include "inverted_search.h"
extern int database_created;
int database_updated = 0;
int update(v_files *flist, v_files **head, main_t *mainnode, sub_t *subnode, hash_t *hashtable)
{
    if(database_created == 1)
    {
        printf(BRED"DATABASE already created\nCan't perform update DATABASE operation\n"RESET);
        return FAILURE;
    }
    if(database_updated == 1)
    {
        printf(BRED"DATABASE already Updated\nCan't perform update DATABASE operation again\n"RESET);
        return FAILURE;
    }
    char filename[50];
    printf(BCYAN"Enter the file name to update data: "RESET);
    scanf("%s", filename);
    
    char *delim = strstr(filename, ".");
    if(delim == NULL)
    {
        printf(BRED"Invalid Extension\n"RESET);
        return FAILURE;
    }
    else if(strcmp(delim, ".txt") != 0)
    {
        printf(BRED"Entered Filename is not in .txt format\n"RESET);
        return FAILURE;
    }

    FILE *file = update_validation(filename);
    if(file == NULL)
    {
        return FAILURE;
    }

    rewind(file);
    
    int index;
    while(fscanf(file, "#%d;", &index) == 1)
    {
        hashtable[index].index = index;
        char word[50];
        int file_count;
        while(fscanf(file, "%[^;];%d;", word, &file_count) == 2)
        {
            //printf("word %s fc %d pos %ld\n", word, file_count, ftell(file));
            main_t *newmain = create_mainnode(mainnode);
            if(newmain == NULL)
            {
                printf(BRED"Mainnode Creation Failed\n"RESET);
                return FAILURE;
            }
            main_t *maintemp = hashtable[index].hashmainlink;
            if(maintemp == NULL)
            {
                hashtable[index].hashmainlink = newmain;
                maintemp = hashtable[index].hashmainlink;
                strcpy(maintemp->word, word);
                maintemp->file_count = file_count;
                maintemp->mainlink = NULL;
                maintemp->mainsublink = NULL;
            }
            else
            {
                while(maintemp->mainlink != NULL)
                {
                    maintemp = maintemp->mainlink;
                }
                maintemp->mainlink = newmain;
                maintemp = maintemp->mainlink;
                strcpy(maintemp->word, word);
                maintemp->file_count = file_count;
                maintemp->mainlink = NULL;
                maintemp->mainsublink = NULL;
            }
            char f_name[50];
            int word_count;
            if(maintemp->file_count == 1)
            {
                fscanf(file,"%[^;];%d;", f_name, &word_count);
                sub_t *newsub = create_subnode(subnode);
                if(newsub == NULL)
                {
                    printf(BRED"Subnode Creation Failed\n"RESET);
                    return FAILURE;
                }
                maintemp->mainsublink = newsub;
                sub_t *subtemp = maintemp->mainsublink;
                strcpy(subtemp->f_name, f_name);
                subtemp->word_count = word_count;
                subtemp->sublink = NULL;
                if(*head == NULL)
                {
                    insert_at_last(head, subtemp->f_name);
                }
                else
                {
                    if(validate_duplicate(head, subtemp->f_name) == SUCCESS)
                    {
                        insert_at_last(head, subtemp->f_name);
                    }
                }
            }
            else if(maintemp->file_count > 1)
            {
                for(int i = 0; i < maintemp->file_count; i++)
                {
                    fscanf(file,"%[^;];%d;", f_name, &word_count);
                    sub_t *newsub = create_subnode(subnode);
                    sub_t *subtemp = maintemp->mainsublink;
                    if(subtemp == NULL)
                    {
                        maintemp->mainsublink = newsub;
                        subtemp = maintemp->mainsublink;
                        subtemp->sublink = NULL;
                        strcpy(subtemp->f_name, f_name);
                        subtemp->word_count = word_count;
                    }
                    else
                    {   
                        while(subtemp->sublink != NULL)
                        {
                            subtemp = subtemp->sublink;
                        }
                        subtemp->sublink = newsub;
                        subtemp = subtemp->sublink;
                        strcpy(subtemp->f_name, f_name);
                        subtemp->word_count = word_count;
                        subtemp->sublink = NULL;
                    }
                    if(*head == NULL)
                    {
                        insert_at_last(head, subtemp->f_name);
                    }
                    else
                    {
                        if(validate_duplicate(head, subtemp->f_name) == SUCCESS)
                        {
                            insert_at_last(head, subtemp->f_name);
                        }
                    }
                }
            }
            char c_hash;
            c_hash = fgetc(file);
            if(c_hash != '#')
            {
                fscanf(file,"\n");
            }
            else
            {
                break;
            }
        }
        fscanf(file,"\n");
    }
    database_updated = 1;
    return SUCCESS;
}

FILE *update_validation(char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
        printf(BRED"Input File Doesn't Exist\n"RESET);
        return NULL;
    }
    fseek(fptr, 0, SEEK_SET);
    char validate_hash;
    fscanf(fptr, "%c", &validate_hash);
    if(validate_hash != '#')
    {
        printf(BRED"Input File is not a DATABASE File\n"RESET);
        fclose(fptr);
        return NULL;
    }
    fseek(fptr, 0, SEEK_END);
    fseek(fptr, -2, SEEK_CUR);
    fscanf(fptr, "%c", &validate_hash);
    if(validate_hash != '#')
    {
        printf(BRED"Input File is not a DATABASE File\n"RESET);
        fclose(fptr);
        return NULL;
    }
    return fptr;
}

int validate_duplicate(v_files **head, char *filename)
{
    v_files *temp = *head;
    while(temp != NULL)
    {
        if(strcmp(temp->filename, filename) == 0)
        {
            return FAILURE;
        }
        temp = temp->link;
    }
    return SUCCESS;
}