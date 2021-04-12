#include "Error.h"
#include <string.h>
struct ErrorNode *ErrorHead = NULL;
int HaveErrors=0;
void print_Node(struct ErrorNode* node){
    printf("Error Type %s at line %d:%s.\n",node->ErrorType,node->Linenumber,node->Information);
}
void print_Errors(){
    if(HaveErrors==0) return;
    struct ErrorNode* p=ErrorHead;
    while(p!=NULL){
        print_Node(p);
        p=p->next;
    }
}
void insert_Error(char* errorType,int linenumber,char* information){
    HaveErrors++;
    struct ErrorNode* q=(struct ErrorNode*)malloc(sizeof(struct ErrorNode));
    q->Linenumber=linenumber;
    q->ErrorType=malloc(strlen(errorType));
    strcpy(q->ErrorType,errorType);
    q->Information=malloc(strlen(information));
    strcpy(q->Information,information);
    q->next=NULL;
    struct ErrorNode* p=ErrorHead;
    if(ErrorHead==NULL)
    {
        ErrorHead=q;
        return;
    }
    while(p->next!=NULL)
        p=p->next;
    p->next=q;
}