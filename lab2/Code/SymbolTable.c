#include "SymbolTable.h"
//初始化
void initTable()
{
    for(int i=0;i<TABLE_SIZE;i++)
    {
        SymbolTable[i]=NULL;
        StructTable[i]=NULL;
        FunctionTable[i]=NULL;
    }
    headptr=NULL;
    namelessStructNumber=0;
}

//hash函数
unsigned int hash_pjw(char* name)
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~TABLE_SIZE) val = (val ^ (i >> 12)) & TABLE_SIZE;
    }
    return val;
}
//插入新的节点
void insert_Node(Type type_in,char* name)
{
    struct TableNode* temp=(struct TableNode*)malloc(sizeof(struct TableNode));
    unsigned int hashnum=0;
    temp->next=NULL;
    temp->type=type_in;
    if(name!=NULL)
    {
        hashnum=hash_pjw(name);
        temp->name=malloc(strlen(name)+1);
        strcpy(temp->name,name);
    }
    else temp->name=NULL;
    temp->next=NULL;
    temp->ifdef=0;
    if(type_in->kind==STRUCTURE)
    {
        if(name!=NULL && strcmp(type_in->u.structure.structName,name)==0)
        {
            if(StructTable[hashnum]==NULL) StructTable[hashnum]=temp;
            else
            {
                temp->next=StructTable[hashnum];
                StructTable[hashnum]=temp;
            }
        }
        else if(name==NULL)
        {
            temp->name=malloc(sizeof(char)*15);
            int i=0;
            int num=namelessStructNumber;
            do
            {
                temp->name[i]=num%10+'0';
                i++;
                num=num/10;
            } while (num!=0 && i<14);
            temp->name[i]='\0';
            namelessStructNumber++;
            temp->type->u.structure.structName=malloc(strlen(temp->name)+1);
            strcpy(temp->type->u.structure.structName,temp->name);
            hashnum=hash_pjw(temp->name);
            if(StructTable[hashnum]==NULL ) StructTable[hashnum]=temp;
            else
            {
                temp->next=StructTable[hashnum];
                StructTable[hashnum]=temp;
            }
        }
    }
    else if(type_in->kind==FUNCTION)
    {
        if(FunctionTable[hashnum]==NULL) FunctionTable[hashnum]=temp;
        else{
            temp->next=FunctionTable[hashnum];
            FunctionTable[hashnum]=temp;
        }
        return;
    }
    if(SymbolTable[hashnum]==NULL) SymbolTable[hashnum]=temp;
    else
    {
        temp->next=SymbolTable[hashnum];
        SymbolTable[hashnum]=temp;
    }
}
//创建Basic type类型
Type create_Basic_Type(char* ifint)
{
    Type temp=(Type)malloc(sizeof(struct Type_));
    if(strcmp(ifint,"int")==0) temp->kind=BASIC_INT;
    else if(strcmp(ifint,"float")==0) temp->kind=BASIC_FLOAT;
    else 
    {
        printf("Unknown type: %s.\n",ifint);
        exit(0);
    }
    return temp;
}
//创建Array type类型
Type create_Array_Type(Type paratype,int size_in)
{
    Type temp=(Type)malloc(sizeof(struct Type_));
    temp->kind=ARRAY;
    temp->u.array.size=size_in;
    temp->u.array.elem=paratype;
    return temp;
}
//创建structure type类型,同时完成FieldList_的接口
FieldList new_FieldList(char* name_in,Type type_in,int line_no)
{
    FieldList temp=(FieldList)malloc(sizeof(struct FieldList_));
    temp->next=NULL;
    if(name_in==NULL) temp->name=NULL;
    else 
    {
        temp->name=malloc(strlen(name_in)+1);
        strcpy(temp->name,name_in);
     }
    temp->type=type_in;
    temp->lineno=line_no;
    return temp;
}

FieldList insert_FieldList(FieldList head,FieldList ptr)
{
    if(head==NULL) return ptr;
    if(ptr==NULL) return head;
    FieldList p=head;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    p->next=ptr;
    return head;
}
void free_FieldList(FieldList head)
{
    while(head != NULL)
    {
        FieldList temp = head->next;
        free(head);
        head = temp;
    }
}

