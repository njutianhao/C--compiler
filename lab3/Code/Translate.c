#include "GrammarTree.h"
#include "syntax.tab.h"
int translate_success = 1;

int Success()
{
    return translate_success;
}
void translate()
{
    init();
    translate_Program(root);
}
void translate_Program(struct GrammarTree *root)
{
    if (translate_success == 0)
        return;
    struct GrammarTree *extDefListChild = get_child(root, 1);
    translate_ExtDefList(extDefListChild);
}

void translate_ExtDefList(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;

    struct GrammarTree *first = get_child(node, 1);
    if (first == NULL)
        return;
    else
    {
        struct GrammarTree *second = get_child(node, 2);
        translate_ExtDef(first);
        translate_ExtDefList(second);
    }
}

void translate_ExtDef(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;

    //struct GrammarTree *first = get_child(node, 1);
    struct GrammarTree *second = get_child(node, 2);
    if (second->type == FunDec)
    {
        struct GrammarTree *third = get_child(node, 3);
        translate_FunDec(second);
        translate_CompSt(third);
    }
}

void translate_FunDec(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;

    struct GrammarTree *first = get_child(node, 1);
    Operand op = new_char_Operand(first->val.str, OP_FUNCTION);
    create_InterCode_oneOp(op, IR_FUNCTION);
    Type type = search_function(first->val.str);
    if (type == NULL)
        return;
    else
    {
        FieldList head = getFieldListhead(type);
        while (head != NULL)
        {
            if (head->type->kind == ARRAY)
            {
                translate_success = 0;
                printf("Cannot translate: Code contains parameters of array type.\n");
                return;
            }
            if (head->type->kind == STRUCTURE)
            {
                Operand varop = new_char_Operand(head->name, OP_ADDRESS);
                create_InterCode_oneOp(varop, IR_PARAM);
            }
            else
            {
                Operand varop = new_char_Operand(head->name, OP_VARIABLE);
                create_InterCode_oneOp(varop, IR_PARAM);
            }
            head = head->next;
        }
    }
}
void translate_CompSt(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;
    struct GrammarTree *deflist = get_child(node, 2);
    struct GrammarTree *stmtlist = get_child(node, 3);
    translate_DefList(deflist);
    translate_StmtList(stmtlist);
}
void translate_DefList(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;
    if (get_child(node, 1) == NULL)
        return;
    translate_Def(get_child(node, 1));
    translate_DefList(get_child(node, 2));
}
void translate_StmtList(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;
    if (get_child(node, 1) == NULL)
        return;
    translate_Stmt(get_child(node, 1));
    translate_StmtList(get_child(node, 2));
}

void translate_Def(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;
    translate_DecList(get_child(node, 2));
}

void translate_DecList(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;
    translate_Dec(get_child(node, 1));
    if (get_child(node, 2) != NULL)
    {
        translate_DecList(get_child(node, 3));
    }
}
void translate_Dec(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;
    translate_VarDec(get_child(node, 1), NULL);
    if (get_child(node, 2) != NULL)
    {
        Operand op1 = new_variable();
        Operand op2 = new_temp();
        translate_VarDec(get_child(node, 1), op1);
        translate_Exp(get_child(node, 3), op2);
        create_InterCode_twoOp(op1, op2, IR_ASSIGN);
    }
}
void translate_VarDec(struct GrammarTree *node, Operand place)
{
    if (translate_success == 0)
        return;
    struct GrammarTree *first = get_child(node, 1);
    if (first->type == ID)
    {
        Type varType = search_with_name(first->val.str);
        if (varType->kind == BASIC_INT || varType->kind == BASIC_FLOAT)
        {
            if (place == NULL)
                new_char_Operand(first->val.str, OP_VARIABLE);
            else
                renew_char(place, first->val.str, OP_VARIABLE);
        }
        else if (varType->kind == ARRAY)
        {
            if (getDimension(varType) > 1)
            {
                translate_success = 0;
                printf("Cannot translate: Code contains variables of multi-dimensional array type.\n");
                return;
            }
            else
            {
                if (place != NULL)
                {
                    renew_char(place, first->val.str, OP_VARIABLE);
                    Operand op2 = new_int_Operand(getSize(varType) * 4, OP_CONSTANT);
                    create_InterCode_twoOp(place, op2, IR_DEC);
                }
                else
                {
                    Operand op1 = new_char_Operand(first->val.str, OP_VARIABLE);
                    Operand op2 = new_int_Operand(getSize(varType) * 4, OP_CONSTANT);
                    create_InterCode_twoOp(op1, op2, IR_DEC);
                }
            }
        }
        else if (varType->kind == STRUCTURE)
        {
            Operand op1 = new_char_Operand(first->val.str, OP_VARIABLE);
            Operand op2 = new_int_Operand(getSize(varType) * 4, OP_CONSTANT);
            create_InterCode_twoOp(op1, op2, IR_DEC);
        }
    }
    else
        translate_VarDec(first, place);
}

