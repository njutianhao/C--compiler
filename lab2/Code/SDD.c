#include"GrammarTree.h"
#include"syntax.tab.h"
#include"SDDError.h"

int instruct = 0;

char *get_VarDec_name(struct GrammarTree *node){
    if(node->type != ID)
        return get_VarDec_name(get_child(node,1));
    return node->val.str;
}

char *prepare_exp_name(struct GrammarTree *node){
    if(node->head == NULL)
    {
        char *res;
        switch(node->type){
            case ID:
                res = (char *)malloc(strlen(node->val.str) + 1);
                return strcpy(res,node->val.str);
            case INT:
                res = (char *)malloc(11);
                sprintf(res,"%d",node->val.i);
                return res;
            case FLOAT:
                res = (char *)malloc(50);
                sprintf(res,"%.6f",node->val.f);
                return res;
            default:
                res = (char *)malloc(strlen(token2_symbol_map[node->type - BASE_NUM]) + 1);
                return strcpy(res,token2_symbol_map[node->type - BASE_NUM]);
            }
    }
    struct ListNode *l = node->head;
    char *res = NULL;
    while(l != NULL){
        char *tmp = prepare_exp_name(l->val);
        if(res == NULL)
        {
            res = tmp;
        }
        else
        {
            char *str = malloc(strlen(res) + strlen(tmp) + 1);
            strcat(strcpy(str,res),tmp);
            free(res);
            free(tmp);
            res = str;
        }
        l = l->next;
    }
    return res;
}

int is_leftval(struct GrammarTree *node){
    struct GrammarTree *p = get_child(node,1);
    struct GrammarTree *n = get_child(node,2);
    while(p->head != NULL){
        n = get_child(p,2);
        p = get_child(p,1);
    }
    return p->type == ID && n == NULL;
}

struct GrammarTree *get_child(struct GrammarTree *node,int index){
    struct ListNode *head = node->head;
    for(int i = 1;i < index;i++)
    {
        if(head == NULL)
            return NULL;
        head = head->next;
    }
    if(head == NULL)
        return NULL;
    return head->val;
}

void SDT(){
    initTable();
    handle_ExtDefList(get_child(root,1));
    check_func_not_defined();
}

void handle_ExtDefList(struct GrammarTree *node){
    if(node == NULL || node -> head == NULL)
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
            if(handle_FunDec(tmp2) == 0)
                return ; 
            if(tmp3->type != CompSt)
            {
                if(try_insert_FuncNode(tmp2->line,tmp2->syn.func.t,tmp2->syn.func.name,0) == 0)
                    return ;
            }
            else
            {
                if(try_insert_FuncNode(tmp2->line,tmp2->syn.func.t,tmp2->syn.func.name,1) == 0)
                    return ;
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
        case TYPE:node->syn.t = create_Basic_Type(tmp->val.str);return 1;
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
            try_insert_all_FieldList(tmp2->syn.f);
            t = create_Structure_Type(tmp2->syn.f,tmp->syn.str);
            res = try_insert_struct(tmp->line,t,tmp->syn.str);
            instruct = old_instruct;
            if(res == 1)
            {
                node->syn.t = t;
            }
            return res;
        case Tag:
            handle_Tag(tmp);
            t = search_struct(tmp->syn.str);
            if(check_undefined_struct(tmp->line,t,tmp->syn.str) == 0)
                return 0;
            node->syn.t = t;
            return 1;
    }
}

void handle_Tag(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    handle_ID(tmp);
    node-> syn = tmp->syn;
}

void handle_OptTag(struct GrammarTree *node){
    struct GrammarTree* tmp = get_child(node,1);
    node->syn.str = NULL;
    if(tmp == NULL)
        return;
    if(tmp->type == ID){
        handle_ID(tmp);
        node->syn.str = tmp->syn.str;
    }
}

void handle_DefList(struct GrammarTree *node){
    node->syn.f = NULL;
    if(node->head == NULL)
        return;
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    handle_Def(tmp);  
    handle_DefList(tmp2);
    if(check_FieldList(tmp->syn.f,tmp2->syn.f,instruct) == 0)
        return;
    node->syn.f = insert_FieldList(tmp->syn.f,tmp2->syn.f);
}

