#include"GrammarTree.h"
#include"syntax.tab.h"

int instruct = 0;

int try_insert(Type type_in,int line,char* name){
    if(name_exist(name) == 0)
    {
        insert_Node(type_in,name);   
    }
    else if(search_struct(name) == NULL)
    {
        char *inf = strcat("Redefined variable \"",strcat(name,"\"."));
        insert_Error("3",line,inf);
        return 0;
    }
    else
    {
        char *inf = strcat("Redefined field \"",strcat(name,"\"."));
        insert_Error("15",line,inf);
        return 0;
    }
}

struct GrammarTree *get_child(struct GrammarTree *node,int index){
    struct ListNode *head = node->head;
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
    struct ListNode *p;
    switch(node->type){
        case ExtDefList: handle_ExtDefList(node);break;
        case DefList:handle_DefList(node);break;
        case Exp:handle_Exp(node);break;
        default :
            p = node->head;
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
    handle_ExtDef(get_child(node,1));
    handle_ExtDefList(get_child(node,2));
}

void handle_ExtDef(struct GrammarTree *node){
    struct GrammarTree *tmp1 = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    struct GrammarTree *tmp3 = get_child(node,3);
    int res = handle_Specifier(tmp1);
    if(res == 0)
        return ;
    tmp2->inh = tmp1->syn;
    switch(tmp2->type){
        case FunDec:
            if(handle_FunDec(tmp2) == 0)
                return ;
            handle_CompSt(tmp3);
        case ExtDecList:;

    }
}

int handle_Specifier(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    int res;
    switch(tmp->type){
        case TYPE:node->syn.t = create_Basic_Type(tmp->val.str); return 1;
        case StructSpecifier:
            res = handle_StructSpecifier(tmp);
            if(res == 1) node->syn = tmp->syn;
            return res;
        default:
            printf("wrong in handle_Specifier\n");
            exit(0);
    }
}

int handle_StructSpecifier(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,2);
    struct GrammarTree *tmp2 = get_child(node,4);
    int old_instruct;
    int res;
    Type t;
    switch(tmp->type){
        case OptTag:
            handle_OptTag(tmp);
            old_instruct = instruct;
            instruct = 1;
            handle_DefList(tmp2);
            t = create_Structure_Type(tmp2->syn.f,tmp->syn.str);
            res = try_insert(t,tmp->line,tmp->syn.str);
            instruct = old_instruct;
            if(res == 1)
            {
                node->syn.t = t;
            }
            return res;
        case Tag:
            handle_ID(tmp);
            t = search_struct(tmp->syn.str);
            if(t == NULL)
            {
                return 0;
            }
            else
            {
                node->syn.t = t;
                return 1;
            }
    }
}

void handle_OptTag(struct GrammarTree *node){
    struct GrammarTree* tmp = get_child(node,1);
    if(tmp == NULL)
    {
        node->syn.str = NULL;
    }
    else if(tmp->type == ID){
        handle_ID(tmp);
        node->syn.str = tmp->syn.str;
    }
    else{
        printf("wrong in handle_OptTag\n");
        exit(0);
    }
}

void handle_DefList(struct GrammarTree *node){
    if(node->head == NULL)
    {
        node->syn.f = NULL;
        return;
    }
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    handle_Def(tmp);  
    handle_DefList(tmp2);
    node->syn.f = insert_FieldList(tmp->syn.f,tmp2->syn.f);
}

void handle_Def(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    handle_Specifier(tmp);
    tmp2->inh = tmp->syn;
    handle_DecList(tmp2);
    node->syn = tmp2->syn;
}

void handle_DecList(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    tmp->inh = node->inh;
    int res = handle_Dec(tmp);
    if(res == 1)
    {
        node->syn = tmp->syn;
    }
    else
        node->syn.f = NULL;
    if(tmp2 != NULL)
    { 
        tmp2->inh = node->inh;
        handle_DecList(tmp2);
        node->syn.f = insert_FieldList(tmp->syn.f,tmp2->syn.f);
    }
}

int handle_Dec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    tmp->inh = node->inh;
    if(tmp2 == NULL){
        int res = handle_VarDec(tmp);
        if(res == 1) node->syn = tmp->syn;
        return res;
    }
    else if(instruct == 1){
        char *inf = strcat("initilize feild \"",strcat(node->val.str,"\" when defining its struct."));
        insert_Error("15",node->line,inf);
        return 0;
    }
    else{
        int res = handle_VarDec(tmp);
        if(res == 1)
        {
            Define(tmp->syn.str);
            node->syn = tmp->syn;
        }
        return res;
    }
}

int handle_VarDec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    if(tmp2 == NULL){
        handle_ID(tmp);
        int res = try_insert(node->inh.t,node->line,tmp->syn.str);
        if(res == 1) node->syn.f = new_FieldList(tmp->syn.str,node->inh.t);
        return res;
    }
    else{
        tmp->inh.t = create_Array_Type(node->inh.t,tmp2->val.i);
        int res = handle_VarDec(tmp);
        if(res == 1) node->syn = tmp->syn;
        return res;
    }
}

int handle_FunDec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    FieldList f = NULL;
    handle_ID(tmp);
    if(tmp2->type == VarList)
    {
        handle_VarList(tmp2);
        f = tmp2->syn.f;
    }
    
}

void handle_CompSt(struct GrammarTree *node){
    ;
}

void handle_ID(struct GrammarTree *node){
    node->syn.str = node->val.str;
}

void handle_VarList(struct GrammarTree *node){

}

void handle_Exp(struct GrammarTree *node){

}

//NOTE