#include "SDDError.h"

int try_insert_all_FieldList(FieldList f){
    int res = 1;
    while(f != NULL){
        if(try_insert_Node(getFieldListLine(f),getFieldListType(f),getFieldListName(f)) == 0)
            res = 0;
        f = getNextFieldList(f);
    }
    return res;
}

int try_insert_struct(int line,Type type_in,char *name){
    if(name_exist(name) == 0)
    {
        insert_Node(type_in,name);  
        return 1;
    }
    else
    {
        char *s1 = "Duplicated name \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("16",line,inf);
        return 0;
    }
}

int try_insert_Node(int line,Type type_in,char* name){
    if(getKind(type_in) == FUNCTION)
    {
        printf("wrong in try_insert_Node\n");
        exit(0);
    }
    else if(name_exist(name) == 0)
    {
        insert_Node(type_in,name);  
        return 1;
    }
    else
    {
        char *s1 = "Redefined variable \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("3",line,inf);
        return 0;
    }
}

int try_insert_FuncNode(int line,Type type_in,char* name,int define){
    if(getKind(type_in) != FUNCTION)
    {
        printf("wrong in try_insert_FuncNode\n");
        exit(0);
    }
    Type t = search_function(name);
    if(t == NULL)
    {
        insert_Node(type_in,name);
        if(define == 1)
            Define(name);
        return 1;
    }
    else if(if_define(name) == 1 && define == 1){
        char *s1 = "Redefined function \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("4",line,inf);
        return 0;
    }
    else if(same(t,type_in) == 0)
    {
        char *s1 = "Inconsistent declaration of function \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("19",line,inf);
        return 0;
    }
    else
    {
        if(define == 1)
            Define(name);
        return 1;
    }
}

FieldList check_FieldList(FieldList p1,FieldList p2){
    FieldList res = malloc(sizeof(FieldList));
    FieldList f = FieldList_repeat(p1,p2,&res);
    if(f == NULL){
        ;
    }
    else{
        char *s1 = "Redefined field \"";
        char *s2 = "\"";
        while(f != NULL)
        {
            char *name = getFieldListName(p1);
            char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
            char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
            insert_Error("15",getFieldListLine(f),inf);
            f = getNextFieldList(f);
        }
    }
    free_FieldList(f);
    return res;
}

int check_return_type(int line,char *funcname,Type t){
    Type t1 = getReturnType(funcname);
    if(same(t1,t) == 0)
    {
        char *inf = "Type mismatched for return";
        insert_Error("8",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_condition_type(int line,Type t){
    if(isInt(t) == 1)
        return 1;
    else{
        char *inf = "Use wrong type for condition";
        insert_Error("20",line,inf);
        return 0;
    }
}

int check_undefined_struct(int line,Type t,char *name){
    if(t == NULL)
    {
        char *s1 = "Undefined structure \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("17",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_undefined_var(int line,Type t,char *name){
    if(t == NULL)
    {
        char *s1 = "Undefined variable \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("1",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_undefined_func(int line,Type t,char *name){
    if(t == NULL)
    {
        char *s1 = "Undefined function \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2));
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("2",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_assign_type(int line,Type t1,Type t2){
    if(same(t1,t2) == 0)
    {
        char *inf = "Type mismatched for assignment";
        insert_Error("5",line,inf);
        return 0;
    }
    else{
        return 1;

    }
}

int check_instruct(int line,char *name){
    if(instruct == 1){
        char *s1 = "initilize feild \"";
        char *s2 = "\" when defining its struct";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("15",line,inf);
        return 0;
    }
    return 1;
}

int check_paras(int line,FieldList f,char *name){
    if(check_paralist(name,f) == 0)
    {
        char *s1 = "Function \"";
        char *s2 = generateFuncStr(name);
        char *s3 = "\" is not applicable for arguments \"";
        char *s4 = generateStr(f);
        char *s5 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + strlen(s5) + 1);
        char *inf = strcat(strcat(strcat(strcat(strcpy(tmp,s1),s2),s3),s4),s5);
        insert_Error("9",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_leftval(int line,int isleftval){
    if(isleftval == 0)
    {
        char *inf = "The left-hand side of an assignment must be a variable";
        insert_Error("6",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_oprands_type(int line,Type t1,Type t2){
    if(same(t1,t2) == 0)
    {
        char *inf = "Type mismatched for operands";
        insert_Error("7",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_use_var_as_func(int line,Type t,char *name){
    if(t == NULL)
        return 1;
    else
    {
        char *s1 = "\"";
        char *s2 = "\" is not a function";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("11",line,inf);
        return 0;
    }
}

int check_array_type(int line,Type t,char *name){
    if(isArray(t) == 0)
    {
        char *s1 = "\"";
        char *s2 = "\" is not an array";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        free(name);
        insert_Error("10",line,inf);
        return 0;
    }
    else
    {
        free(name);
        return 1;
    }
}

int check_struct_type(int line,Type t){
    if(isStruct(t) == 0)
    {
        char *inf = "Illegal use of \".\"";
        insert_Error("13",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_int_in_array(int line,Type t,char *name){
    if(isInt(t) == 0)
    {
        char *s1 = "\"";
        char *s2 = "\" is not an integer";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        free(name);
        insert_Error("12",line,inf);
        return 0;
    }
    else
    {
        free(name);
        return 1;
    }
        
}

int check_field_in_struct(int line,Type t,char *name){
    if(isInStruct(t,name) == 0)
    {
        char *s1 = "Non-existent field \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("14",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_func_not_defined(){
    struct UndefinedFunction *p= get_undefined_function();
    if(p == NULL)
        return 1;
    while(p != NULL)
    {
        char *name = p->func_name;
        int line = p->line;
        char *s1 = "Undefined function \"";
        char *s2 = "\"";
        char *tmp = (char *)malloc(strlen(s1) + strlen(name) + strlen(s2) + 1);
        char *inf = strcat(strcat(strcpy(tmp,s1),name),s2);
        insert_Error("18",line,inf);
        p = p->next;
    }
    return 0;
}