//FieldList是否有重名变量
FieldList FieldList_repeat(FieldList head,FieldList ptr)
{
    FieldList tempHead=head;
    FieldList tempPtr=ptr;
    FieldList repeatHead=NULL;
    for(;tempHead!=NULL;tempHead=tempHead->next)
    {
        for(;tempPtr!=NULL;tempPtr=tempPtr->next)
        {
            if(strcmp(tempHead->name,tempPtr->name)==0)
            {
                FieldList p=(FieldList)malloc(sizeof(struct FieldList_));
                p->type=tempHead->type;
                p->next=NULL;
                if(tempHead->name!=NULL)
                {
                    p->name=malloc(strlen(tempHead->name)+1);
                    strcpy(p->name,tempHead->name);
                }
                else p->name=NULL;
                if(repeatHead==NULL) repeatHead=p;
                else
                {
                    FieldList tmp=repeatHead;
                    while (tmp->next!=NULL) tmp=tmp->next;
                    tmp->next=p;
                }
            } 
        }
    }
    return repeatHead;
}


Type create_Structure_Type(FieldList head,char* struct_Name)
{
    Type temp=(Type)malloc(sizeof(struct Type_));
    temp->kind=STRUCTURE;
    temp->u.structure.structmember=head;
    if(struct_Name!=NULL)
    {
        temp->u.structure.structName=malloc(strlen(struct_Name)+1);
        strcpy(temp->u.structure.structName,struct_Name);
    }
    else temp->u.structure.structName=NULL;
    return temp;
}
//创建function type类型
Type create_Function_Type(Type returntype,FieldList List,int declareline)
{
    Type temp=(Type)malloc(sizeof(struct Type_));
    temp->kind=FUNCTION;
    temp->u.function.returnType=returntype;
    temp->u.function.paramlist=List;
    temp->u.function.declare_line=declareline;
    return temp;
}

//检查函数是否声明(存在),1表示存在
Type if_declare(char* name)
{
    unsigned int hashnum=hash_pjw(name);
    struct TableNode* p=FunctionTable[hashnum];
    for(;p!=NULL;p=p->next)
    {
       if(strcmp(p->name,name)==0)
       {
           return p->type;
       }
    }
    return NULL;
}

//函数声明后又定义,返回0为正常定义,返回1为存在重复定义,-1为未查询到
int Define(char* name)
{
    unsigned int hashnum=hash_pjw(name);
    struct TableNode* p=FunctionTable[hashnum];
    for(;p!=NULL;p=p->next)
    {
       if(strcmp(p->name,name)==0)
       {
           if(p->ifdef==1) return 1;
           else 
           {
               p->ifdef=1;
               return 0;
           }
       }
    }
    return -1;
}
//检查是否定义,-1代表未查询到,
int if_define(char* name)
{
    unsigned int hashnum=hash_pjw(name);
    struct TableNode* p=FunctionTable[hashnum];
    for(;p!=NULL;p=p->next)
    {
       if(strcmp(p->name,name)==0) return p->ifdef;
    }
    return -1;    
}
//检查函数实参和形参类型匹配
int check_paralist(char* funcName,FieldList head)
{
    Type functype=search_function(funcName);
    if(functype==NULL){
        printf("Unknown function.\n");
        exit(0);
    }
    int num1=0,num2=0;
    for(FieldList p=functype->u.function.paramlist;p!=NULL;p=p->next)
        num1++;
    for(FieldList p=head;p!=NULL;p=p->next)
        num2++;
    if(num1!=num2) return 0;
    FieldList ptr1=functype->u.function.paramlist;
    FieldList ptr2=head;
    while(ptr1!=NULL && ptr2!=NULL)
    {
        if(same(ptr1->type,ptr2->type)!=1) return 0;
        ptr1=ptr1->next;
        ptr2=ptr2->next;
    }
    return 1;
}
//返回值类型匹配
int check_return(char* funcName,Type returntype)
{
    Type functype=search_function(funcName);
    if(functype==NULL){
        printf("Unknown function.\n");
        exit(0);
    }
    if(same(functype->u.function.returnType,returntype)==1) return 1;
    return 0;
}
//获取返回值类型
Type getReturnType(char* funcName)
{
    Type functype=search_function(funcName);
    if(functype==NULL){
        printf("Unknown function.\n");
        exit(0);
    }
    return functype->u.function.returnType;
}
Type getListHeadType(FieldList head)
{
    if(head!=NULL) return head->type;
    return NULL;
}
char* getFieldListName(FieldList list)
{
    return list->name;
}
Type getFieldListType(FieldList list)
{
    return list->type;
}
int getFieldListLine(FieldList list)
{
    return list->lineno;
}
//根据名字查询节点
Type search_with_name(char* Name)
{
    unsigned int number=hash_pjw(Name);
    struct TableNode* p=SymbolTable[number];
    for(;p!=NULL;p=p->next)
    {
       if(strcmp(p->name,Name)==0)
       {
           return p->type;
       }
    }
    return NULL;
}
//根据名字查询该名称结构体
Type search_struct(char* Name)
{
    if(Name==NULL) return NULL;
    //printf("%s\n",Name);
    unsigned int number=hash_pjw(Name);
    struct TableNode* p=StructTable[number];
    for(;p!=NULL;p=p->next)
    {
       if(strcmp(p->name,Name)==0)
       {
           return p->type;
       }
    }
    return NULL;
}
//根据名字查询函数
Type search_function(char* Name)
{
    unsigned int number=hash_pjw(Name);
    struct TableNode* p=FunctionTable[number];
    for(;p!=NULL;p=p->next)
    {
       if(strcmp(p->name,Name)==0)
       {
           return p->type;
       }
    }
    return NULL;
}

