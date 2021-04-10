#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 0x3fff

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
enum  KIND { BASIC_INT,BASIC_FLOAT, ARRAY, STRUCTURE ,FUNCTION};
struct Type_
{
    enum KIND kind; 
    union
    {
        struct 
        { 
            Type elem; 
            int size; 
        } array;// 数组类型信息包括元素类型、数组大小
        struct 
        {
            char* structName;//结构体名称
            FieldList structmember;// 结构体类型信息是一个链表
        } structure;
        struct 
        {
            Type returnType;//返回值类型
            FieldList paramlist;//参数列表
        } function;  
    } u; 
};

struct FieldList_
{
    char* name; // 域的名字 
    Type type; // 域的类型
    FieldList next; // 下一个域
};

struct TableNode
{
    char* name;//变量或函数名
    Type type;
    int ifdef;//是否经过定义或初始化，未定义或未初始化则置0
    struct TableNode* next;//hash表下一个元素指针
};


struct TableNode* SymbolTable[TABLE_SIZE];//符号表

void initTable();//初始化
unsigned int hash_pjw(char* name);//hash函数

void insert_Node(Type type_in,char* name,int if_def);//插入新的节点
Type search_with_name(char* Name);//根据名字查询节点
//int search_struct_with_type(Type type_in);//对于没有name的结构体只能根据type查找,返回是否存在等价structure,是为1，不是为0
int name_exist(char* name);//某一变量、形参或者成员名是否已存在,是则返回1,不是则返回0

Type create_Basic_Type(char* ifint);//创建Basic type类型
Type create_Array_Type(Type paratype,int size_in);//创建Array type类型
Type create_Structure_Type(FieldList head,char* struct_Name);//创建Structure type类型
Type create_Function_Type(Type returntype,FieldList List);//创建Funtion type类型,若为函数声明，if_def设置为0
int  Define(char* name);//声明后又定义,返回0为正常定义,返回1为存在重复定义
int if_define(char* name);//检查是否定义

FieldList new_FieldList(char* name_in,Type type_in);//创建一个FieldList节点
FieldList insert_FieldList(FieldList head,FieldList ptr);//向FieldList链表内插入节点

int same(Type A,Type B);//检查是否为同一类型，是则返回1,不是则返回0,异常则返回-1
//int strict_array_same(Type A,Type B);//检查数组严格相等,返回值同same()
enum KIND getKind(Type type);//type转KIND

#endif