#include "MachineCode.h"
#define DEBUG_SIG 0
struct tmp_symbol
{
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

void set_distance(struct tmp_symbol *head, int pos, int *dst, Operand op)
{
    struct tmp_symbol *p = head->next;
    struct tmp_symbol *prev = head;
    while (p != NULL)
    {
        if (op == p->op)
        {
            *dst = pos - p->pos;
            p->pos = pos;
            return;
        }
        prev = p;
        p = p->next;
    }
    prev->next = malloc(sizeof(struct tmp_symbol));
    p = prev->next;
    p->next = NULL;
    p->op = op;
    p->pos = pos;
    *dst = 2147483647;
}

void init_block()
{
    struct InterCodes *p = head.next;
    struct InterCodes *tmp;
    while (p != &head)
    {
        switch (p->code.kind)
        {
        case IR_GOTO:
        case IR_IFGOTO:
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
        p = p->next;
    }
    p = head.prev;
    struct tmp_symbol symbol_head;
    symbol_head.next = NULL;
    int pos = 0;
    while (p != &head)
    {
        if (p->code.kind == SPLIT_POINT)
        {
            pos = 0;
            struct tmp_symbol *q = symbol_head.next;
            while (q != NULL)
            {
                struct tmp_symbol *tmp2 = q->next;
                free(q);
                q = tmp2;
            }
            symbol_head.next = NULL;
            p = p->prev;
            continue;
        }
        switch (p->code.opnum)
        {
        case 4:
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[3]), p->code.u.control.label);
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[2]), p->code.u.control.op2);
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[1]), p->code.u.control.relop);
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[0]), p->code.u.control.op1);
            break;
        case 3:
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[2]), p->code.u.binop.op2);
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[1]), p->code.u.binop.op1);
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[0]), p->code.u.binop.result);
            break;
        case 2:
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[1]), p->code.u.assign.left);
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[0]), p->code.u.assign.right);
            break;
        case 1:
            set_distance(&symbol_head, pos, &(p->code.next_op_distance[0]), p->code.u.single);
            break;
        default:
            assert(0);
        }
        p = p->prev;
        pos++;
    }
    struct tmp_symbol *f = symbol_head.next;
    while (f != NULL)
    {
        free(f);
        f = f->next;
    }
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
            if (DEBUG_SIG)
            {
                printf("IR_LABEL\n");
            }
            save_regs(fp);
            fprintf(fp, "%s:\n", p->code.u.single->u.vname);
            break;
        }
        case IR_ADD_ADDR:
        case IR_ADD:
        {
            if (DEBUG_SIG)
            {
                printf("IR_ADD\n");
            }
            Operand op1 = p->code.u.binop.op1;
            Operand op2 = p->code.u.binop.op2;
            Operand res = p->code.u.binop.result;
            int dis_res = p->code.next_op_distance[0];
            int dis1 = p->code.next_op_distance[1];
            int dis2 = p->code.next_op_distance[2];
            int reg_res, reg1, reg2;
            if (op1->kind == OP_CONSTANT)
            {
                reg1 = load_imm(fp, op1);
                Regs[reg1].distance = 0;
            }
            else
            {
                reg1 = get_reg(fp, op1);
                Regs[reg1].distance = 0;
            }
            if (op2->kind == OP_CONSTANT)
            {
                reg2 = load_imm(fp, op2);
                Regs[reg2].distance = 0;
            }
            else
            {
                reg2 = get_reg(fp, op2);
                Regs[reg2].distance = 0;
            }
            reg_res = get_reg(fp, res);
            Regs[reg_res].distance = 0;
            fprintf(fp, "  add %s, %s, %s\n", Regs[reg_res].name, Regs[reg1].name, Regs[reg2].name);
            Regs[reg_res].distance = dis_res;
            Regs[reg1].distance = dis1;
            Regs[reg2].distance = dis2;
            break;
        }
        case IR_SUB:
        {
            if (DEBUG_SIG)
            {
                printf("IR_SUB\n");
            }
            Operand op1 = p->code.u.binop.op1;
            Operand op2 = p->code.u.binop.op2;
            Operand res = p->code.u.binop.result;
            int dis_res = p->code.next_op_distance[0];
            int dis1 = p->code.next_op_distance[1];
            int dis2 = p->code.next_op_distance[2];
            int reg_res, reg1, reg2;
            if (op1->kind == OP_CONSTANT)
            {
                reg1 = load_imm(fp, op1);
                Regs[reg1].distance = 0;
            }
            else
            {
                reg1 = get_reg(fp, op1);
                Regs[reg1].distance = 0;
            }
            if (op2->kind == OP_CONSTANT)
            {
                reg2 = load_imm(fp, op2);
                Regs[reg2].distance = 0;
            }
            else
            {
                reg2 = get_reg(fp, op2);
                Regs[reg2].distance = 0;
            }
            reg_res = get_reg(fp, res);
            Regs[reg_res].distance = 0;
            fprintf(fp, "  sub %s, %s, %s\n", Regs[reg_res].name, Regs[reg1].name, Regs[reg2].name);
            Regs[reg_res].distance = dis_res;
            Regs[reg1].distance = dis1;
            Regs[reg2].distance = dis2;
            break;
        }
        case IR_MUL:
        {
            if (DEBUG_SIG)
            {
                printf("IR_MUL\n");
            }
            Operand op1 = p->code.u.binop.op1;
            Operand op2 = p->code.u.binop.op2;
            Operand res = p->code.u.binop.result;
            int dis_res = p->code.next_op_distance[0];
            int dis1 = p->code.next_op_distance[1];
            int dis2 = p->code.next_op_distance[2];
            int reg_res, reg1, reg2;

            if (op1->kind == OP_CONSTANT)
            {
                reg1 = load_imm(fp, op1);
                Regs[reg1].distance = 0;
            }
            else
            {
                reg1 = get_reg(fp, op1);
                Regs[reg1].distance = 0;
            }

            if (op2->kind == OP_CONSTANT)
            {
                reg2 = load_imm(fp, op2);
                Regs[reg2].distance = 0;
            }
            else
            {
                reg2 = get_reg(fp, op2);
                Regs[reg2].distance = 0;
            }
            reg_res = get_reg(fp, res);
            Regs[reg_res].distance = 0;
            fprintf(fp, "  mul %s, %s, %s\n", Regs[reg_res].name, Regs[reg1].name, Regs[reg2].name);
            Regs[reg_res].distance = dis_res;
            Regs[reg1].distance = dis1;
            Regs[reg2].distance = dis2;
            break;
        }
        case IR_DIV:
        {
            if (DEBUG_SIG)
            {
                printf("IR_DIV\n");
            }
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
            }
            int dis_res = p->code.next_op_distance[0];
            int dis1 = p->code.next_op_distance[1];
            int dis2 = p->code.next_op_distance[2];
            int reg_res, reg1, reg2;
            if (op1->kind == OP_CONSTANT)
            {
                reg1 = load_imm(fp, op1);
                Regs[reg1].distance = 0;
            }
            else
            {
                reg1 = get_reg(fp, op1);
                Regs[reg1].distance = 0;
            }
            if (op2->kind == OP_CONSTANT)
            {
                reg2 = load_imm(fp, op2);
                Regs[reg2].distance = 0;
            }
            else
            {
                reg2 = get_reg(fp, op2);
                Regs[reg2].distance = 0;
            }
            reg_res = get_reg(fp, res);
            Regs[reg_res].distance = 0;
            fprintf(fp, "  div %s, %s\n", Regs[reg1].name, Regs[reg2].name);
            fprintf(fp, "  mflo %s\n", Regs[reg_res].name);
            Regs[reg_res].distance = dis_res;
            Regs[reg1].distance = dis1;
            Regs[reg2].distance = dis2;
            /*
                old version
                int reg_res, reg1, reg2;
                reg1 = ensure_right(fp, op1, p->code.next_op_distance[1]);
                reg2 = ensure_right(fp, op2, p->code.next_op_distance[2]);
                if (res->kind == OP_ADDRESS)
                {
                    Operand t = new_temp();
                    int reg_tmp = get_reg(fp, t);
                    fprintf(fp, "  div %s, %s\n", Regs[reg1].name, Regs[reg2].name);
                    fprintf(fp, "  mflo %s\n", Regs[reg_tmp].name);
                    store(fp, res, t, p->code.next_op_distance[0], 2147483647);
                }
                else
                {
                    reg_res = get_reg(fp, res);
                    fprintf(fp, "  div %s, %s\n", Regs[reg1].name, Regs[reg2].name);
                    fprintf(fp, "  mflo %s\n", Regs[reg_res].name);
                }*/

            break;
        }
        case IR_ASSIGN:
        {
            if (DEBUG_SIG)
            {
                printf("IR_ASSIGN\n");
            }
            Operand right = p->code.u.assign.right;
            Operand left = p->code.u.assign.left;
            int disright = p->code.next_op_distance[0];
            int disleft = p->code.next_op_distance[1];
            int reg_left, reg_right;
            if (right->kind == OP_CONSTANT)
            {
                reg_right = load_imm(fp, right);
                Regs[reg_right].distance = 0;
            }
            else
            {
                reg_right = get_reg(fp, right);
                Regs[reg_right].distance = 0;
            }
            reg_left = get_reg(fp, left);
            Regs[reg_left].distance = 0;
            if (right->kind == OP_ADDRESS && left->kind == OP_ADDRESS)
            {
                printf("both addr in assign!\n");
                exit(0);
            }
            else if (right->kind == OP_ADDRESS)
            {
                fprintf(fp, "  lw %s, 0(%s)\n", Regs[reg_left].name, Regs[reg_right].name);
            }
            else if (left->kind == OP_ADDRESS)
            {
                fprintf(fp, "  sw %s, 0(%s)\n", Regs[reg_right].name, Regs[reg_left].name);
            }
            else
            {
                fprintf(fp, "  move %s, %s\n", Regs[reg_left].name, Regs[reg_right].name);
            }
            Regs[reg_left].distance = disleft;
            Regs[reg_right].distance = disright;
            break;
        }
        case IR_ASSIGNADDR:
        {
            if (DEBUG_SIG)
            {
                printf("IR_ASSIGNADDR\n");
            }
            Operand right = p->code.u.assign.right;
            Operand left = p->code.u.assign.left;
            int disright = p->code.next_op_distance[0];
            int disleft = p->code.next_op_distance[1];
            int offset = get_stack_offset(right);
            if (offset == -1)
            {
                printf("stack does not have it!\n");
                exit(0);
            }
            int reg_left = get_reg(fp, left);
            Regs[reg_left].distance = 0;
            fprintf(fp, "  la %s, %d($fp)\n", Regs[reg_left].name, offset);
            Regs[reg_left].distance = disleft;
            break;
        }
        case IR_GOTO:
        {
            if (DEBUG_SIG)
            {
                printf("IR_GOTO\n");
            }
            save_regs(fp);
            fprintf(fp, "  j %s\n", getOperandName(p->code.u.single));
            break;
        }
        case IR_IFGOTO:
        {
            if (DEBUG_SIG)
            {
                printf("IR_IFGOTO\n");
            }
            Operand op1 = p->code.u.control.op1;
            Operand relop = p->code.u.control.relop;
            Operand op2 = p->code.u.control.op2;
            Operand label = p->code.u.control.label;
            int dis1 = p->code.next_op_distance[0];
            int dis2 = p->code.next_op_distance[2];
            int reg1, reg2;
            if (op1->kind == OP_CONSTANT)
            {
                reg1 = load_imm(fp, op1);
                Regs[reg1].distance = 0;
            }
            else
            {
                reg1 = get_reg(fp, op1);
                Regs[reg1].distance = 0;
            }
            if (op2->kind == OP_CONSTANT)
            {
                reg2 = load_imm(fp, op2);
                Regs[reg2].distance = 0;
            }
            else
            {
                reg2 = get_reg(fp, op2);
                Regs[reg2].distance = 0;
            }
            Regs[reg1].distance = dis1;
            Regs[reg2].distance = dis2;
            save_regs(fp);
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
            Regs[reg1].distance = dis1;
            Regs[reg2].distance = dis2;
            break;
        }
        case IR_READ:
        {
            if (DEBUG_SIG)
            {
                printf("IR_READ\n");
            }
            fprintf(fp, "  addi $sp, $sp, -4\n");
            fprintf(fp, "  sw $ra, 0($sp)\n");
            fprintf(fp, "  jal read\n");
            fprintf(fp, "  lw $ra, 0($sp)\n");
            fprintf(fp, "  addi $sp, $sp, 4\n");
            Operand op = p->code.u.single;
            int dis = p->code.next_op_distance[0];
            int reg = get_reg(fp, op);
            Regs[reg].distance = 0;
            fprintf(fp, "  move %s, $v0\n", Regs[reg].name);
            Regs[reg].distance = dis;
            break;
        }
        case IR_WRITE:
        {
            if (DEBUG_SIG)
            {
                printf("IR_WRITE\n");
            }
            Operand op = p->code.u.single;
            int dis = p->code.next_op_distance[0];
            if (is_main)
            {
                int reg;
                if (op->kind == OP_CONSTANT)
                    reg = load_imm(fp, op);
                else
                    reg = get_reg(fp, op);
                Regs[reg].distance = 0;
                fprintf(fp, "  move $a0, %s\n", Regs[reg].name);
                fprintf(fp, "  addi $sp, $sp, -4\n");
                fprintf(fp, "  sw $ra, 0($sp)\n");
                fprintf(fp, "  jal write\n");
                fprintf(fp, "  lw $ra, 0($sp)\n");
                fprintf(fp, "  addi $sp, $sp, 4\n");
                Regs[reg].distance = dis;
            }
            else
            {
                //在非main函数中调用时需要额外保存$a0
                fprintf(fp, "  addi $sp, $sp, -8\n");
                fprintf(fp, "  sw $a0, 0($sp)\n");
                fprintf(fp, "  sw $ra, 4($sp)\n");
                int reg;
                if (op->kind == OP_CONSTANT)
                    reg = load_imm(fp, op);
                else
                    reg = get_reg(fp, op);
                Regs[reg].distance = 0;
                fprintf(fp, "  move $a0, %s\n", Regs[reg].name);
                fprintf(fp, "  jal write\n");
                fprintf(fp, "  lw $a0, 0($sp)\n");
                fprintf(fp, "  lw $ra, 4($sp)\n");
                fprintf(fp, "  addi $sp, $sp, 8\n");
                Regs[reg].distance = dis;
            }
            break;
        }
        case IR_RETURN:
        {
            if (DEBUG_SIG)
            {
                printf("IR_RETURN\n");
            }
            Operand op = p->code.u.single;
            int dis = p->code.next_op_distance[0];
            int reg;
            if (op->kind == OP_CONSTANT)
            {
                reg = load_imm(fp, op);
                Regs[reg].distance = 0;
            }
            else
            {
                reg = get_reg(fp, op);
                Regs[reg].distance = 0;
            }
            fprintf(fp, "  move $v0, %s\n", Regs[reg].name);
            Regs[reg].distance = dis;
            fprintf(fp, "  jr $ra\n");
            //TO DO
            break;
        }
        case IR_FUNCTION:
        {
            if (DEBUG_SIG)
            {
                printf("IR_FUNCTION\n");
            }
            Operand op = p->code.u.single;
            fprintf(fp, "\n%s:\n", op->u.name);
            if (strcmp(op->u.name, "main") == 0)
            {
                is_main = 1;
                fprintf(fp, "  move $fp, $sp\n");
            }
            else
                is_main = 0;
            while (Records.fp != NULL)
            {
                struct StackNode *p = Records.fp;
                Records.fp = Records.fp->next;
                free(p);
            }
            Records.size = 0;
            for (int i = 8; i <= 25; i++)
                Regs[i].is_free = 1;
            //TO DO
            break;
        }
        case IR_ARG:
        {
            if (DEBUG_SIG)
            {
                printf("IR_ARG\n");
            }
            int *a = save_regs(fp);
            push(fp, 30);
            push(fp, 31);
            //fprintf(fp, "  sw $ra, 0($sp)\n");
            //fprintf(fp, "  sw $fp, 4($sp)\n");
            //fprintf(fp,"  move $fp, $sp");
            int paranum = 0;
            struct InterCodes *q = p;
            while (q->code.kind == IR_ARG)
            {
                paranum++;
                q = q->next;
            }
            while (p->code.kind == IR_ARG)
            {
                push_arg(fp, p->code.u.single);
                p = p->next;
            }
            assert(p->code.kind == IR_CALL); //assertion
            fprintf(fp, "  move $fp, $sp\n");
            fprintf(fp, "  jal %s\n", p->code.u.assign.right->u.name);
            fprintf(fp, "  move $sp, $fp\n");
            for (int i = 0; i < paranum; i++)
                pop(fp);
            fprintf(fp, "  lw $ra, 0($sp)\n");
            fprintf(fp, "  lw $fp, 4($sp)\n");
            pop(fp);
            pop(fp);
            load_regs(fp, a);
            int reg = get_reg(fp, p->code.u.assign.left);
            int dis = p->code.next_op_distance[1];
            Regs[reg].distance = 0;
            fprintf(fp, "  move %s, $v0\n", Regs[reg].name);
            Regs[reg].distance = dis;
            break;
        }
        case IR_CALL:
        {
            if (DEBUG_SIG)
            {
                printf("IR_CALL\n");
            }
            int *a = save_regs(fp);
            fprintf(fp, "  addi $sp, $sp, -8\n");
            push(fp, 30);
            push(fp, 31);
            //fprintf(fp, "  sw $ra, 0($sp)\n");
            //fprintf(fp, "  sw $fp, 4($sp)\n");
            fprintf(fp, "  move $fp, $sp\n");
            fprintf(fp, "  jal %s\n", p->code.u.assign.right->u.name);
            fprintf(fp, "  move $sp, $fp\n");
            fprintf(fp, "  lw $ra, 0($sp)\n");
            fprintf(fp, "  lw $fp, 4($sp)\n");
            fprintf(fp, "  addi $sp, $sp, 8\n");
            load_regs(fp, a);
            int reg = get_reg(fp, p->code.u.assign.left);
            int dis = p->code.next_op_distance[1];
            Regs[reg].distance = 0;
            fprintf(fp, "  move %s, $v0\n", Regs[reg].name);
            Regs[reg].distance = dis;
            break;
        }
        case IR_DEC:
        {
            if (DEBUG_SIG)
            {
                printf("IR_DEC\n");
            }
            stack_malloc(p->code.u.assign.left, p->code.u.assign.right->u.value);
            fprintf(fp,"  addi $sp, $sp, %d\n",-p->code.u.assign.right->u.value);
            int i=0,size=p->code.u.assign.right->u.value;
            while(i<size)
            {
                fprintf(fp, "  sw $zero, %d($sp)\n",-i);
                i=i+4;
            }
            break;
        }
        case IR_PARAM:
        {
            if (DEBUG_SIG)
            {
                printf("IR_PARAM\n");
            }
            int i = 0;
            while (p->next->code.kind == IR_PARAM)
            {
                add_stacknode(p->code.u.single, i * 4);
                i++;
                p = p->next;
            }
            add_stacknode(p->code.u.single, i * 4);
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

int get_stack_offset(Operand op)
{
    struct StackNode *p = Records.fp;
    while (p != NULL)
    {
        if (strcmp(p->op->u.vname, op->u.vname) == 0)
        {
            return p->offset;
        }
        p = p->next;
    }
    return -1;
}

int save(FILE *fp, int reg_idx)
{
    assert(Regs[reg_idx].content->kind != OP_CONSTANT);
    struct StackNode *p = Records.fp;
    struct StackNode *prev = NULL;
    while (p != NULL)
    {
        //if (p->op == Regs[reg_idx].content)
        if (strcmp(p->op->u.vname, Regs[reg_idx].content->u.vname) == 0)
        {
            fprintf(fp, "  sw %s, %d($fp)\n", Regs[reg_idx].name, p->offset);
            Regs[reg_idx].is_free = 1;
            p->distance = Regs[reg_idx].distance;
            return p->offset;
        }
        prev = p;
        p = p->next;
    }
    if (prev == NULL)
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
    p->distance = Regs[reg_idx].distance;
    fprintf(fp, "  sw %s, %d($fp)\n", Regs[reg_idx].name, p->offset);
    fprintf(fp, "  addi $sp, $sp, -4\n");
    Regs[reg_idx].is_free = 1;
    return p->offset;
}

int push(FILE *fp, int reg_idx)
{
    struct StackNode *p = Records.fp;
    struct StackNode *prev = NULL;
    while (p != NULL)
    {
        prev = p;
        p = p->next;
    }
    if (prev == NULL)
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
    p->distance = Regs[reg_idx].distance;
    fprintf(fp, "  sw %s, %d($fp)\n", Regs[reg_idx].name, p->offset);
    Regs[reg_idx].is_free = 1;
    fprintf(fp, "  addi $sp, $sp, -4\n");
    return p->offset;
}

void pop(FILE *fp)
{
    struct StackNode *p = Records.fp;
    if (p == NULL)
        return;
    struct StackNode *prev = NULL;
    while (p->next != NULL)
    {
        prev = p;
        p = p->next;
    }
    if (prev == NULL)
    {
        Records.fp = NULL;
        free(p);
    }
    else
    {
        prev->next = NULL;
        free(p);
    }
    fprintf(fp, "  addi $sp, $sp, 4\n");
    return;
}

int get_unused_reg(FILE *fp)
{
    for (int i = 8; i < 26; i++)
    {
        if (Regs[i].is_free == 1)
        {
            return i;
        }
    }
    int max = -1;
    int maxpos = -1;
    for (int i = 8; i < 26; i++)
    {
        if (Regs[i].distance > max)
        {
            max = Regs[i].distance;
            maxpos = i;
        }
    }
    if (Regs[maxpos].content->kind != OP_CONSTANT)
        save(fp, maxpos);
    return maxpos;
}

int get_reg(FILE *fp, Operand op)
{

    for (int i = 0; i < 32; i++)
    {
        if (Regs[i].is_free == 0 && Regs[i].content->kind != OP_CONSTANT && strcmp(op->u.vname, Regs[i].content->u.vname) == 0)
        {
            return i;
        }
    }
    struct StackNode *p = Records.fp;

    struct StackNode *prev = NULL;
    while (p != NULL)
    {
        if (strcmp(p->op->u.vname, op->u.vname) == 0)
        {

            int i = get_unused_reg(fp);
            Regs[i].is_free = 0;
            Regs[i].content = op;
            Regs[i].distance = p->distance;
            fprintf(fp, "  lw %s, %d($fp)\n", Regs[i].name, p->offset);
            return i;
        }
        prev = p;
        p = p->next;
    }

    for (int i = 8; i < 26; i++)
    {
        if (Regs[i].is_free == 1)
        {
            Regs[i].is_free = 0;
            Regs[i].content = op;
            return i;
        }
    }
    int i = get_unused_reg(fp);
    Regs[i].is_free = 0;
    Regs[i].content = op;
    return i;
}

int load_imm(FILE *fp, Operand op)
{
    int i = get_unused_reg(fp);
    Regs[i].is_free = 0;
    Regs[i].distance = 2147483647;
    Regs[i].content = op;
    fprintf(fp, "  li %s, %d\n", Regs[i].name, op->u.value);
    return i;
}

int *save_regs(FILE *fp)
{
    int *res = malloc(sizeof(int) * 32);
    for (int i = 0; i < 32; i++)
    {
        res[i] = 1;
        if (Regs[i].is_free == 0 && Regs[i].content->kind!=OP_CONSTANT)
        {
            res[i] = save(fp, i);
            Regs[i].is_free = 1;
        }
    }
    return res;
}

void load_regs(FILE *fp, int *a)
{
    for (int i = 0; i < 32; i++)
    {
        if (a[i] != 1)
        {
            fprintf(fp, "  lw %s, %d($fp)\n", Regs[i].name, a[i]);
            struct StackNode *p = Records.fp;
            while (p != NULL)
            {
                if (p->offset == a[i])
                {
                    Regs[i].is_free = 0;
                    Regs[i].content = p->op;
                    Regs[i].distance = p->distance;
                    break;
                }
                p = p->next;
            }
            assert(p != NULL);
        }
    }
    free(a);
}

void push_arg(FILE *fp, Operand op)
{
    int i = get_unused_reg(fp);
    int off = get_stack_offset(op);
    fprintf(fp, "  lw %s, %d($fp)\n", Regs[i].name, off);
    push(fp, i);
}

int stack_malloc(Operand op, int size)
{
    struct StackNode *p = Records.fp;
    if (p == NULL)
    {
        Records.fp = malloc(sizeof(struct StackNode));
        p = Records.fp;
        p->offset = -size;
    }
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = malloc(sizeof(struct StackNode));
        p->next->offset = p->offset - size;
        p = p->next;
    }
    p->next = NULL;
    p->op = op;
    return p->offset;
}

void add_stacknode(Operand op, int offset)
{
    struct StackNode *p = malloc(sizeof(struct StackNode));
    p->next = Records.fp;
    p->offset = offset;
    p->op = op;
    Records.fp = p;
}