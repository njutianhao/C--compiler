#include"InterMediate.h"
Operand table[10000];
int top = 0;
char *nameTable[10000];
int vNum = 0;


char *generateString(char *a,char *b){
    int aL = strlen(a);
    int bL = strlen(b);
    int size = aL+bL+1;
    char *res = (char *)malloc(size);
    return strcat(strcpy(res,a),b);
}


char *itoa(int i){
    assert(i>0);
    int tmp = i;
    int count = 0;
    while(tmp != 0){
        tmp/=10;
        count++;
    }
    char *res = (char *)malloc(count + 1);
    res[count] = 0;
    count--;
    while(count >= 0)
    {
        res[count] = i%10 + '0';
        i/=10;
        count--;
    }
    return res;
}

char *getName(char *name){
    for(int i = 0;i < vNum;i++)
        if(strcmp(nameTable[i],name) == 0)
        {
            return nameTable[i];
        }
    char *newNameNum = itoa(vNum+1);
    char *newName = generateString("v",newNameNum);
    nameTable[vNum++] = newName;
    free(newNameNum);
    return newName;
}

void init(){
    head.next = &head;
    head.prev = &head;
}

void add_operand(Operand operand,struct OperandList ** head){
    if(*head == NULL)
    {
        *head = (struct OperandList*)malloc(sizeof(struct OperandList));
        (*head)->operand = operand;
        (*head)->next = NULL; 
    }
    else
    {
        struct OperandList *tmp = *head;
        *head = (struct OperandList*)malloc(sizeof(struct OperandList));
        (*head)->operand = operand;
        (*head)->next = tmp; 
    }
}

char *getOperandName(Operand o){
    if(o->u.vname ==NULL)
        return o->u.name;
    return o->u.vname;
}

Operand new_temp(){
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind=OP_CONSTANT;
    res->u.vname=NULL;
    return res;
}
Operand new_label(){
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = OP_LABEL;
    res->u.vname =NULL;
    return res;
}
Operand new_variable(){
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = OP_VARIABLE;
    res->u.vname = NULL;
    return res;
}
Operand new_char_Operand(char *name, int OpKind){
    assert(top < 10000);
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = OpKind;
    res->u.name = name;
    res->u.vname=getName(name);
    table[top++] = res;
    return res;
}
Operand new_int_Operand(int val, int OpKind){
    assert(top < 10000);
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = OpKind;
    res->u.value = val;
    table[top++] = res;
    res->u.vname=NULL;
    return res;
}

void create_InterCode_oneOp(Operand op, int CodeKind){
    struct InterCodes *tmp = (struct InterCodes *)malloc(sizeof(struct InterCodes));   
    tmp->prev = head.prev;
    tmp->next = &head;
    head.prev->next = tmp;
    head.prev = tmp;
    tmp->code.kind = CodeKind;
    tmp->code.u.single = op;
}
void create_InterCode_twoOp(Operand op1,Operand op2,int CodeKind){
    struct InterCodes *tmp = (struct InterCodes *)malloc(sizeof(struct InterCodes));   
    tmp->prev = head.prev;
    tmp->next = &head;
    head.prev->next = tmp;
    head.prev = tmp;
    tmp->code.kind = CodeKind;
    tmp->code.u.assign.left= op1;
    tmp->code.u.assign.right = op2;
}
void create_InterCode_threeOp(Operand op1,Operand op2,Operand op3,int CodeKind){
    struct InterCodes *tmp = (struct InterCodes *)malloc(sizeof(struct InterCodes));   
    tmp->prev = head.prev;
    tmp->next = &head;
    head.prev->next = tmp;
    head.prev = tmp;
    tmp->code.kind = CodeKind;
    tmp->code.u.binop.result = op1;
    tmp->code.u.binop.op1 = op2;
    tmp->code.u.binop.op2 = op3;
}
void create_InterCode_fourOp(Operand op1,Operand relop,Operand op2,Operand label,int CodeKind){
    struct InterCodes *tmp = (struct InterCodes *)malloc(sizeof(struct InterCodes));   
    tmp->prev = head.prev;
    tmp->next = &head;
    head.prev->next = tmp;
    head.prev = tmp;
    tmp->code.kind = CodeKind;
    tmp->code.u.control.label = label;
    tmp->code.u.control.relop = relop;
    tmp->code.u.control.op1 = op1;
    tmp->code.u.control.op2 = op2;
}

