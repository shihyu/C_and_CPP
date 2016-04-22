/*=============================================================
// 函 数 名：hashdel
// 功能描述：在哈希表中删除一个元素
// 输入参数： HD 哈希表数组的指针
//            m 哈希表的长度，应该为素数
//            a 待删除的元素, a.KEY是它的关键字
// 返 回 值：若删除成功则返回1,否则返回0
//==============================================================*/

int hashdel(HT, m, a)
hashlist HT;
int m;
ElemType a;
{
    int temp, d, i;
    d = hashpos(a.KEY, 0, m);
    temp = d;
    i = 1;

    while (!KeyEqu(HT[d].KEY,
                   NULLTag)) {          /* 常量NULLTag是空标志，需要自己定义*/
        if (KeyEqu(HT[d].KEY, a.KEY)) {           /* 已经找到，返回位置*/
            ElemDEL(&HT[d]);
            return (1);
        }

        d = (d + 2 * i - 1) %
            m;                 /* 不为空且不相等，说明已经被其它元素占据，向后探查*/
        i++;

        if (d == temp) {                         /* 这时删除失败*/
            return (0);
        }
    }

    return (0);                                   /* 这时删除失败*/
}