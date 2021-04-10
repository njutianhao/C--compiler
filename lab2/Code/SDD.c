#include"GrammarTree.h"
#include"SymbleTable.h"

/*struct GrammarTree *get_child(struct ListNode *head,int index){
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
    Type t = handle_Specifier(get_child(node->head,1));
    struct GrammarTree *tmp = get_child(node->head,2);
    switch(tmp->type){
        case FunDec:
            handle_FunDec(t,tmp);
            handle_CompSt(get_child(node->head,3));
        case ExtDecList:;

    }
}

Type handle_Specifier(struct GrammarTree *node){
    switch(node->type){
        case TYPE:;
        case StructSpecifier:;
    }
    printf("wrong in handle_Specifier\n");
    exit(0);
}

void handle_FunDec(Type t,struct GrammarTree *node){
    handle_ID(t,get_child(node->head,1));
    struct GrammarTree *tmp = get_child(node->head,3);
    if(tmp->type == VarList)
        handle_VarList(tmp);
}

void handle_ID(Type t,struct GrammarTree *node){
    if(name_exist(node->val.str) == 0)
        insert_Node(t,node->val.str);
    else
    {
        char *inf = strcat("Redefined variable \"",strcat(node->val.str,"\"."));
        insert_Error('3',node->line,inf);
    }
}

void handle_VarList(struct GrammarTree *node){

}

void handle_DefList(struct GrammarTree *node){

}

void handle_Exp(struct GrammarTree *node){

}*/