#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
//TO DO
typedef struct Operand_ * Operand;
struct Operand_
{
    enum
    {
        OP_VARIABLE,
        OP_CONSTANT,
        OP_ADDRESS,
        OP_FUNCTION,
        OP_LABEL,
        OP_RELOP
    } kind;
    struct
    {
        //int order;//v,t的序号
        int value;
        char *name;//保存函数&变量名
        char *vname;
    } u;
};

struct InterCode
{
    enum
    {
        IR_ASSIGN,
        IR_ADD,
        IR_SUB,
        IR_MUL,
        IR_DIV,
        IR_FUNCTION,
        IR_PARAM,
        IR_LABEL,
        IR_IFGOTO,
        IR_GOTO,
        IR_CALL,
        IR_READ,
        IR_WRITE,
        IR_ARG,
        IR_RETURN,
        IR_DEC,
        IR_ASSIGNADDR,
        IR_ADD_ADDR
    } kind;
    union
    {
        Operand single;
        struct
        {
            Operand right, left;
        } assign;
        struct
        {
            Operand result, op1, op2;
        } binop;
        struct 
        {
            Operand op1,relop,op2,label;
        } control;
    } u;
};

struct InterCodes {
    struct InterCode code;
    struct InterCodes *prev, *next; 
};

struct InterCodes head;

//TO DO 存储结构
struct OperandList
{
    Operand operand;
    struct OperandList* next;
};
//TO COMPLETE 函数接口

void init();
void add_operand(Operand operand,struct OperandList ** head);
Operand new_temp();//对于保存同一int型常量的t，可以不再重复产生
Operand new_label();
Operand new_variable();
//下列两个函数需要维护每一个变量variable的中间代码名v1，v2等，如果对于给出的变量名已存在对应的operand则无需创建新的operand
Operand new_char_Operand(char *name, int OpKind);
Operand new_int_Operand(int val, int OpKind);

void create_InterCode_oneOp(Operand op, int CodeKind);
void create_InterCode_twoOp(Operand op1,Operand op2,int CodeKind);
void create_InterCode_threeOp(Operand op1,Operand op2,Operand op3,int CodeKind);
void create_InterCode_fourOp(Operand op1,Operand relop,Operand op2,Operand label,int CodeKind);

void renew_int(Operand op,int value,int OpKind);
void renew_char(Operand op,char* name,int OpKind);

void generateCode(char *fileName);

void set_Op_address(Operand op);
void set_Op_name(Operand op,char* name);
int  get(Operand op,char* name);
#endif