//某一变量、形参或者成员名是否已存在,是则返回1,不是则返回0
int name_exist(char* name)
{
    if(name==NULL) {
        return 0;
    }
    unsigned int hashnum=hash_pjw(name);
    struct TableNode* p=SymbolTable[hashnum];
    for(;p!=NULL;p=p->next)
    {
        if(strcmp(p->name,name)==0) return 1;
    }
    return 0;
}

//检查是否为同一类型，是则返回1，不是则返回0,异常则返回-1
int same(Type A,Type B)
{
    if(A==NULL||B==NULL) return -1;
    if(A->kind!=B->kind) return 0;
    switch (A->kind)
    {
    case BASIC_INT:
        {
            return 1;
            break;
        }
    case BASIC_FLOAT:
        {
            return 1;
            break;
        }
    case ARRAY:
        {
            int DimensionA=0,DimensionB=0;
            Type Atype=A;
            Type Btype=B;
            while(Atype!=NULL){
                DimensionA++;
                Atype=Atype->u.array.elem;
                if(Atype->kind!=ARRAY) break;
            }
            while(Btype!=NULL){
                DimensionB++;
                Btype=Btype->u.array.elem;
                if(Btype->kind!=ARRAY) break;
            }
            if(DimensionA!=DimensionB) return 0;
            if(same(Atype,Btype)==1) return 1;
            else return 0;
            break; 
        }   
    case STRUCTURE:
        {
            if(A->u.structure.structName==NULL && B->u.structure.structName==NULL) return 0;
            if(strcmp(A->u.structure.structName,B->u.structure.structName)==0) return 1;
            else return 0; 
            break;
        }
    case FUNCTION:
        {
            int flag=same(A->u.function.returnType,B->u.function.returnType);
            if(flag!=1) return flag;
            FieldList paramA=A->u.function.paramlist;
            FieldList paramB=B->u.function.paramlist;
            int Anum=0,Bnum=0;
            while(paramA!=NULL){
                Anum++;
                paramA=paramA->next;
            }
            while(paramB!=NULL)
            {
                Bnum++;
                paramB=paramB->next;
            }
            if(Anum!=Bnum) return 0;
            paramA=A->u.function.paramlist;
            paramB=B->u.function.paramlist;
            while(paramB!=NULL &&paramA!=NULL)
            {
                if(paramB->type->kind!=paramA->type->kind) return 0;
                flag=same(paramA->type,paramB->type);
                if(flag!=1) return flag;
                paramB=paramB->next;
                paramA=paramA->next;
            }
            return 1;
            break;
        }
    default:
        {
            printf("Unknown Type of the parameter.\n");
            break;
        }
    }

}