void handle_Def(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    node->syn.f = NULL;
    if(handle_Specifier(tmp) == 0)
        return ;
    tmp2->inh = tmp->syn;
    handle_DecList(tmp2);
    node->syn = tmp2->syn;
}

void handle_DecList(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    tmp->inh = node->inh;
    node->syn.f = NULL;
    int res = handle_Dec(tmp);
    if(res == 1)
        node->syn = tmp->syn;
    if(tmp2 != NULL)
    { 
        tmp2->inh = node->inh;
        handle_DecList(tmp2);
        if(check_FieldList(tmp->syn.f,tmp2->syn.f,instruct) == 0)
        {
            return;
        }
        node->syn.f = insert_FieldList(tmp->syn.f,tmp2->syn.f);
    }
}

int handle_Dec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    tmp->inh = node->inh;
    node->syn.f = NULL;
    if(tmp2 == NULL){
        if(handle_VarDec(tmp) == 0)
            return 0;
        node->syn = tmp->syn;
        return 1;
    }
    else
    {
        if(check_instruct(node->line,get_VarDec_name(tmp)) == 0 || handle_VarDec(tmp) == 0 ||handle_Exp(tmp2) == 0)
            return 0;
        if(check_assign_type(tmp->line,getListHeadType(tmp->syn.f),tmp2->syn.t) == 0)
            return 0;
        node->syn = tmp->syn;
        return 1;
    } 
}

int handle_VarDec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    node->syn.f = NULL;
    if(tmp2 == NULL){
        handle_ID(tmp);
        node->syn.f = new_FieldList(tmp->syn.str,node->inh.t,tmp->line);
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
    node->syn.func.name = tmp->syn.str;
    node->syn.func.t = create_Function_Type(node->inh.t,f,tmp->line);
    return 1;
}

void handle_CompSt(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,2);
    struct GrammarTree *tmp2 = get_child(node,3);
    handle_DefList(tmp);
    try_insert_all_FieldList(tmp->syn.f);
    free_FieldList(tmp->syn.f);
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
    node->syn.f = NULL;
    if(tmp2 != NULL)
    {
        handle_VarList(tmp2);
        node->syn = tmp2->syn;
    }
    if(try_insert_all_FieldList(tmp->syn.f) == 0)
        return 0;
    if(tmp2 != NULL)
        node->syn.f = insert_FieldList(tmp->syn.f,tmp2->syn.f);
    else
        node->syn = tmp->syn;
    return 1;
}

