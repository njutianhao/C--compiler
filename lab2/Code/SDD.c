#include"GrammarTree.h"
#include"syntax.tab.h"
#include"SymbleTable.h"

struct GrammarTree *get_child(struct ListNode *head,int index){
    for(int i = 1;i < index;i++)
    {
        if(head == NULL)
            return NULL;
        head = head->next;
    }
    return head->val;
}

void SDT(){
    SDT_DFS(root);
}

void SDT_DFS(struct GrammarTree *node){
    switch(node->type){
        case ExtDefList: handle_ExtDefList(node);break;
        case DefList:handle_DefList(node);break;
        case Exp:handle_Exp(node);break;
        default :
            ListNode *p = node->head;
            while(p != NULL)
            {
                SDT_DFS(p->val);
                p = p->next;
            }
    }
}

void handle_ExtDefList(struct GrammarTree *node){
    if(node->head == NULL)
        return ;
    handle_ExtDef(get_child(node->head,1));
    handle_ExtDefList(get_child(node->head,2));
}

void handle_ExtDef(struct GrammarTree *node){
    TYPE t = handle_Specifier(get_child(node->head,1));
    struct GrammarTree *tmp = get_child(node->head,2);
    switch(tmp->type){
        case FunDec:
            handle_FunDec(t,tmp);
            handle_CompSt(get_child(node->head,3));
        case ExtDecList:

    }
}

TYPE handle_Specifier(struct GrammarTree *node){

}

void handle_FunDec(TYPE t,struct GrammarTree *node){
    handle_ID(t,get_child(node->head,1));
    node = get_child(node->head,3);
    if(node->type == VarList)
        handle_VarList(node);
}

void handle_ID(TYPE t,struct GrammarTree *node){
    
    insert_Node(t,node->val.str);
}

void handle_VarList(struct GrammarTree *node){

}

void handle_DefList(struct GrammarTree *node){

}

void handle_Exp(struct GrammarTree *node){

}