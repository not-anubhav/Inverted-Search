#ifndef IS_H
#define IS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "color.h"

#define SUCCESS 0
#define FAILURE -1
#define TABLE_EMPTY -2

typedef struct file_list
{
    /* data */
    char filename[50];
    struct file_list *link;
}v_files;

typedef struct subnode
{
    int word_count;
    char f_name[50];
    struct subnode *sublink;
}sub_t;

typedef struct mainnode
{
    int file_count;
    char word[50];
    struct mainnode *mainlink;
    sub_t *mainsublink;
}main_t;

typedef struct hash
{
    int index;
    main_t *hashmainlink;
}hash_t;

int read_validate(int argc, char *argv[], v_files *files, v_files **head);
int insert_at_last(v_files **head, char data[]);
int validate_file(char *filename[]);
void print_Flist(v_files *head);
int create_database(v_files *flist, v_files **head, sub_t *subnode, main_t *mainnode, hash_t *hashtable);
void create_HT(hash_t *hashtable);
sub_t *create_subnode(sub_t *subnode);
main_t *create_mainnode(main_t *mainnode);
int display_output(sub_t *subnode, main_t *mainnode, hash_t *hashtable);
int search (hash_t *hashtable, main_t *mainnode, sub_t *subnode);
int save_database(main_t *mainnode, sub_t *subnode, hash_t *hashtable);
int validate_savefile(char *filename);
FILE *database_file(char *filename);
int update(v_files *flist, v_files **head, main_t *mainnode, sub_t *subnode, hash_t *hashtable);
FILE *update_validation(char *filename);
int validate_duplicate(v_files **head, char *filename);
int delete_node(v_files **from_head, v_files **using_head);
int print_ht(hash_t *hashtable);
#endif