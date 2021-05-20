#ifndef ERROR_H
#define ERROR_H
#include<stdio.h>
#include<stdlib.h>
struct ErrorNode{
    int Linenumber;
    char* ErrorType;
    char *Information;
    struct ErrorNode* next;
};
struct ErrorNode *ErrorHead;
int HaveErrors;
void print_Errors();
void print_Node(struct ErrorNode* node);
void insert_Error(char*errorType,int linenumber,char* information);
#endif