#ifndef MACHINECODE_H
#define MACHINECODE_H
#include "InterMediate.h"
struct Register
{
    int is_free;
    char *name;
    Operand content;
    int distance;
};

struct Register Regs[32]; //32个寄存器

struct StackNode //栈中某一位置存放的数据信息
{
    int offset;     //相对栈顶/栈底的偏移量，由具体实现决定是相对于栈底还是栈顶
    Operand op;     //当前位置存储的数据
    // int reg_number; //原来所在寄存器编号，若未被分配则该域无意义(-1)
    int distance;
    struct StackNode *next;
};

struct FunctionRecord //函数活动记录
{
    int size;//活动记录的大小
    struct StackNode *fp; //当前记录的栈底
    struct FunctionRecord *next;
};


struct FunctionRecord Records;//模拟栈中的过程调用序列
int is_main; //表示当前所在函数是否为main函数

void init_reg();
void init_data(FILE *fp);
void init_code(FILE *fp);
void init_block();
//涉及寄存器分配
int get_reg(FILE *fp, Operand op); 
int load_imm(FILE *fp, Operand op);    //装载一个立即数，返回该值所在寄存器编号

//有关主要机器码生成
int ensure_right(FILE *fp, Operand op,int dis);         //确保表达式寄存器和其内容的正确性,即确保对应寄存器中有其对应的数值，若是立即数或者地址类型则需要装载数据
void store(FILE *fp, Operand dst, Operand val,int dis_dst,int dis_val); //将一个value装载到目的地址
int load(FILE *fp, Operand dst, Operand src);   //从一个地址中装载数据到寄存器,返回寄存器编号
void translate_intercode(FILE *fp, struct InterCodes *start);
void generate_machine_code(FILE *fp);


int get_stack_offset(Operand op);
void push_arg(FILE *fp,Operand op);
int save(FILE *fp,int reg_idx);
int push(FILE *fp,int reg_idx);
void pop();
int get_unused_reg(FILE *fp);
int *save_regs(FILE *fp);
void load_regs(FILE *fp,int *a);
int stack_malloc(Operand op,int size);
void add_stacknode(Operand op,int offset);
#endif