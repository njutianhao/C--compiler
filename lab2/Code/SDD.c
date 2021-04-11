#include"GrammarTree.h"
#include"syntax.tab.h"

int instruct = 0;

int try_insert_Node(int line,Type type_in,char* name){
    if(getKind(type_in) == FUNCTION)
    {

    }
    else if(name_exist(name) == 0)
    {
        insert_Node(type_in,name);  
        return 1;
    }
    else if(search_struct(name) == NULL)
    {
        char *inf = strcat("Redefined variable \"",strcat(name,"\"."));
        insert_Error("3",line,inf);
        return 0;
    }
    else
    {
        char *inf = strcat("Duplicated name \"",strcat(name,"\"."));
        insert_Error("16",line,inf);
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
    if(handle_Specifier(tmp1) == 0)
        return ;
    tmp2->inh = tmp1->syn;
    switch(tmp2->type){
        case FunDec:
            tmp2->inh = tmp1->syn;
            if(handle_FunDec(tmp2) == 0)
                return ; 
            if(tmp3->type == CompSt)
            {
                Define(tmp2->syn.str);
                tmp3->inh = tmp2->syn;
                handle_CompSt(tmp3);
            }
            break;
        case ExtDecList:
            handle_ExtDecList(tmp2);
            break;
    }
}

int handle_Specifier(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    switch(tmp->type){
        case TYPE:node->syn.t = create_Basic_Type(tmp->val.str); return 1;
        case StructSpecifier:
            if(handle_StructSpecifier(tmp) == 0)
                return 0;
            node->syn = tmp->syn;
            return 1;
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
                char *inf = strcat("Undefined structure \"",strcat(tmp->syn.str,"\"."));
                insert_Error("17",tmp->line,inf);
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
        if(handle_VarDec(tmp) == 0)
            return 0;
        node->syn = tmp->syn;
        return 1;
    }
    else if(instruct == 1){
        char *inf = strcat("initilize feild \"",strcat(node->val.str,"\" when defining its struct."));
        insert_Error("15",node->line,inf);
        return 0;
    }
    else{
        if(handle_VarDec(tmp) == 0)
            return 0;
        if(handle_Exp(tmp2) == 0)
            return 0;
        if(same(getListHeadType(tmp->syn.f),tmp2->syn.t) == 0)
        {
            char *inf = "Type mismatched for assignment.";
            insert_Error("5",tmp->line,inf);
            return 0;
        }
        node->syn = tmp->syn;
        return 1;
    }
}

int handle_VarDec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    if(tmp2 == NULL){
        handle_ID(tmp);
        if(try_insert(node->inh.t,node->line,tmp->syn.str) == 0)
            return 0;
        node->syn.f = new_FieldList(tmp->syn.str,node->inh.t);
        return 1;
    }
    else{
        tmp->inh.t = create_Array_Type(node->inh.t,tmp2->val.i);
        if(handle_VarDec(tmp) == 0)
            return 0;
        node->syn = tmp->syn;
        return 1;
    }
}

int handle_FunDec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    FieldList f = NULL;
    handle_ID(tmp);
    if(tmp2->type == VarList)
    {
        if(handle_VarList(tmp2) == 0)
            return 0;
        f = tmp2->syn.f;
    }
    node->syn = tmp->syn;
    return try_insert(create_Function_Type(node->inh.t,f,tmp->syn.str),tmp->line,tmp->syn.str);
}

void handle_CompSt(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,2);
    struct GrammarTree *tmp2 = get_child(node,3);
    handle_DefList(tmp);
    tmp2->inh = node->inh;
    handle_StmtList(tmp2);
}

void handle_ID(struct GrammarTree *node){
    node->syn.str = node->val.str;
}

int handle_VarList(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    handle_ParamDec(tmp);
    FieldList f = NULL;
    if(tmp2 != NULL)
    {
        handle_VarList(tmp2);
        f = tmp2->syn.f;
    }
    node->syn.f = insert_FieldList(tmp->syn.f,f);
}

