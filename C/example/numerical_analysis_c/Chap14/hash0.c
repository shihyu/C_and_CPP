#define KEY name                                             /* 调用哈希函数需要的宏*/
#define NULLTag "\0"
#define DELTag "1\0"
#define HashSize 29

struct student {                                             /* 定义存放学生信息的结构体*/
    int num;
    char name[8];
    char sex;
    int age;
};

typedef struct student ElemType;
typedef struct student* ElemTypeP;
typedef ElemType hashlist[HashSize];
typedef char KeyType[8];

int KeyEqu(char* stra, char* strb);  /* 判断关键字是否相同*/
void ElemCP(ElemType* a,
            ElemType* b);                         /* 将元素b中内容拷贝到a中*/
void ElemDEL(ElemType*
             a);                                    /* 将元素a设成已删除*/
void ElemNULL(ElemType*
              a);                                   /* 将元素a设成空，用于初始化或清空哈希表*/

#include "stdio.h"
#include "string.h"
#include "hashk.c"
#include "hashpos.c"
#include "hashins.c"
#include "hashsch.c"
#include "hashdel.c"

main()
{
    int i, m;
    static ElemType x[16] = {{101, "Zhao", 'M', 19},
        {102, "Qian", 'F', 18}, {103, "Sun", 'M', 19},
        {104, "Li", 'F', 20}, {105, "Zhou", 'M', 19},
        {106, "Wu", 'F', 18}, {107, "Zheng", 'M', 17},
        {108, "Wang", 'F', 21}, {109, "Jiang", 'M', 19},
        {110, "Shen", 'F', 18}, {111, "Chu", 'M', 19},
        {112, "Wei", 'F', 19}, {113, "He", 'M', 18},
        {114, "Lv", 'F', 18}, {115, "Shi", 'M', 19},
        {110, "Zhang", 'F', 18}
    };
    KeyType a = "Zhou";                                /* a为要查找的关键字*/
    hashlist HT;                                        /* 定义哈希表*/
    m = HashSize;

    for (i = 0; i < m; i++) {                           /* 初始化哈希表*/
        ElemNULL(&HT[i]);
    }

    for (i = 0; i < 16; i++) {                          /* 将元素插入哈希表*/
        hashins(HT, m, x[i]);
    }

    i = hashsch(HT, m, a);                              /* 在哈希表中查找*/

    if (i != -1) {
        printf("%-5d%-8s%-2c%-2d%\n", HT[i].num, HT[i].name, HT[i].sex, HT[i].age);
    }
}

int KeyEqu(char* stra, char* strb)   /* 判断关键字是否相同*/
{
    return (!strcmp(stra, strb));
}

void ElemCP(ElemType* a,
            ElemType* b)                          /* 将元素b中内容拷贝到a中*/
{
    int i;
    a->num = b->num;

    for (i = 0; i < 8; i++) {
        a->name[i] = b->name[i];
    }

    a->name[7] = '\0';
    a->sex = b->sex;
    a->age = b->age;
}

void ElemDEL(ElemType*
             a)                                    /* 将元素a设成已删除*/
{
    int i;
    a->name[0] = '1';

    for (i = 1; i < 8; i++) {
        a->name[i] = '\0';
    }
}

void ElemNULL(ElemType*
              a)                                    /* 将元素a设成已删除*/
{
    int i;

    for (i = 0; i < 8; i++) {
        a->name[i] = '\0';
    }
}