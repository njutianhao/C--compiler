#include "MachineCode.h"

struct tmp_symbol{
    Operand op;
    struct tmp_symbol *next;
    int pos;
};

void init_reg()
{
    for (int i = 0; i < 32; i++)
    {
        Regs[i].is_free = 1;
        Regs[i].content = NULL;
    }
    Regs[0].name = "$zero";
    Regs[1].name = "$at";
    Regs[2].name = "$v0";
    Regs[3].name = "$v1";

    Regs[4].name = "$a0";
    Regs[5].name = "$a1";
    Regs[6].name = "$a2";
    Regs[7].name = "$a3";

    Regs[8].name = "$t0";
    Regs[9].name = "$t1";
    Regs[10].name = "$t2";
    Regs[11].name = "$t3";
    Regs[12].name = "$t4";
    Regs[13].name = "$t5";
    Regs[14].name = "$t6";
    Regs[15].name = "$t7";

    Regs[16].name = "$s0";
    Regs[17].name = "$s1";
    Regs[18].name = "$s2";
    Regs[19].name = "$s3";
    Regs[20].name = "$s4";
    Regs[21].name = "$s5";
    Regs[22].name = "$s6";
    Regs[23].name = "$s7";

    Regs[24].name = "$t8";
    Regs[25].name = "$t9";

    Regs[26].name = "$k0";
    Regs[27].name = "$k1";

    Regs[28].name = "$gp";
    Regs[29].name = "$sp";
    Regs[30].name = "$fp";
    Regs[31].name = "$ra";
}
void init_data(FILE *fp) //填写数据段
{
    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
}

void init_code(FILE *fp) //填写代码段开始部分，主要是read和write函数
{
    fprintf(fp, ".text\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _prompt\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 5\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  jr $ra\n\n");

    fprintf(fp, "write:\n");
    fprintf(fp, "  li $v0, 1\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _ret\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  move $v0, $0\n");
    fprintf(fp, "  jr $ra\n"); //返回地址
}

void set_distance(struct tmp_symbol *head,int pos,int *dst,Operand op){
    struct tmp_symbol *p = head->next;
    struct tmp_symbol *prev = head;
    while(p != NULL)
    {
        if(op == p->op)
        {
            *dst = pos - p->pos;
            p->pos = pos;
            return ;
        }
        prev = p;
        p = p->next;
    }
    prev->next = malloc(sizeof(struct tmp_symbol));
    p = prev->next;
    p ->next = NULL;
    p->op = op;
    p->pos = pos;
    *dst = 2147483647;
}

void init_block(){
    struct InterCodes *p = head.next;
    struct InterCodes *tmp;
    while(p != &head)
    {
        switch(p->code.kind)
        {
            case IR_GOTO:case IR_IFGOTO:
            tmp = p->next;
            p->next = malloc(sizeof(struct InterCodes));
            p->next->next = tmp;
            tmp->prev = p->next;
            p->next->prev = p;
            p->next->code.kind = SPLIT_POINT;
            break;
            case IR_LABEL:
            tmp = p->prev;
            tmp->next = malloc(sizeof(struct InterCodes));
            tmp->next->next = p;
            tmp->next->prev = tmp;
            p->prev = tmp->next;
            tmp->next->code.kind = SPLIT_POINT;
            break;
        }
        p = p ->next;
    }
    p = head.prev;
    struct tmp_symbol symbol_head;
    symbol_head.next = NULL;
    int pos = 0;
    while(p != &head)
    {
        if(p->code.kind == SPLIT_POINT)
        {
            pos = 0;
            struct tmp_symbol *q = symbol_head.next;
            while(q != NULL){
                struct tmp_symbol *tmp2 = q->next;
                free(q);
                q = tmp2;
            }
            symbol_head.next = NULL;
            p = p->prev;
            continue;
        }
        switch(p->code.opnum)
        {
            case 4:
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[3]),p->code.u.control.label);
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[2]),p->code.u.control.op2);
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[1]),p->code.u.control.relop);
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[0]),p->code.u.control.op1);
                break;
            case 3:
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[2]),p->code.u.binop.op2);
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[1]),p->code.u.binop.op1);
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[0]),p->code.u.binop.result);
                break;
            case 2:
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[1]),p->code.u.assign.left);
                set_distance(&symbol_head,pos,&(p->code.next_op_distance[0]),p->code.u.assign.right);
                break;
            case 1:set_distance(&symbol_head,pos,&(p->code.next_op_distance[0]),p->code.u.single);break;
            default:assert(0);
        }
        p = p->prev;
        pos++;
    }
    struct tmp_symbol *f = symbol_head.next;
    while(f != NULL)
    {
        free(f);
        f = f->next;
    }
}