int handle_ParamDec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    if(handle_Specifier(tmp) == 0)
        return 0;
    tmp2->inh = tmp->syn;
    handle_VarDec(tmp2);
    node->syn = tmp2->syn;
    return 1;
}

void handle_StmtList(struct GrammarTree *node){
    if(node->head == NULL)
        return ;
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    tmp->inh = node->inh;
    tmp2->inh = node->inh;
    handle_Stmt(tmp);
    handle_StmtList(tmp2);
}

void handle_Stmt(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2;
    struct GrammarTree *tmp3;
    struct GrammarTree *tmp4;
    switch(tmp->type){
        case Exp: handle_Exp(tmp);break;
        case CompSt: handle_CompSt(tmp);break;
        case RETURN: 
            tmp2 = get_child(node,2);
            handle_Exp(tmp2);
             //TODO:RETURN TYPE UNMATCH
            break;
        case IF:
            tmp2 = get_child(node,3);
            tmp3 = get_child(node,5);
            tmp4 = get_child(node,7);
            handle_Exp(tmp2);
            tmp3->inh = node->inh;
            handle_Stmt(tmp3);
            if(tmp4 != NULL)
            {
                tmp4->inh = node->inh;
                handle_Stmt(tmp4);
            }
            break;
        case WHILE:
            tmp2 = get_child(node,3);
            tmp3 = get_child(node,5);
            handle_Exp(tmp2);
            tmp3->inh = node->inh;
            handle_Stmt(tmp3);
            break;
    }
}

void handle_ExtDecList(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    handle_VarDec(tmp);
    free_FieldList(tmp->syn.f);
    if(tmp2 != NULL)
        handle_ExtDecList(tmp2);
}

int handle_Exp(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    struct GrammarTree *tmp3 = get_child(node,3);
    FieldList f = NULL;
    switch(tmp->type){
        case INT:node->syn.t = create_Basic_Type("int");return 1;
        case FLOAT:node->syn.t = create_Basic_Type("float");return 1;
        case LP:
            if(handle_Exp(tmp2) == 0)
                return 0;
            node->syn = tmp2->syn;
            return 1;
        case MINUS:
            if(handle_Exp(tmp2) == 0)
                return 0;
            node->syn = tmp2->syn;
            return 1;
        case NOT:
            if(handle_Exp(tmp2)== 0)
                return 0;
            node->syn = tmp2->syn;
            return 1;
        case ID:
            handle_ID(tmp);
            if(tmp3->type == NULL)
            {
                node->syn.t = search_with_name(tmp->syn.str); //TODO:undefined
                return 1;
            }
            else
            {
                f = NULL;
                switch(tmp3->type){
                    case Args:handle_Args(tmp3);
                        f = tmp3->syn.f;
                        //NO break
                    case RP:if(check_paralist(tmp->syn.str,f) == 0)
                        {
                            //TODO:
                            return 0;
                        }
                        node->syn.t = getReturnType(tmp->syn.str);
                        return 1;
                }
                printf("wrong in handle_Exp\n");
                exit(0);
            }
        case Exp:
            switch(tmp2->type){
                case ASSIGNOP:
                case AND:
                case OR:
                case RELOP:
                case PLUS:
                case MINUS:
                case STAR:
                case DIV:
                    handle_Exp(tmp);
                    handle_Exp(tmp3);
                    if(same(tmp->syn.t,tmp3->syn.t) == 0)
                    {
                        //TODO:
                        return 0;
                    }
                    node->syn = tmp->syn.t;
                    return 1;
                case LB://TODO
                case DOT://TODO
            }
    }
}

void handle_Args(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    handle_Exp(tmp);
    FieldList f = new_FieldList(NULL,tmp);
    node->syn.f = f;
    if(tmp2 != NULL){
        handle_Args(tmp2);
        node->syn.f = insert_FieldList(f,tmp2->syn.f);
    }
}