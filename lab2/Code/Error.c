#include "GrammarTree.h"
struct ErrorNode *ErrorHead = NULL;
int HaveErrors=0;
void print_Errors(){
    if(HaveErrors==0) return;
    struct ErrorNode* p=ErrorHead;
    while(p!=NULL){
        print_Node(p);
        p=p->next;
    }
}
void insert_Error(char* errorType,int linenumber,char* information){
    if(ErrorHead==NULL){
        ErrorHead=(struct ErrorNode*)malloc(sizeof(struct ErrorNode));
        ErrorHead->Linenumber=linenumber;
        ErrorHead->ErrorType=errorType;
        char* tmp=information;
        ErrorHead->Information=tmp;
        ErrorHead->next=NULL;
    }
    else{
        struct ErrorNode* p=ErrorHead;
        struct ErrorNode* q=(struct ErrorNode*)malloc(sizeof(struct ErrorNode));
        q->Linenumber=linenumber;
        q->ErrorType=errorType;
        q->next=NULL;
        char* tmp=information;
        q->Information=tmp;
        if(p->Linenumber>q->Linenumber){
            q->next=ErrorHead;
            ErrorHead=q;
            return;
        }
        while(p!=NULL){
            if(p->next==NULL && p->Linenumber<q->Linenumber){
                p->next=q;
                return;
            }
            if(p->Linenumber<=q->Linenumber && p->next->Linenumber>=q->Linenumber){
                q->next=p->next;
                p->next=q;
                return;
            }
            p=p->next;
        }
    }
}