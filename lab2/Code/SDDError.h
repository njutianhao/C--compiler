#ifndef SDDERROR_H
#define SDDERROR_H
#include"GrammarTree.h"
#include"Error.h"
#include"syntax.tab.h"

int try_insert_all_FieldList(FieldList f);

int try_insert_Node(int line,Type type_in,char* name);

int try_insert_FuncNode(int line,Type type_in,char* name,int define);

int try_insert_struct(int line,Type type_in,char *name);

int check_FieldList(FieldList p1,FieldList p2,int instruct);

int check_return_type(int line,char *funcname,Type t);

int check_condition_type(int line,Type t);

int check_undefined_struct(int line,Type t,char *name);

int check_undefined_var(int line,Type t,char *name);
//use undefined func 
int check_undefined_func(int line,Type t,char *name);

int check_use_var_as_func(int line,Type t,char *name);

int check_assign_type(int line,Type t1,Type t2);

int check_oprands_type(int line,Type t1,Type t2);

int check_instruct(int line,char *name);

int check_paras(int line,FieldList f,char *name);

int check_leftval(int line,int isleftval);

int check_array_type(int line,Type t,char *name);

int check_struct_type(int line,Type t);

int check_int_in_array(int line,Type t,char *name);

int check_field_in_struct(int line,Type t,char *name);
//never defined func
int check_func_not_defined();
#endif