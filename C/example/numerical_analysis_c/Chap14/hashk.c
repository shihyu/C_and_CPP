/*=============================================================
// 函 数 名：hashk
// 功能描述：字符串哈希函数，将字符串转化成整数
// 输入参数： str 指向字符串的指针
//            i 选择算法，应在0~7之间
// 返 回 值：无符号整数，即字符串对应的整数
//==============================================================*/

unsigned int hashk(str, i)
char* str;
int i;
{
    static unsigned int ELFHash(char* str);         /*  ELF Hash Function */
    static unsigned int BKDRHash(char* str);        /*  BKDR Hash Function */
    static unsigned int RSHash(char* str);      /*  RS Hash Function */
    static unsigned int JSHash(char* str);      /*  JS Hash Function */
    static unsigned int PJWHash(char* str);         /*  PJW Hash Function */
    static unsigned int SDBMHash(char* str);        /*  SDBM Hash Function */
    static unsigned int DJBHash(char* str);         /*  DJB Hash Function */
    static unsigned int APHash(char* str);          /*  AP Hash Function */

    if (i == 0) {                           /* 选择调用*/
        return (ELFHash(str));
    } else if (i == 1) {
        return (BKDRHash(str));
    } else if (i == 2) {
        return (RSHash(str));
    } else if (i == 3) {
        return (JSHash(str));
    } else if (i == 4) {
        return (PJWHash(str));
    } else if (i == 5) {
        return (SDBMHash(str));
    } else if (i == 6) {
        return (DJBHash(str));
    } else if (i == 7) {
        return (APHash(str));
    } else {
        return (ELFHash(str));
    }
}

static unsigned int ELFHash(char* str)             /*  ELF Hash Function */
{
    unsigned int hash = 0;
    unsigned int x = 0;

    while (*str) {
        hash = (*str++) + (hash << 4);

        if ((x = hash & 0xF0000000L) != 0) {
            hash = hash ^ (x >> 24);
            hash = hash & (~x);
        }
    }

    return (hash & 0x7FFFFFFF);
}

static unsigned int BKDRHash(char* str)            /*  BKDR Hash Function */
{
    static unsigned int seed =
        13131;               /*  31 131 1313 13131 131313 etc..*/
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

static unsigned int RSHash(char* str)               /*  RS Hash Function */
{
    static unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str) {
        hash = hash * a + (*str++);
        a = a * b;
    }

    return (hash & 0x7FFFFFFF);
}

static unsigned int JSHash(char* str)               /*  JS Hash Function */
{
    unsigned int hash = 1315423911;

    while (*str) {
        hash = hash ^ ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

static unsigned int PJWHash(char*
                            str)              /*  P.J.Weinberger Hash Function*/
{
    unsigned int OneEighth = (unsigned int)(sizeof(unsigned int));
    unsigned int BitsofUI = (unsigned int)(OneEighth * 8);
    unsigned int ThreeQuarters = (unsigned int)(OneEighth * 6);
    unsigned int HighBits  = (unsigned int)(0xFFFFFFFF) << (BitsofUI - OneEighth);
    unsigned int hash  = 0;
    unsigned int test  = 0;

    while (*str) {
        hash = (hash << OneEighth) + (*str++);

        if ((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return (hash & 0x7FFFFFFF);
}

static unsigned int SDBMHash(char* str)               /*  SDBM Hash Function */
{
    unsigned int hash = 0;

    while (*str) {
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

static unsigned int DJBHash(char* str)                 /*  DJB Hash Function */
{
    unsigned int hash = 5381;

    while (*str) {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

static unsigned int APHash(char* str)                  /*  AP Hash Function */
{
    unsigned int hash = 0;
    int i = 0;

    while (*str)
        if ((i++) & 1) {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        } else {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }

    return (hash & 0x7FFFFFFF);
}