//type转KIND
enum KIND getKind(Type type){
    return type->kind;
}

enum KIND getKindwithName(char* name){
    unsigned int number=hash_pjw(name);
    struct TableNode* p=SymbolTable[number];
    for(;p!=NULL;p=p->next)
    {
       if(strcmp(p->name,name)==0)
       {
           return p->type->kind;
       }
    }
    p=FunctionTable[number];
    for(;p!=NULL;p=p->next)
    {
        if(strcmp(p->name,name)==0){
            return p->type->kind;
        }
    }
    printf("Unknown varaible name.\n");
    exit(0);
}
struct UndefinedFunction* get_undefined_function()
{
    for(int i=0;i<TABLE_SIZE;i++){
        if(FunctionTable[i]!=NULL)
        {
            struct TableNode* p=FunctionTable[i];
            for(;p!=NULL;p=p->next)
            {
                if(p->ifdef==0)
                {
                    struct UndefinedFunction* node=(struct UndefinedFunction*)malloc(sizeof(struct UndefinedFunction));
                    if(p->name!=NULL)
                    {
                        node->func_name=malloc(strlen(p->name)+1);
                        strcpy(node->func_name,p->name);
                    }
                    else node->func_name=NULL;
                    node->line=p->type->u.function.declare_line;
                    node->next=headptr;
                    headptr=node;                    
                }
            }
        }
    }
    return headptr;
}