void translate_Exp(struct GrammarTree *node, Operand place)
{
    if (translate_success == 0)
        return;
    struct GrammarTree *first = get_child(node, 1);
    //Exp -> LP Exp RP
    if (first->type == LP)
        translate_Exp(get_child(node, 2), place);
    //Exp -> INT
    else if (first->type == INT)
    {
        renew_int(place, first->val.i, OP_CONSTANT);
    }
    //Exp -> ID
    else if (first->type == ID && get_child(node, 2) == NULL)
    {
        if (getKindwithName(first->val.str) == STRUCTURE)
        {
                Operand tmp=place;
                int flag=get(place, first->val.str);
                assert(flag==1);
        }
        else
            renew_char(place, first->val.str, OP_VARIABLE);
    }
    //Exp -> Exp ASSIGNOP Exp
    else if (first->type == Exp && get_child(node, 2)->type == ASSIGNOP)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand op1 = new_temp();
        Operand op2 = new_temp();
        translate_Exp(first, op1);
        translate_Exp(third, op2);
        create_InterCode_twoOp(op1, op2, IR_ASSIGN);
    }
    //Exp -> Exp PLUS Exp
    else if (first->type == Exp && get_child(node, 2)->type == PLUS)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand op1 = new_temp();
        Operand op2 = new_temp();
        translate_Exp(first, op1);
        translate_Exp(third, op2);
        create_InterCode_threeOp(place, op1, op2, IR_ADD);
    }
    //Exp -> Exp MINUS Exp
    else if (first->type == Exp && get_child(node, 2)->type == SUB)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand op1 = new_temp();
        Operand op2 = new_temp();
        translate_Exp(first, op1);
        translate_Exp(third, op2);
        create_InterCode_threeOp(place, op1, op2, IR_SUB);
    }
    //Exp -> Exp STAR Exp
    else if (first->type == Exp && get_child(node, 2)->type == STAR)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand op1 = new_temp();
        Operand op2 = new_temp();
        translate_Exp(first, op1);
        translate_Exp(third, op2);
        create_InterCode_threeOp(place, op1, op2, IR_MUL);
    }
    //Exp -> Exp DIV Exp
    else if (first->type == Exp && get_child(node, 2)->type == DIV)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand op1 = new_temp();
        Operand op2 = new_temp();
        translate_Exp(first, op1);
        translate_Exp(third, op2);
        create_InterCode_threeOp(place, op1, op2, IR_DIV);
    }
    // Exp -> MINUS Exp
    else if (first->type == MINUS)
    {
        struct GrammarTree *second = get_child(node, 2);
        Operand op1 = new_temp();
        translate_Exp(second, op1);
        Operand op2 = new_int_Operand(0, OP_CONSTANT);
        create_InterCode_threeOp(place, op2, op1, IR_SUB);
    }
    /*
    Exp -> NOT Exp
        -> Exp AND Exp
        -> Exp OR Exp
        -> Exp RELOP Exp
    */
    else if (first->type == NOT || get_child(node, 2)->type == AND || get_child(node, 2)->type == OR || get_child(node, 2)->type == RELOP)
    {
        Operand label1 = new_label();
        Operand label2 = new_label();
        Operand op1 = new_int_Operand(0, OP_CONSTANT);
        Operand op2 = new_int_Operand(1, OP_CONSTANT);
        create_InterCode_twoOp(place, op1, IR_ASSIGN);
        translate_Cond(node, label1, label2);
        create_InterCode_oneOp(label1, IR_LABEL);
        create_InterCode_twoOp(place, op2, IR_ASSIGN);
        create_InterCode_oneOp(label2, IR_LABEL);
    }
    /*
    Exp -> ID LP RP
        -> ID LP Args RP
    */
    else if (first->type == ID || get_child(node, 2)->type == LP)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand op = new_char_Operand(first->val.str, OP_FUNCTION);
        if (third->type == RP)
        {
            if (strcmp(first->val.str, "read") == 0)
                create_InterCode_oneOp(place, IR_READ);
            else
                create_InterCode_twoOp(place, op, IR_CALL);
        }
        else
        {
            struct OperandList *arg_list = NULL;
            translate_Args(third, &arg_list);
            if (strcmp(first->val.str, "write") == 0)
                create_InterCode_oneOp(arg_list->operand, IR_WRITE);
            else
            {
                struct OperandList *arg = arg_list;
                while (arg != NULL)
                {
                    Type t = search_with_name(arg->operand->u.name);
                    if (t != NULL && t->kind == STRUCTURE)
                    {
                        Operand op = new_variable();
                        renew_char(op, arg->operand->u.name, OP_ADDRESS);
                        create_InterCode_oneOp(op, IR_ARG);
                    }
                    // maybe improve: distinguish array
                    else
                    {
                        create_InterCode_oneOp(arg_list->operand, IR_ARG);
                    }
                    arg = arg->next;
                }
                create_InterCode_twoOp(place, op, IR_CALL);
            }
        }
    }
    //Exp -> Exp DOT ID
    else if (get_child(node, 2)->type == DOT)
    {
        Operand op1 = new_temp();
        translate_Exp(get_child(node, 1), op1);
        Type type = getBasicType(search_with_name(op1->u.name));
        int offset = get_offset(type, get_child(node, 3)->val.str);
        if (offset == 0)
        {
            if (op1->kind == OP_ADDRESS)
            {
                create_InterCode_threeOp(place, op1, new_int_Operand(0, OP_CONSTANT), IR_ADD_ADDR);
            }
            else
            {
                create_InterCode_twoOp(place, op1, IR_ASSIGNADDR);
            }
        }
        else
        {
            if (op1->kind == OP_ADDRESS)
            {
                create_InterCode_threeOp(place, op1, new_int_Operand(offset * 4, OP_CONSTANT), IR_ADD_ADDR);
            }
            else
            {
                Operand t = new_temp();
                create_InterCode_twoOp(t, op1, IR_ASSIGNADDR);
                create_InterCode_threeOp(place, t, new_int_Operand(offset * 4, OP_CONSTANT), IR_ADD_ADDR);
            }
        }
        set_Op_address(place);
        set_Op_name(place, get_child(node, 3)->val.str);
    }
    //Exp -> Exp1 LB Exp2 RB
    else if (get_child(node, 2)->type == LB)
    {
        Operand offset = new_temp();
        Operand id = new_temp();
        translate_Exp(get_child(node, 3), offset);
        translate_Exp(get_child(node, 1), id);
        assert(id->u.name != NULL);
        Type id_type = search_with_name(id->u.name);
        int size = getSize(getBasicType(id_type));
        if (offset->kind == OP_ADDRESS)
        {
            Operand t1 = new_temp();
            create_InterCode_twoOp(t1, offset, IR_ASSIGN);
            Operand t2 = new_temp();
            create_InterCode_threeOp(t2, t1, new_int_Operand(size * 4, OP_CONSTANT), IR_MUL);
            if (id->kind == OP_ADDRESS)
            {
                create_InterCode_threeOp(place, id, t2, IR_ADD_ADDR);
            }
            else
            {
                Operand t3 = new_temp();
                create_InterCode_twoOp(t3, id, IR_ASSIGNADDR);
                create_InterCode_threeOp(place, t3, t2, IR_ADD_ADDR);
            }
        }
        else
        {
            Operand t1 = new_temp();
            create_InterCode_threeOp(t1, offset, new_int_Operand(size * 4, OP_CONSTANT), IR_MUL);
            if (id->kind == OP_ADDRESS)
            {
                create_InterCode_threeOp(place, id, t1, IR_ADD_ADDR);
            }
            else
            {
                Operand t2 = new_temp();
                create_InterCode_twoOp(t2, id, IR_ASSIGNADDR);
                create_InterCode_threeOp(place, t2, t1, IR_ADD_ADDR);
            }
        }
        set_Op_address(place);
        set_Op_name(place, id->u.name);
    }
}
void translate_Stmt(struct GrammarTree *node)
{
    if (translate_success == 0)
        return;
    struct GrammarTree *first = get_child(node, 1);
    //Stmt -> Exp SEMI
    if (first->type == Exp)
    {
        translate_Exp(first, NULL);
    }
    //Stmt -> CompSt
    else if (first->type == CompSt)
    {
        translate_CompSt(first);
    }
    //Stmt -> RETURN Exp SEMI
    else if (first->type == RETURN)
    {
        Operand op = new_temp();
        translate_Exp(get_child(node, 2), op);
        create_InterCode_oneOp(op, IR_RETURN);
    }
    // Stmt -> IF LP Exp RP Stmt1 (ELSE Stmt2)
    else if (first->type == IF)
    {
        struct GrammarTree *exp = get_child(node, 3);
        struct GrammarTree *stmt1 = get_child(node, 5);
        Operand label1 = new_label();
        Operand label2 = new_label();
        translate_Cond(exp, label1, label2);
        create_InterCode_oneOp(label1, IR_LABEL);
        translate_Stmt(stmt1);
        if (get_child(node, 6) == NULL)
        {
            create_InterCode_oneOp(label2, IR_LABEL);
        }
        else
        {
            Operand label3 = new_label();
            struct GrammarTree *stmt2 = get_child(node, 7);
            create_InterCode_oneOp(label3, IR_GOTO);
            create_InterCode_oneOp(label2, IR_LABEL);
            translate_Stmt(stmt2);
            create_InterCode_oneOp(label3, IR_LABEL);
        }
    }
    //Stmt -> WHILE LP Exp RP Stmt1
    else if (first->type == WHILE)
    {
        Operand label1 = new_label();
        Operand label2 = new_label();
        Operand label3 = new_label();
        struct GrammarTree *exp = get_child(node, 3);
        struct GrammarTree *stmt1 = get_child(node, 3);
        create_InterCode_oneOp(label1, IR_LABEL);
        translate_Cond(exp, label2, label3);
        create_InterCode_oneOp(label2, IR_LABEL);
        translate_Stmt(stmt1);
        create_InterCode_oneOp(label1, IR_GOTO);
        create_InterCode_oneOp(label3, IR_LABEL);
    }
}

