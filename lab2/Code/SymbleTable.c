#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 0x3fff

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

struct Type_
{
    enum { BASIC, ARRAY, STRUCTURE ,FUNCTION} kind; 
    union
    {
        int basic;// 基本类型 int(=0)&float(=other)                          
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
    struct FieldList_ nodeType;//节点存储的域信息
    struct TableNode* next;//hash表下一个元素指针
};


struct TableNode* SymbleTable[TABLE_SIZE];//符号表

void initTable();//初始化
unsigned int hash_pjw(char* name);//hash函数

void insert_Node(Type type_in,char* name);//插入新的节点
FieldList search_with_name(char* Name);//根据名字查询节点
int search_struct_with_type(Type type_in);//对于没有name的结构体只能根据type查找,返回是否存在等价structure,是为1，不是为0

Type create_Basic_Type(int ifint);//创建Basic type类型,0表示int
Type create_Array_Type(Type paratype,int size_in);//创建Array type类型
Type create_Structure_Type(FieldList head,char* struct_Name);//创建Structure type类型
Type create_Function_Type(Type returntype,FieldList List);//创建Funtion type类型

FieldList new_FieldList(char* name_in,Type type_in);//创建一个FieldList节点
int insert_FieldList(FieldList head,FieldList ptr);//向FieldList链表内插入节点

int same(Type A,Type B);//检查是否为同一类型，是则返回1，不是则返回0,异常则返回-1
int strict_array_same(Type A,Type B);//检查数组严格相等,返回值同same()


//初始化
void initTable()
{
    for(int i=0;i<TABLE_SIZE;i++)
        SymbleTable[i]=NULL;
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
    unsigned int hashnum=hash_pjw(name);
    temp->next=NULL;
    temp->nodeType.type=type_in;
    strcpy(temp->nodeType.name,name);
    temp->nodeType.next=NULL;
    if(SymbleTable[hashnum]==NULL) SymbleTable[hashnum]=temp;
    else
    {
        temp->next=SymbleTable[hashnum];
        SymbleTable[hashnum]=temp;
    }
}
//创建Basic type类型
Type create_Basic_Type(int ifint)//0表示int
{
    Type temp=(Type)malloc(sizeof(struct Type_));
    temp->kind=BASIC;
    if(ifint==0) temp->u.basic=0;
    else temp->u.basic=1;
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
FieldList new_FieldList(char* name_in,Type type_in)
{
    FieldList temp=(FieldList)malloc(sizeof(struct FieldList_));
    temp->next=NULL;
    strcpy(temp->name,name_in);
    temp->type=type_in;
    return temp;
}

int insert_FieldList(FieldList head,FieldList ptr)
{
    if(ptr==NULL||ptr->next!=NULL) return -1;
    ptr->next=head;
    head=ptr;
    return 0;
}

Type create_Structure_Type(FieldList head,char* struct_Name)
{
    Type temp=(Type)malloc(sizeof(struct Type_));
    temp->kind=STRUCTURE;
    temp->u.structure.structmember=head;
    strcpy(temp->u.structure.structName,struct_Name);
    return temp;
}
//创建function type类型
Type create_Function_Type(Type returntype,FieldList List)
{
    Type temp=(Type)malloc(sizeof(struct Type_));
    temp->kind=FUNCTION;
    temp->u.function.returnType=returntype;
    temp->u.function.paramlist=List;
    return temp;
}
//根据名字查询节点
FieldList search_with_name(char* Name)
{
    FieldList temp=NULL;
    unsigned int number=hash_pjw(Name);
    struct TableNode* p=SymbleTable[number];
    for(;p!=NULL;p=p->next)
    {
       if(strcmp(p->nodeType.name,Name)==0)
       {
           temp=(FieldList)malloc(sizeof(struct FieldList_));
           strcpy(temp->name,p->nodeType.name);
           temp->next=NULL;
           temp->type=p->nodeType.type;
           return temp;
       }
    }
    return temp;
}
//对于没有name的结构体只能根据type查找,返回是否存在等价structure
int search_struct_with_type(Type type_in)
{
    unsigned int num=hash_pjw(NULL);
    struct TableNode* p=SymbleTable[num];
    for(;p!=NULL;p=p->next)
    {
        if(same(p->nodeType.type,type_in)==1) return 1;
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
    case BASIC:
        {
            if(A->u.basic==0 && B->u.basic==0) return 1;
            else if(A->u.basic!=0 && B->u.basic!=0) return 1;
            else return 0;
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
            if(DimensionA==DimensionB) return 1;
            else return 0;
            break; 
        }   
    case STRUCTURE:
        {
            FieldList stAmember=A->u.structure.structmember;
            FieldList stBmember=B->u.structure.structmember;
            int Anum=0,Bnum=0;
            while(stAmember!=NULL){
                Anum++;
                stAmember=stAmember->next;
            }
            while(stBmember!=NULL)
            {
                Bnum++;
                stBmember=stBmember->next;
            }
            if(Anum!=Bnum) return 0;
            stAmember=A->u.structure.structmember;
            stBmember=B->u.structure.structmember;
            while(stAmember!=NULL && stBmember!=NULL)
            {
                if(stAmember->type->kind!=stBmember->type->kind) return 0;
                if(stAmember->type->kind==ARRAY){
                    //结构体中数组要严格相等
                    int flag=strict_array_same(stAmember->type,stBmember->type);
                    if(flag!=1) return flag;
                }
                else
                {
                    int flag=same(stAmember->type,stBmember->type);
                    if(flag!=1) return flag;
                }
                stAmember=stAmember->next;
                stBmember=stBmember->next;
            }
            return 1; 
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

//检查数组严格相等,返回值同same()
int strict_array_same(Type A,Type B)
{
    if(A==NULL || B==NULL) return -1;
    if(A->kind!=ARRAY || B->kind!=ARRAY) return -1;
    if(A->u.array.size!=B->u.array.size) return 0;
    Type elemA=A->u.array.elem;
    Type elemB=B->u.array.elem;
    if(elemA->kind!=elemB->kind) return 0;
    if(elemA->kind==ARRAY) return strict_array_same(elemA,elemB);
    else return same(elemA,elemB);
}