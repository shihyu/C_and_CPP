#define STRU struct student
#define KEY age
STRU {
    int num;
    char name[8];
    char sex;
    int age;
};

#include "stdio.h"
#include "sech.c"
#include "Fsech.c"

main()
{
    int i, q, a;
    long int k;
    static STRU x[16] = {{101, "Zhao", 'M', 19},
        {102, "Qian", 'F', 18}, {103, "Sun", 'M', 19},
        {104, "Li", 'F', 20}, {105, "Zhou", 'M', 19},
        {106, "Wu", 'F', 18}, {107, "Zheng", 'M', 17},
        {108, "Wang", 'F', 21}, {109, "Jiang", 'M', 19},
        {110, "Shen", 'F', 18}, {111, "Chu", 'M', 19},
        {112, "Wei", 'F', 19}, {113, "He", 'M', 18},
        {114, "Lv", 'F', 18}, {115, "Shi", 'M', 19},
        {110, "Zhang", 'F', 18}
    };
    FILE* fp;
    STRU str;
    printf("Serch from Array: \n");
    a = 18;
    i = 0;

    do {
        q = sech(x, 16, i, a);                      /* 查找并打印*/

        if (q != -1)
            printf("%-5d%-8s%-2c%-2d%\n", x[q].num,
                   x[q].name, x[q].sex, x[q].age);

        i = q + 1;
    } while (q != -1);

    k = sizeof(STRU);
    fp = fopen("stu.dat", "w+");                      /* 打开文件写*/

    for (i = 0; i < 16; i++)
        if (fwrite(&x[i], k, 1, fp) != 1) {           /* 写入文件*/
            printf("Cannot write file\n");           /* 写入失败*/
            i = 16;
        }

    fclose(fp);

    printf("\nSerch from File: \n");
    fp = fopen("stu.dat", "r+");                     /* 打开文件读*/

    do {
        q = Fsech(fp, a, &str);                      /* 查找并打印*/

        if (q)
            printf("%-5d%-8s%-2c%-2d%\n", str.num,
                   str.name, str.sex, str.age);
    } while (q);

    fclose(fp);
}