char* generateStr(FieldList p)
{
    char* str=malloc(strlen("(")+1);
    strcpy(str,"(");
    while(p!=NULL)
    {
        printf("got here\n");
        if(p->type==NULL){ printf("gotcha\n");}
        printf("%d\n",p->type->kind);
        switch(p->type->kind)
        {
            case BASIC_INT:
            {
                char* temp=malloc(strlen(str)+strlen("int")+1);
                temp=strcat(strcpy(temp,str),"int");
                free(str);
                str=malloc(strlen(temp)+1);
                strcpy(str,temp);
                free(temp);
                break;
            }
            case BASIC_FLOAT:
            {
                char*temp=malloc(sizeof(str)+sizeof("float")+1);
                temp=strcat(strcpy(temp,str),"float");
                free(str);
                str=malloc(strlen(temp)+1);
                strcpy(str,temp);
                free(temp);
                break;
            }
            case ARRAY:
            {
                Type temp=p->type;
                int num=0;
                while(temp->kind==ARRAY)
                {
                    temp=temp->u.array.elem;
                    num++;
                }
                switch (temp->kind)
                {
                    case BASIC_INT:
                    {
                        char* tmp=malloc(sizeof(str)+sizeof("int")+1);
                        tmp=strcat(strcpy(tmp,str),"int");
                        free(str);
                        str=malloc(strlen(tmp)+1);
                        strcpy(str,tmp);
                        free(tmp);
                        for(int i=0;i<num;i++)
                        {
                            tmp=malloc(sizeof(str)+sizeof("[]")+1);
                            tmp=strcat(strcpy(tmp,str),"[]");
                            free(str);
                            str=malloc(strlen(tmp)+1);
                            strcpy(str,tmp);
                            free(tmp);
                        }
                        break;
                    }
                    case BASIC_FLOAT:
                    {
                        char* tmp=malloc(sizeof(str)+sizeof("float")+1);
                        tmp=strcat(strcpy(tmp,str),"float");
                        free(str);
                        str=malloc(strlen(tmp)+1);
                        strcpy(str,tmp);
                        free(tmp);
                        for(int i=0;i<num;i++)
                        {
                            tmp=malloc(sizeof(str)+sizeof("[]")+1);
                            tmp=strcat(strcpy(tmp,str),"[]");
                            free(str);
                            str=malloc(strlen(tmp)+1);
                            strcpy(str,tmp);
                            free(tmp);
                        }
                        break;
                    }
                    case STRUCTURE:
                    {
                        char* tmp=malloc(sizeof(str)+sizeof("struct ")+1);
                        tmp=strcat(strcpy(tmp,str),"struct ");
                        free(str);
                        str=malloc(strlen(tmp)+1);
                        strcpy(str,tmp);
                        free(tmp);
                        if(temp->u.structure.structName!=NULL && '0'<=temp->u.structure.structName[0] && temp->u.structure.structName[0]<='9')
                        {
                            //do nothing
                        }
                        else if(temp->u.structure.structName!=NULL)
                        {
                            tmp=malloc(sizeof(str)+strlen(temp->u.structure.structName)+1);
                            tmp=strcat(strcpy(tmp,str),temp->u.structure.structName);
                            free(str);
                            str=malloc(strlen(tmp)+1);
                            strcpy(str,tmp);
                            free(tmp);
                        }
                        else {
                            //do nothing
                        }
                        for(int i=0;i<num;i++)
                        {
                            tmp=malloc(sizeof(str)+sizeof("[]")+1);
                            tmp=strcat(strcpy(tmp,str),"[]");
                            free(str);
                            str=malloc(strlen(tmp)+1);
                            strcpy(str,tmp);
                            free(tmp);
                        }
                        break;
                    }
                    case FUNCTION:
                    {
                        printf("paralist error!");
                        exit(0);
                    }
                }
                break;
            }
            case STRUCTURE:
            {
                char* tmp=malloc(sizeof(str)+sizeof("struct ")+1);
                tmp=strcat(strcpy(tmp,str),"struct ");
                free(str);
                str=malloc(strlen(tmp)+1);
                strcpy(str,tmp);
                free(tmp);
                if(p->type->u.structure.structName!=NULL && '0'<=p->type->u.structure.structName[0] && p->type->u.structure.structName[0]<='9')
                {
                    //do nothing
                }
                else if(p->type->u.structure.structName!=NULL)
                {
                    tmp=malloc(sizeof(str)+strlen(p->type->u.structure.structName)+1);
                    tmp=strcat(strcpy(tmp,str),p->type->u.structure.structName);
                    free(str);
                    str=malloc(strlen(tmp)+1);
                    strcpy(str,tmp);
                    free(tmp);
                }
                else
                {
                    //do nothing
                }
                break;
            }
            case FUNCTION:
            {
                printf("paralist error!");
                exit(0);
            }
        }
        if(p->next!=NULL) 
        {
            char* tmp=malloc(sizeof(str)+sizeof(", ")+1);
            tmp=strcat(strcpy(tmp,str),", ");
            free(str);
            str=malloc(strlen(tmp)+1);
            strcpy(str,tmp);
            free(tmp);
        }
        else 
        {
            char* tmp=malloc(sizeof(str)+sizeof(")")+1);
            tmp=strcat(strcpy(tmp,str),")");
            free(str);
            str=malloc(strlen(tmp)+1);
            strcpy(str,tmp);
            free(tmp);        
        }
        printf("loop\n");
        p=p->next;
    }
    return str;
}

char *generateFuncStr(char *name){
    Type t = search_function(name);
    char *str = generateStr(t->u.function.paramlist);
    char *res = malloc(strlen(name) + strlen(str));
    return strcat(strcpy(res,name),str);
}

int isInt(Type t){
    return getKind(t) == BASIC_INT;
}

int isArray(Type t){
    return getKind(t) == ARRAY;
}

int isStruct(Type t){
    return getKind(t) == STRUCTURE;
}

Type getLowerArray(Type t){
    if(t->u.array.elem==NULL) printf("12345\n"); 
    return t->u.array.elem;
}

int isInStruct(Type t,char *name){
    FieldList f = t->u.structure.structmember;
    while(f != NULL)
    {
        if(strcmp(f->name,name) == 0)
            return 1;
        f = f->next;
    }
    return 0;
}

Type getFieldType(Type t,char *name){
    FieldList f = t->u.structure.structmember;
    while(f != NULL)
    {
        if(strcmp(f->name,name) == 0)
            return f->type;
        f = f->next;
    }
    return NULL;
}
FieldList getNextFieldList(FieldList f){
    if(f == NULL)
        return NULL;
    return f->next;
}

void displayFieldList(FieldList f){
    while(f != NULL)
    {
        printf("%s ",f->name);
        f = f->next;
    }
    printf("\n");
}