int handle_ParamDec(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    node->syn.f = NULL;
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

int handle_Stmt(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2;
    struct GrammarTree *tmp3;
    struct GrammarTree *tmp4;
    int res;
    switch(tmp->type){
        case Exp: handle_Exp(tmp);break;
        case CompSt: tmp->inh = node->inh;handle_CompSt(tmp);break;
        case RETURN: 
            tmp2 = get_child(node,2);
            handle_Exp(tmp2);
            if(check_return_type(tmp->line,node->inh.str,tmp2->syn.t) == 0)
                return 0;
            break;
        case IF:
            tmp2 = get_child(node,3);
            tmp3 = get_child(node,5);
            tmp4 = get_child(node,7);
            res = handle_Exp(tmp2);
            tmp3->inh = node->inh;
            handle_Stmt(tmp3);
            if(tmp4 != NULL)
            {
                tmp4->inh = node->inh;
                handle_Stmt(tmp4);
            }
            if(res == 0)
                return 0;
            if(check_condition_type(tmp2->line,tmp2->syn.t) == 0)
                return 0;
            break;
        case WHILE:
            tmp2 = get_child(node,3);
            tmp3 = get_child(node,5);
            res = handle_Exp(tmp2);
            tmp3->inh = node->inh;
            handle_Stmt(tmp3);
            if(res == 0)
                return 0;
            if(check_condition_type(tmp2->line,tmp2->syn.t) == 0)
                return 0;
            break;
    }
    return 1;
}

void handle_ExtDecList(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    tmp->inh = node->inh;
    if(handle_VarDec(tmp) != 0)
    {
        try_insert_all_FieldList(tmp->syn.f);
        free_FieldList(tmp->syn.f);
    }
    if(tmp2 != NULL)
    {
        tmp2->inh = node->inh;
        handle_ExtDecList(tmp2);
    }
}

int handle_Exp(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,2);
    struct GrammarTree *tmp3 = get_child(node,3);
    FieldList f = NULL;
    Type t;
    char *name;
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
            if(tmp3 == NULL)
            {
                t = search_with_name(tmp->syn.str);
                if(check_undefined_var(tmp->line,t,tmp->syn.str) == 0)
                    return 0;
                node->syn.t = t;
                return 1;
            }
            else
            {       
                t = search_with_name(tmp->syn.str);
                if(check_use_var_as_func(tmp->line,t,tmp->syn.str) == 0)
                    return 0;
                t = search_function(tmp->syn.str);
                if(check_undefined_func(tmp->line,t,tmp->syn.str) == 0)
                    return 0;
                f = NULL;
                switch(tmp3->type){
                    case Args:
                        if(handle_Args(tmp3) == 0)
                            return 0;
                        f = tmp3->syn.f;
                        //NO break
                    case RP:
                        if(check_paras(tmp->line,f,tmp->syn.str) == 0)
                            return 0;    
                        node->syn.t = getReturnType(tmp->syn.str);
                        return 1;
                }
                printf("wrong in handle_Exp\n");
                exit(0);
            }
        case Exp:
            switch(tmp2->type){
                case ASSIGNOP:
                    if(handle_Exp(tmp) == 0 || handle_Exp(tmp3) == 0)
                        return 0;
                    if(check_leftval(tmp->line,is_leftval(tmp)) == 0)
                        return 0;
                    if(check_assign_type(tmp->line,tmp->syn.t,tmp3->syn.t) == 0)
                        return 0;
                    node->syn = tmp->syn;
                    return 1;
                case AND:
                case OR:
                case RELOP:
                case PLUS:
                case SUB:
                case STAR:
                case DIV:
                    if(handle_Exp(tmp) == 0 || handle_Exp(tmp3) == 0)
                        return 0;
                    if(check_oprands_type(tmp->line,tmp->syn.t,tmp3->syn.t) == 0)
                        return 0;
                    node->syn = tmp->syn;
                    return 1;
                case LB:
                    if(handle_Exp(tmp) == 0 || handle_Exp(tmp3) == 0)
                        return 0;
                    name = prepare_exp_name(tmp);
                    if(check_array_type(tmp->line,tmp->syn.t,name) == 0)
                        return 0;
                    name = prepare_exp_name(tmp3);
                    if(check_int_in_array(tmp3->line,tmp3->syn.t,name) == 0)
                        return 0;
                    node->syn.t = getLowerArray(tmp->syn.t);
                    return 1;
                case DOT:
                    if(handle_Exp(tmp) == 0)
                        return 0;
                    handle_ID(tmp3);
                    if(check_struct_type(tmp->line,tmp->syn.t) == 0)
                        return 0;
                    if(check_field_in_struct(tmp->line,tmp->syn.t,tmp3->syn.str) == 0)
                        return 0;
                    node->syn.t = getFieldType(tmp->syn.t,tmp3->syn.str);
                    return 1;
            }
    }
}

int handle_Args(struct GrammarTree *node){
    struct GrammarTree *tmp = get_child(node,1);
    struct GrammarTree *tmp2 = get_child(node,3);
    if(handle_Exp(tmp) == 0)
        return 0;
    FieldList f = new_FieldList(NULL,tmp->syn.t,tmp->line);
    node->syn.f = f;
    if(tmp2 != NULL){
        if(handle_Args(tmp2) == 0)
            return 0;
        node->syn.f = insert_FieldList(f,tmp2->syn.f);
    }
    return 1;
}