void renew_int(Operand *op,int value,int OpKind){
    assert(op!=NULL);
    for(int i = 0;i < top;i++)
    {
        if(table[i]->kind == OpKind && table[i]->u.value == value)
        {
            *op = table[i];
            return ;
        }
    }
}
void renew_char(Operand *op,char* name,int OpKind){
    assert(op!=NULL);
    for(int i = 0;i < top;i++)
    {
        if(table[i]->kind == OpKind && strcmp(table[i]->u.name,name) == 0)
        {
            *op = table[i];
            return ;
        }
    }
}

void generateCode(char *fileName){
    FILE * f = fopen(fileName, "w");
    struct InterCodes *p = head.next;
    Operand o1,o2,o3,o4;
    char *s1,*s2,*s3,*s4,*s5,*s6,*s7,*s8,*num;
    while(p != &head){
        switch(p->code.kind){
            case IR_ASSIGN:
                o1 = p->code.u.assign.left;
                o2 = p->code.u.assign.right;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_VARIABLE);
                s1 = generateString(getOperandName(o1)," := ");
                s2 = generateString(s1,getOperandName(o2));
                s3 = generateString(s2,"\n");
                fputs(s3,f);
                free(s1);
                free(s2);
                free(s3);
                break;
            case IR_ASSIGNADDR:
                o1 = p->code.u.assign.left;
                o2 = p->code.u.assign.right;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_ADDRESS);
                s1 = generateString(getOperandName(o1)," := &");
                s2 = generateString(s1,getOperandName(o2));
                s3 = generateString(s2,"\n");
                fputs(s3,f);
                free(s1);
                free(s2);
                free(s3);
                break;
            case IR_ASSIGNMEM:
                o1 = p->code.u.assign.left;
                o2 = p->code.u.assign.right;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_ADDRESS);
                s1 = generateString(getOperandName(o1)," := *");
                s2 = generateString(s1,getOperandName(o2));
                s3 = generateString(s2,"\n");
                fputs(s3,f);
                free(s1);
                free(s2);
                free(s3);
                break;
            case IR_MEMASSIGN:
                o1 = p->code.u.assign.left;
                o2 = p->code.u.assign.right;
                assert(o1->kind==OP_ADDRESS && o2->kind == OP_VARIABLE);
                s1 = generateString("*",getOperandName(o1));
                s2 = generateString(s1," := ");
                s3 = generateString(s2,getOperandName(o2));
                s4 = generateString(s3,"\n");
                fputs(s4,f);
                free(s1);
                free(s2);
                free(s3);
                free(s4);
                break;
            case IR_ADD:
                o1 = p->code.u.binop.op1;
                o2 = p->code.u.binop.op2;
                o3 = p->code.u.binop.result;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_VARIABLE);
                s1 = generateString(getOperandName(o3)," := ");
                s2 = generateString(s1,getOperandName(o1));
                s3 = generateString(s2," + ");
                s4 = generateString(s3,getOperandName(o2));
                s5 = generateString(s4,"\n");
                fputs(s5,f);
                free(s1);
                free(s2);
                free(s3);
                free(s4);
                free(s5);
                break;
            case IR_SUB:
                o1 = p->code.u.binop.op1;
                o2 = p->code.u.binop.op2;
                o3 = p->code.u.binop.result;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_VARIABLE);
                s1 = generateString(getOperandName(o3)," := ");
                s2 = generateString(s1,getOperandName(o1));
                s3 = generateString(s2," - ");
                s4 = generateString(s3,getOperandName(o2));
                s5 = generateString(s4,"\n");
                fputs(s5,f);
                free(s1);
                free(s2);
                free(s3);
                free(s4);
                free(s5);
                break;
            case IR_MUL:
                o1 = p->code.u.binop.op1;
                o2 = p->code.u.binop.op2;
                o3 = p->code.u.binop.result;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_VARIABLE);
                s1 = generateString(getOperandName(o3)," := ");
                s2 = generateString(s1,getOperandName(o1));
                s3 = generateString(s2," * ");
                s4 = generateString(s3,getOperandName(o2));
                s5 = generateString(s4,"\n");
                fputs(s5,f);
                free(s1);
                free(s2);
                free(s3);
                free(s4);
                free(s5);
                break;
            case IR_DIV:
                o1 = p->code.u.binop.op1;
                o2 = p->code.u.binop.op2;
                o3 = p->code.u.binop.result;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_VARIABLE);
                s1 = generateString(getOperandName(o3)," := ");
                s2 = generateString(s1,getOperandName(o1));
                s3 = generateString(s2," / ");
                s4 = generateString(s3,getOperandName(o2));
                s5 = generateString(s4,"\n");
                fputs(s5,f);
                free(s1);
                free(s2);
                free(s3);
                free(s4);
                free(s5);
                break;
            case IR_FUNCTION:
                o1 = p->code.u.single;
                assert(o1->kind==OP_FUNCTION);
                s1 = generateString("FUNCTION ",getOperandName(o1));
                s2 = generateString(s1," :\n");
                fputs(s2,f);
                free(s1);
                free(s2);
                break;
            case IR_PARAM:
                o1 = p->code.u.single;
                assert(o1->kind==OP_VARIABLE);
                s1 = generateString("PARAM ",getOperandName(o1));
                s2 = generateString(s1,"\n");
                fputs(s2,f);
                free(s1);
                free(s2);
                break;
            case IR_LABEL:
                o1 = p->code.u.single;
                assert(o1->kind==OP_LABEL);
                s1 = generateString("LABEL ",getOperandName(o1));
                s2 = generateString(s1," :\n");
                fputs(s2,f);
                free(s1);
                free(s2);
                break;
            case IR_IFGOTO:
                o1 = p->code.u.control.op1;
                o2 = p->code.u.control.op2;
                o3 = p->code.u.control.relop;
                o4 = p->code.u.control.label;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_VARIABLE && o3->kind==OP_RELOP && o4->kind == OP_LABEL);
                s1 = generateString("IF ",getOperandName(o1));
                s2 = generateString(s2," [");
                s3 = generateString(s2,getOperandName(o3));
                s4 = generateString(s3,"] ");
                s5 = generateString(s4,getOperandName(o2));
                s6 = generateString(s5," GOTO ");
                s7 = generateString(s6,getOperandName(o4));
                s8 = generateString(s7,"\n");
                fputs(s8,f);
                free(s1);
                free(s2);
                free(s3);
                free(s4);
                free(s5);
                free(s6);
                free(s7);
                free(s8);
                break;
            case IR_GOTO:
                o1 = p->code.u.single;
                assert(o1->kind==OP_LABEL);
                s1 = generateString("GOTO ",getOperandName(o1));
                s2 = generateString(s1,"\n");
                fputs(s2,f);
                free(s1);
                free(s2);
                break;
            case IR_CALL:
                o1 = p->code.u.assign.left;
                o2 = p->code.u.assign.right;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_FUNCTION);
                s1 = generateString(getOperandName(o1)," := CALL ");
                s2 = generateString(s1,getOperandName(o2));
                s3 = generateString(s2,"\n");
                fputs(s3,f);
                free(s1);
                free(s2);
                free(s3);
                break;
            case IR_READ:
                o1 = p->code.u.single;
                assert(o1->kind==OP_VARIABLE);
                s1 = generateString("READ ",getOperandName(o1));
                s2 = generateString(s1,"\n");
                fputs(s2,f);
                free(s1);
                free(s2);
                break;
            case IR_WRITE:
                o1 = p->code.u.single;
                assert(o1->kind==OP_VARIABLE);
                s1 = generateString("WRITE ",getOperandName(o1));
                s2 = generateString(s1,"\n");
                fputs(s2,f);
                free(s1);
                free(s2);
                break;
            case IR_ARG:
                o1 = p->code.u.single;
                assert(o1->kind==OP_VARIABLE);
                s1 = generateString("ARG ",getOperandName(o1));
                s2 = generateString(s1,"\n");
                fputs(s2,f);
                free(s1);
                free(s2);
                break;
            case IR_RETURN:
                o1 = p->code.u.single;
                assert(o1->kind==OP_VARIABLE);
                s1 = generateString("RETURN ",getOperandName(o1));
                s2 = generateString(s1,"\n");
                fputs(s2,f);
                free(s1);
                free(s2);
                break;
            case IR_DEC:
                o1 = p->code.u.assign.left;
                o2 = p->code.u.assign.right;
                assert(o1->kind==OP_VARIABLE && o2->kind == OP_CONSTANT);
                s1 = generateString("DEC ",getOperandName(o1));
                s2 = generateString(s1," [");
                free(s1);
                s1 = itoa(o2->u.value);
                s3 = generateString(s2,s1);
                s4 = generateString(s3,"]\n");
                fputs(s3,f);
                free(s1);
                free(s2);
                free(s3);
                free(s4);
                break;
            default:printf("Unknown CodeKind %d\n",p->code.kind);
            assert(0);
            break;
        }
        p = p->next;
    }
}