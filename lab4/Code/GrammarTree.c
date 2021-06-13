#include "GrammarTree.h"
#include "syntax.tab.h"
#include "Error.h"
struct GrammarTree *root = NULL;
char *token_map[] = {"Program", "ExtDecList", "ExtDef", "Specifier", "FunDec", "CompSt",
                     "VarDec", "ExtDefList", "StructSpecifier",
                     "OptTag", "DefList", "Tag", "VarList", "ParamDec",
                     "StmtList", "Stmt", "Exp", "Def", "DecList", "Dec", "Args", "error"};
char *token2_map[] = {"SEMI","COMMA","ASSIGNOP","PLUS","MINUS","STAR","DIV","AND","OR","NOT",
                      "DOT","TYPE","LP","RP","LB","RB","LC","RC","STRUCT","RETURN","IF","ELSE",
                      "WHILE","INT","FLOAT","ID","RELOP","SUB","UMINUS","LOWER_THAN_ELSE"};
char *token2_symbol_map[] = {";", ",", "=", "+",
                             "-", "*","/", "&&", "||", "!", ".", "TYPE", "(", ")", "[", "]", "{", "}", "STRUCT", "RETURN",
                             "IF", "ELSE", "WHILE", "INT", "FLOAT", "ID", "RELOP", "-","-","LOWER_THAN_ELSE"};
void insert(struct GrammarTree *t1, struct GrammarTree *t2)
{
    if (t1->head == NULL)
    {
        t1->head = (struct ListNode *)malloc(sizeof(struct ListNode));
        t1->head->val = t2;
        t1->head->next = NULL;
    }
    else
    {
        struct ListNode *l = t1->head;
        while (l->next != NULL)
        {
            l = l->next;
        }
        l->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        l = l->next;
        l->val = t2;
        l->next = NULL;
    }
}
void __DFS(struct GrammarTree *n, int depth)
{
    struct ListNode *l = n->head;
    switch (n->type)
    {
    case error:
    {
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("error\n");
        return;
    }
    case Program:
    case ExtDecList:
    case ExtDef:
    case Specifier:
    case FunDec:
    case CompSt:
    case VarDec:
    case ExtDefList:
    case StructSpecifier:
    case OptTag:
    case DefList:
    case Tag:
    case VarList:
    case ParamDec:
    case StmtList:
    case Stmt:
    case Exp:
    case Def:
    case DecList:
    case Dec:
    case Args:
        if (l == NULL)
            return;
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("%s (%d)\n", token_map[n->type], n->line);
        while (l != NULL)
        {
            __DFS(l->val, depth + 1);
            l = l->next;
        }
        return;
    case TYPE:
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("TYPE: %s\n", n->val.str);
        return;
    case ID:
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("ID: %s\n", n->val.str);
        return;
    case INT:
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("INT: %d\n", n->val.i);
        return;
    case FLOAT:
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("FLOAT: %f\n", n->val.f);
        return;
    case SEMI:
    case COMMA:
    case ASSIGNOP:
    case PLUS:
    case MINUS:
    case STAR:
    case DIV:
    case AND:
    case OR:
    case NOT:
    case DOT:
    case LP:
    case RP:
    case LB:
    case RB:
    case LC:
    case RC:
    case STRUCT:
    case RETURN:
    case IF:
    case ELSE:
    case WHILE:
    case RELOP:
    case SUB:
    case LOWER_THAN_ELSE:
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("%s\n", token2_map[n->type - BASE_NUM]);
        return;
    }
}
int check_error()
{
    if (HaveErrors == 0 && root != NULL)
        return 0;
    return 1;
}
void print_tree()
{
    __DFS(root, 0);
}
struct GrammarTree *createnode(int type, int line, void *value)
{
    struct GrammarTree *res = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
    res->type = type;
    res->line = line;
    res->head = NULL;
    if (type == ID || type == TYPE)
    {
        res->val.str = *((char **)value);
    }
    else if (type == INT || type == RELOP)
    {
        res->val.i = *((int *)value);
    }
    else if (type == FLOAT)
    {
        res->val.f = *(float *)value;
    }
    return res;
}

void insertall(struct GrammarTree *parent, int num, ...)
{
    va_list ap;
    va_start(ap, num);
    for (int i = 0; i < num; i++)
    {
        struct GrammarTree *tmp = va_arg(ap, struct GrammarTree *);
        insert(parent, tmp);
    }
    va_end(ap);
}

struct GrammarTree *get_child(struct GrammarTree *node, int index)
{
    struct ListNode *head = node->head;
    for (int i = 1; i < index; i++)
    {
        if (head == NULL)
            return NULL;
        head = head->next;
    }
    if (head == NULL)
        return NULL;
    return head->val;
}
char *get_relop(struct GrammarTree *node)
{
    assert(node->type == RELOP);
    char *result = malloc(sizeof(char) * 5);
    switch (node->val.i)
    {
    case L:
    {
        strcpy(result, "<");
        break;
    }
    case LE:
    {
        strcpy(result, "<=");
        break;
    }
    case G:
    {
        strcpy(result, ">");
        break;
    }
    case GE:
    {
        strcpy(result, ">=");
        break;
    }
    case EQ:
    {
        strcpy(result, "==");
        break;
    }
    case NEQ:
    {
        strcpy(result, "!=");
        break;
    }
    default:
    {
        printf("Relop error!");
        exit(0);
    }
    }
    return result;
}