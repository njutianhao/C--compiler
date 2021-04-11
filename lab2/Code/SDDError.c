#include "SDDError.h"
int try_insert_Node(int line,Type type_in,char* name){
    if(getKind(type_in) == FUNCTION)
    {
        Type t = search_function(name);
        if(t == NULL)
        {
            insert_Node(type_in,name);
        }
        else if(same(t,type_in) == 0)
        {
            char *inf = strcat("Inconsistent declaration of function \"",strcat(name,"\"."));
            insert_Error("19",line,inf);
            return 0;
        }
        else
            return 1;
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

int try_Define(int line,char *name){
    if(if_define(name) == -1)
    {
        Define(name);
        return 1;
    }
    else
    {
        char *inf = strcat("Redefined function \"",strcat(name,"\"."));
        insert_Error("4",line,inf);
        return 0;
    }
}

int check_return_type(int line,char *funcname,Type t){
    Type t1 = getReturnType(funcname);
    if(same(t1,t) == 0)
    {
        char *inf = "Type mismatched for return.";
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
        char *inf = strcat("Undefined structure \"",strcat(name,"\"."));
        insert_Error("17",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_undefined_var(int line,Type t,char *name){
    if(t == NULL)
    {
        char *inf = strcat("Undefined variable \"",strcat(name,"\"."));
        insert_Error("1",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_undefined_func(int line,Type t,char *name){
    if(t == NULL)
    {
        char *inf = strcat("Undefined function \"",strcat(name,"\"."));
        insert_Error("2",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_assign_type(int line,Type t1,Type t2){
    if(same(t1,t2) == 0)
    {
        char *inf = "Type mismatched for assignment.";
        insert_Error("5",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_instruct(int line,char *name){
    if(instruct == 1){
        char *inf = strcat("initilize feild \"",strcat(name,"\" when defining its struct."));
        insert_Error("15",line,inf);
        return 0;
    }
    return 1;
}

int check_paras(int line,FieldList f,char *name){
    if(check_paralist(name,f) == 0)
    {
        char *inf = strcat("Function \"",strcat(strcat(strcat(generateFuncStr(name),"\" is not applicable for arguments \""),generateStr(f)),"\"."));
        insert_Error("9",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_leftval(int line,int isleftval){
    if(isleftval == 0)
    {
        char *inf = "The left-hand side of an assignment must be a variable.";
        insert_Error("6",line,inf);
        return 0;
    }
    else
        return 0;
}

int check_oprands_type(int line,Type t1,Type t2){
    if(same(t1,t2) == 0)
    {
        char *inf = "Type mismatched for operands.";
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
        char *inf = strcat("\"",strcat(name,"\" is not a function."));
        insert_Error("11",line,inf);
        return 0;
    }
}

int check_array_type(int line,Type t){
    if(isArray(t) == 0)
    {
        char *inf = "use [] to not an array.";
        insert_Error("10",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_struct_type(int line,Type t){
    if(isStruct(t) == 0)
    {
        char *inf = "Illegal use of \".\".";
        insert_Error("13",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_int_in_array(int line,Type t){
    if(isInt(t) == 0)
    {
        char *inf = "the Exp in [] is not an integer.";
        insert_Error("12",line,inf);
        return 0;
    }
    else
        return 1;
}

int check_field_in_struct(int line,Type t,char *name){
    if(isInStruct(t,name) == 0)
    {
        char *inf = strcat("Non-existent field \"",strcat(name,"\"."));
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
        char *inf = strcat("Undefined function \"",strcat(name,"\"."));
        insert_Error("18",line,inf);
        p = p->next;
    }
    return 0;
}