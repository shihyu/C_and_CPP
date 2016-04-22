/*=============================================================
// 函 数 名：hashins
// 功能描述：在哈希表中插入一个元素
// 输入参数： HD 哈希表数组的指针
//            m 哈希表的长度，应该为素数
//            a 待插入的元素, a.KEY是它的关键字
// 返 回 值：若插入成功则返回1,否则返回0
//==============================================================*/

int hashins(HT, m, a)
hashlist HT;
int m;
ElemType a;
{
    int temp, d, i;
    d = hashpos(a.KEY, 0, m);
    temp = d;
    i = 1;

    while (!KeyEqu(HT[d].KEY, NULLTag) &&
           /* 常量NULLTag是空标志，需要自己定义*/
           !KeyEqu(HT[d].KEY,
                   DELTag)) {             /* 常量DELTag是指此处存放过元素，但是已被删除，需要自己定义*/
        d = (d + 2 * i - 1) % m;                   /* 不为空说明已经被占据，向后探查*/
        i++;

        if (d == temp) {                          /* 这时插入失败*/
            return (0);
        }
    }

    ElemCP(&HT[d], &a);                             /* 将a中内容拷贝到哈希表中*/
    return (1);
}