void translate_Cond(struct GrammarTree *node, Operand label_true, Operand label_false)
{
    if (translate_success == 0)
        return;
    struct GrammarTree *first = get_child(node, 1);
    struct GrammarTree *second = get_child(node, 2);
    if (first->type == NOT)
        translate_Cond(second, label_false, label_true);
    else if (second->type == RELOP)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand op1 = new_temp();
        Operand op2 = new_temp();
        translate_Exp(first, op1);
        translate_Exp(third, op2);
        Operand relop = new_char_Operand(get_relop(second), OP_RELOP);
        create_InterCode_fourOp(op1, relop, op2, label_true, IR_IFGOTO);
        create_InterCode_oneOp(label_false, IR_GOTO);
    }
    else if (second->type == AND)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand label1 = new_label();
        translate_Cond(first, label1, label_false);
        create_InterCode_oneOp(label1, IR_LABEL);
        translate_Cond(third, label_true, label_false);
    }
    else if (second->type == OR)
    {
        struct GrammarTree *third = get_child(node, 3);
        Operand label1 = new_label();
        translate_Cond(first, label_true, label1);
        create_InterCode_oneOp(label1, IR_LABEL);
        translate_Cond(third, label_true, label_false);
    }
    else
    {
        Operand label1 = new_label();
        translate_Exp(node, label1);
        Operand op2 = new_int_Operand(0, OP_CONSTANT);
        Operand relop = new_char_Operand("!=", OP_RELOP);
        create_InterCode_fourOp(label1, relop, op2, label_true, IR_IFGOTO);
        create_InterCode_oneOp(label_false, IR_GOTO);
    }
}
void translate_Args(struct GrammarTree *node, struct OperandList **arg_list)
{
    Operand op = new_temp();
    struct GrammarTree *first = get_child(node, 1);
    if (first->type == Exp && get_child(node, 2) == NULL)
    {
        translate_Exp(first, op);
        if (op->kind == OP_VARIABLE)
        {
            Type arg_type = search_with_name(op->u.name);
            if (arg_type != NULL)
            {
                if (arg_type->kind == ARRAY)
                {
                    translate_success = 0;
                    printf("Cannot translate: Code contains parameters of array type.\n");
                    return;
                }
            }
        }
        add_operand(op, arg_list);
    }
    else
    {
        struct GrammarTree *third = get_child(node, 3);
        translate_Exp(first, op);
        if (op->kind == OP_VARIABLE)
        {
            Type arg_type = search_with_name(op->u.name);
            if (arg_type->kind == ARRAY)
            {
                translate_success = 0;
                printf("Cannot translate: Code contains parameters of array type.\n");
                return;
            }
        }
        add_operand(op, arg_list);
        translate_Args(third, arg_list);
    }
}