int ensure_right(FILE *fp, Operand op,int dis)
{
    if (op->kind == OP_ADDRESS)
    {
        return load_data(fp, op);
    }
    else if (op->kind == OP_CONSTANT)
    {
        return load_imm(fp, op);
    }
    else
        return get_reg(fp, op,dis);
}
void store(FILE *fp, Operand dst, Operand val,int dis_dst, int dis_val) //将一个value装载到目的地址
{
    int reg_dst = get_reg(fp, dst,dis_dst);
    int reg_val = ensure_right(fp, val,dis_val);
    fprintf(fp, "  sw %s, 0(%s)\n", Regs[reg_val].name, Regs[reg_dst].name);
}

/*int load(FILE *fp, Operand dst, Operand src) //从一个地址中装载数据到寄存器
{
    int reg_dst = get_reg(fp, dst);
    int reg_src = get_reg(fp, src);
    fprintf(fp, "  lw %s, 0(%s)\n", Regs[reg_dst].name, Regs[reg_src].name);
    return reg_dst;
}*/
void translate_intercode(FILE *fp, struct InterCodes *start)
{
    struct InterCodes *p = start;
    while (p != &head)
    {
        switch (p->code.kind)
        {
        case IR_LABEL:
        {
            fprintf(fp, "%s:\n", p->code.u.single->u.vname);
            break;
        }
        case IR_ADD:
        {
            Operand op1 = p->code.u.binop.op1;
            Operand op2 = p->code.u.binop.op2;
            Operand res = p->code.u.binop.result;
            if (op1->kind == OP_CONSTANT && op2->kind == OP_CONSTANT)
            {
                int val = op1->u.value + op2->u.value;
                if (res->kind == OP_ADDRESS)
                {
                    store(fp, res, new_int_Operand(val, OP_CONSTANT),p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    int reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  li %s, %d\n", Regs[reg_res].name, val);
                }
            }
            else if (op1->kind == OP_CONSTANT)
            {
                int reg_res, reg2;
                reg2 = ensure_right(fp, op2,p->code.next_op_distance[2]);
                if (res->kind == OP_ADDRESS)
                {
                    Operand t = new_temp();
                    int reg_tmp = get_reg(fp, t,2147483647);
                    fprintf(fp, "  addi %s, %s, %d\n", Regs[reg_tmp].name, Regs[reg2].name, op1->u.value);
                    store(fp, res, t,p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  addi %s, %s, %d\n", Regs[reg_res].name, Regs[reg2].name, op1->u.value);
                }
            }
            else if (op2->kind == OP_CONSTANT)
            {
                int reg_res, reg1;
                reg1 = ensure_right(fp, op1,p->code.next_op_distance[1]);
                if (res->kind == OP_ADDRESS)
                {
                    Operand t = new_temp();
                    int reg_tmp = get_reg(fp, t,2147483647);
                    fprintf(fp, "  addi %s, %s, %d\n", Regs[reg_tmp].name, Regs[reg1].name, op2->u.value);
                    store(fp, res, t,p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  addi %s, %s, %d\n", Regs[reg_res].name, Regs[reg1].name, op2->u.value);
                }
            }
            else
            {
                int reg_res, reg1, reg2;
                reg1 = ensure_right(fp, op1,p->code.next_op_distance[1]);
                reg2 = ensure_right(fp, op2,p->code.next_op_distance[2]);
                if (res->kind == OP_ADDRESS)
                {
                    Operand t = new_temp();
                    int reg_tmp = get_reg(fp, t,2147483647);
                    fprintf(fp, "  add %s, %s, %s\n", Regs[reg_tmp].name, Regs[reg1].name, Regs[reg2].name);
                    store(fp, res, t,p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  add %s, %s, %s\n", Regs[reg_res].name, Regs[reg1].name, Regs[reg2].name);
                }
            }
            break;
        }
        case IR_SUB:
        {
            Operand op1 = p->code.u.binop.op1;
            Operand op2 = p->code.u.binop.op2;
            Operand res = p->code.u.binop.result;
            if (op1->kind == OP_CONSTANT && op2->kind == OP_CONSTANT)
            {
                int val = op1->u.value - op2->u.value;
                if (res->kind == OP_ADDRESS)
                {
                    store(fp, res, new_int_Operand(val, OP_CONSTANT),p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    int reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  li %s, %d\n", Regs[reg_res].name, val);
                }
            }
            else if (op2->kind == OP_CONSTANT)
            {
                int reg_res, reg1;
                reg1 = ensure_right(fp, op1,p->code.next_op_distance[1]);
                if (res->kind == OP_ADDRESS)
                {
                    Operand t = new_temp();
                    int reg_tmp = get_reg(fp, t,2147483647);
                    fprintf(fp, "  addi %s, %s, %d\n", Regs[reg_tmp].name, Regs[reg1].name, -op2->u.value);
                    store(fp, res, t,p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  addi %s, %s, %d\n", Regs[reg_res].name, Regs[reg1].name, -op2->u.value);
                }
            }
            else
            {
                int reg_res, reg1, reg2;
                reg1 = ensure_right(fp, op1,p->code.next_op_distance[1]);
                reg2 = ensure_right(fp, op2,p->code.next_op_distance[2]);
                if (res->kind == OP_ADDRESS)
                {
                    Operand t = new_temp();
                    int reg_tmp = get_reg(fp, t,2147483647);
                    fprintf(fp, "  sub %s, %s, %s\n", Regs[reg_tmp].name, Regs[reg1].name, Regs[reg2].name);
                    store(fp, res, t,p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  sub %s, %s, %s\n", Regs[reg_res].name, Regs[reg1].name, Regs[reg2].name);
                }
            }
            break;
        }
        case IR_MUL:
        {
            Operand op1 = p->code.u.binop.op1;
            Operand op2 = p->code.u.binop.op2;
            Operand res = p->code.u.binop.result;
            if (op1->kind == OP_CONSTANT && op2->kind == OP_CONSTANT)
            {
                int val = op1->u.value * op2->u.value;
                if (res->kind == OP_ADDRESS)
                {
                    store(fp, res, new_int_Operand(val, OP_CONSTANT),p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    int reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  li %s, %d\n", Regs[reg_res].name, val);
                }
            }
            else
            {
                int reg_res, reg1, reg2;
                reg1 = ensure_right(fp, op1,p->code.next_op_distance[1]);
                reg2 = ensure_right(fp, op2,p->code.next_op_distance[2]);
                if (res->kind == OP_ADDRESS)
                {
                    Operand t = new_temp();
                    int reg_tmp = get_reg(fp, t,2147483647);
                    fprintf(fp, "  mul %s, %s, %s\n", Regs[reg_tmp].name, Regs[reg1].name, Regs[reg2].name);
                    store(fp, res, t,p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  mul %s, %s, %s\n", Regs[reg_res].name, Regs[reg1].name, Regs[reg2].name);
                }
            }
            break;
        }
        case IR_DIV:
        {
            Operand op1 = p->code.u.binop.op1;
            Operand op2 = p->code.u.binop.op2;
            Operand res = p->code.u.binop.result;
            if (op1->kind == OP_CONSTANT && op2->kind == OP_CONSTANT)
            {
                if (op2->u.value == 0)
                {
                    printf("divide 0!\n");
                    exit(0);
                }
                int val = op1->u.value / op2->u.value;
                if (res->kind == OP_ADDRESS)
                {
                    store(fp, res, new_int_Operand(val, OP_CONSTANT),p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    int reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  li %s, %d\n", Regs[reg_res].name, val);
                }
            }
            else
            {
                int reg_res, reg1, reg2;
                reg1 = ensure_right(fp, op1,p->code.next_op_distance[1]);
                reg2 = ensure_right(fp, op2,p->code.next_op_distance[2]);
                if (res->kind == OP_ADDRESS)
                {
                    Operand t = new_temp();
                    int reg_tmp = get_reg(fp, t, 2147483647);
                    fprintf(fp, "  div %s, %s\n", Regs[reg1].name, Regs[reg2].name);
                    fprintf(fp, "  mflo %s\n", Regs[reg_tmp].name);
                    store(fp, res, t,p->code.next_op_distance[0],2147483647);
                }
                else
                {
                    reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
                    fprintf(fp, "  div %s, %s\n", Regs[reg1].name, Regs[reg2].name);
                    fprintf(fp, "  mflo %s\n", Regs[reg_res].name);
                }
            }
            break;
        }
        case IR_ASSIGN:
        {
            Operand right = p->code.u.assign.right;
            Operand left = p->code.u.assign.left;
            if (left->kind != OP_ADDRESS)
            {
                if (right->kind == OP_CONSTANT)
                {
                    int reg_left = get_reg(fp, left,p->code.next_op_distance[1]);
                    fprintf(fp, "  li %s, %d", Regs[reg_left].name, right->u.value);
                }
                else
                {
                    int reg_left = get_reg(fp, left,p->code.next_op_distance[1]);
                    int reg_right = ensure_right(fp, right,p->code.next_op_distance[0]);
                    fprintf(fp, "  move %s, %s\n", Regs[reg_left].name, Regs[reg_right].name);
                }
            }
            else
            {
                store(fp, left, right,p->code.next_op_distance[1],p->code.next_op_distance[0]);
            }
            break;
        }
        case IR_ASSIGNADDR:
        {
            Operand right = p->code.u.assign.right;
            Operand left = p->code.u.assign.left;
            int reg_left = get_reg(fp, left,p->code.next_op_distance[1]);
            int reg_right = ensure_right(fp, right,p->code.next_op_distance[0]);
            fprintf(fp, "  la %s, %s\n", Regs[reg_right].name, right->u.name);
            fprintf(fp, "  move %s, %s\n", Regs[reg_left].name, Regs[reg_right].name);
            break;
        }
        case IR_GOTO:
        {
            fprintf(fp, "  j %s\n", getOperandName(p->code.u.single));
            break;
        }
        case IR_IFGOTO:
        {
            Operand op1 = p->code.u.control.op1;
            Operand relop = p->code.u.control.relop;
            Operand op2 = p->code.u.control.op2;
            Operand label = p->code.u.control.label;
            int reg1 = ensure_right(fp, op1,p->code.next_op_distance[0]);
            int reg2 = ensure_right(fp, op2,p->code.next_op_distance[2]);
            if (strcmp(relop->u.name, "==") == 0)
            {
                fprintf(fp, "  beq %s, %s, %s\n", Regs[reg1].name, Regs[reg2].name, label->u.vname);
            }
            else if (strcmp(relop->u.name, "!=") == 0)
            {
                fprintf(fp, "  bne %s, %s, %s\n", Regs[reg1].name, Regs[reg2].name, label->u.vname);
            }
            else if (strcmp(relop->u.name, ">") == 0)
            {
                fprintf(fp, "  bgt %s, %s, %s\n", Regs[reg1].name, Regs[reg2].name, label->u.vname);
            }
            else if (strcmp(relop->u.name, "<") == 0)
            {
                fprintf(fp, "  blt %s, %s, %s\n", Regs[reg1].name, Regs[reg2].name, label->u.vname);
            }
            else if (strcmp(relop->u.name, ">=") == 0)
            {
                fprintf(fp, "  bge %s, %s, %s\n", Regs[reg1].name, Regs[reg2].name, label->u.vname);
            }
            else if (strcmp(relop->u.name, "<=") == 0)
            {
                fprintf(fp, "  ble %s, %s, %s\n", Regs[reg1].name, Regs[reg2].name, label->u.vname);
            }
            break;
        }
        case IR_ADD_ADDR:
        {
            Operand op1 = p->code.u.binop.op1;
            Operand op2 = p->code.u.binop.op2;
            Operand res = p->code.u.binop.result;
            int reg1 = get_reg(fp, op1,p->code.next_op_distance[1]);
            int reg_res = get_reg(fp, res,p->code.next_op_distance[0]);
            if (op2->kind == OP_CONSTANT)
            {
                fprintf(fp, "  addi %s, %s, %d\n", Regs[reg_res].name, Regs[reg1].name, op2->u.value);
            }
            else
            {
                int reg2 = ensure_right(fp, op2,p->code.next_op_distance[2]);
                fprintf(fp, "  add %s, %s, %s\n", Regs[reg_res].name, Regs[reg1].name, Regs[reg2].name);
            }
            break;
        }
        case IR_READ:
        {
            fprintf(fp, "  addi $sp, $sp, -4\n");
            fprintf(fp, "  sw $ra, 0($sp)\n");
            fprintf(fp, "  jal read\n");
            fprintf(fp, "  lw $ra, 0($sp)\n");
            fprintf(fp, "  addi $sp, $sp, 4\n");
            Operand op = p->code.u.single;
            int reg = get_reg(fp, op,p->code.next_op_distance[0]);
            fprintf(fp, "  move %s, $v0\n", Regs[reg].name);
            break;
        }
        case IR_WRITE:
        {
            Operand op = p->code.u.single;
            if (is_main)
            {
                int reg = ensure_right(fp, op,p->code.next_op_distance[0]);
                fprintf(fp, "  move $a0, %s\n", Regs[reg].name);
                fprintf(fp, "  addi $sp, $sp, -4\n");
                fprintf(fp, "  sw $ra, 0($sp)\n");
                fprintf(fp, "  jal write\n");
                fprintf(fp, "  lw $ra, 0($sp)\n");
                fprintf(fp, "  addi $sp, $sp, 4\n");
            }
            else
            {
                //在非main函数中调用时需要额外保存$a0
                fprintf(fp, "  addi $sp, $sp, -8\n");
                fprintf(fp, "  sw $a0, 0($sp)\n");
                fprintf(fp, "  sw $ra, 4($sp)\n");
                int reg = ensure_right(fp, op,p->code.next_op_distance[0]);
                fprintf(fp, "  move $a0, %s\n", Regs[reg].name);
                fprintf(fp, "  jal write\n");
                fprintf(fp, "  lw $a0, 0($sp)\n");
                fprintf(fp, "  lw $ra, 4($sp)\n");
                fprintf(fp, "  addi $sp, $sp, 8\n");
            }
            break;
        }
        case IR_RETURN:
        {
            Operand op=p->code.u.single;
            if(op->kind==OP_CONSTANT)
            {
                load_imm();
            }
            break;
        }
        default:
            break;
        }
        p = p->next;
    }
}
void generate_machine_code(FILE *fp)
{
    init_reg();
    init_data(fp);
    init_code(fp);
    init_block();
    translate_intercode(fp, head.next);
}

int get_stack_offset(Operand op){
    struct StackNode *p = Records.fp;
    while(p!= NULL)
    {
        if(p->op == op)
        {
            return p->offset;      
        }
        p = p ->next;
    }
    return -1;
}


int save(FILE *fp,int reg_idx){
    struct StackNode *p = Records.fp;
    struct StackNode *prev = NULL;
    while(p != NULL)
    {
        if(p->op == Regs[reg_idx].content)
        {
            fprintf(fp,"  sw %s, %d($fp)\n",Regs[reg_idx].name,p->offset);
            Regs[reg_idx].is_free = 1;
            return p->offset;
        }
        prev = p;
        p = p->next;
    }
    if(prev==NULL)
    {
        Records.fp = malloc(sizeof(struct StackNode));
        p = Records.fp;
        p->offset = -4;
    }
    else 
    {
        prev->next = malloc(sizeof(struct StackNode));
        p = prev->next;
        p->offset = prev->offset - 4;
    }
    p->next = NULL;
    p->op = Regs[reg_idx].content;
    fprintf(fp,"  sw %s, %d($fp)\n",Regs[reg_idx].name,p->offset);
    Regs[reg_idx].is_free = 1;
    return p->offset;
}

int push(FILE *fp,int reg_idx){
    struct StackNode *p = Records.fp;
    struct StackNode *prev = NULL;
    while(p != NULL)
    {
        prev = p;
        p = p->next;
    }
    if(prev==NULL)
    {
        Records.fp = malloc(sizeof(struct StackNode));
        p = Records.fp;
        p->offset = -4;
    }
    else 
    {
        prev->next = malloc(sizeof(struct StackNode));
        p = prev->next;
        p->offset = prev->offset - 4;
    }
    p->next = NULL;
    p->op = Regs[reg_idx].content;
    fprintf(fp,"  sw %s, %d($fp)\n",Regs[reg_idx].name,p->offset);
    Regs[reg_idx].is_free = 1;
    return p->offset;
}

void pop(){
    struct StackNode *p = Records.fp;
    if(p == NULL)
        return ;
    struct StackNode *prev = NULL;
    while(p->next != NULL)
    {
        prev = p;
        p = p->next;
    }
    if(prev == NULL)
    {
        Records.fp = NULL;
        free(p);
    }
    else
    {
        prev->next = NULL;
        free(p);
    }
    return ;
}   

int get_unused_reg(FILE *fp){
    for(int i = 8;i < 26;i++)
    {
        if(Regs[i].is_free == 1)
        {
            return i;
        }
    }
    int max = -1;
    int maxpos = -1;
    for(int i = 8;i < 26;i++)
    {
        if(Regs[i].distance > max)
        {
            max = Regs[i].distance;
            maxpos = i;
        }
    }
    save(fp,maxpos);
    return maxpos;
}

int get_reg(FILE *fp, Operand op,int distance){
    for(int i = 0;i < 32;i++)
    {
        if(Regs[i].is_free == 0 && Regs[i].content==op)
        {
            Regs[i].distance = distance;
            return i;
        }
    }
    struct StackNode *p = Records.fp;
    struct StackNode *prev= NULL;
    while(p != NULL)
    {
        if(p->op == op)
        {
            int i = get_unused_reg(fp);
            Regs[i].is_free = 0;
            Regs[i].content = op;
            Regs[i].distance = distance;
            fprintf(fp, "  lw %s, %d($fp)\n",Regs[i].name,p->offset);
            return i;
        }
        prev = p;
        p = p->next;
    }
    for(int i = 8;i < 26;i++)
    {
        if(Regs[i].is_free == 1)
        {
            Regs[i].is_free = 0;
            Regs[i].distance = distance;
            Regs[i].content = op;
            return i;
        }
    }
    int i = get_unused_reg(fp);
    Regs[i].is_free = 0;
    Regs[i].distance = distance;
    Regs[i].content = op;
    return i;
}


int *save_regs(FILE* fp){
    int *res = malloc(sizeof(int) * 32);
    for(int i = 0;i < 32;i++)
    {
        res[i] = 1;
        if(Regs[i].is_free == 0)
        {
            res[i] = save(fp,i);
        }
    }
    return res;
}

void load_regs(FILE *fp,int *a){
    for(int i = 0;i < 32;i++)
    {
        if(a[i] != 1)
        {
            fprintf(fp, "  lw %s, %d($fp)\n",Regs[i].name,a[i]);
        }
    }
    free(a);
}