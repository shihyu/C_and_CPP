void Remez(double a, double b, double p[7], double (*f)(double))
/*
a 双精度实型变量。区间左端点值 b 双精度实型变量。区间右端点值
p双精度实型一维数组，长度为7。返回5次最佳一致逼近多项式的6个系数，最后一项为多项式的偏差(不一定为绝对值)
f 双精度实型函数指针变量。指向计算函数f(x)值的函数。
*/
{
    int i, j, k, m, kk; //i,j二维数组的行列，k一维数组元素号，m新值插入点
    double h = 0.00001 * (b - a);
    double x1, newx, s, t;
    double x[7], ff[7], X[7][7], temp[7][7], tempf[7];
    double (*xx)[7] =
        X;//存放X矩阵，指针的形式可以方便的完成每次迭代中的插入新一行的操作

    for (k = 0; k < 7; k++) {
        t = cos((6 - k) * PI / 6);
        x[k] = (b + a + (b - a) * t) / 2.0;
        ff[k] = (*f)(x[i]);
    }          //在区间内取n+1次切比雪夫多项式的交错点组做为初始点集

    double pre_mu = 1.0e35; //保证迭代能够进行
    double mu = 1.0;

    for (i = 0; i < 7; i++) {
        ff[i] = (*f)(x[i]);

        xx[i][0] = 1.0;

        for (j = 1; j < 6; j++) {
            xx[i][j] = x[i] * xx[i][j - 1];
        }

        xx[i][6] = mu;
        mu = -mu;
    }         //初始X矩阵构造

    //下面开始迭代
    int flagx;
    　　　//记录f(newx)-P(newx)的符号
    int times = 0; //记录迭代次数

    while (times < 100) {
        for (i = 0; i < 7; i++) {
            tempf[i] = ff[i];

            for (j = 0; j < 7; j++) {
                temp[i][j] = xx[i][j];
            }
        }

        Gauss_sort_all(temp, tempf, p, NULL);

        mu = fabs(p[6]);

        if (fabs(mu - pre_mu) < REPS) {
            return;    //满足精度要求，返回
        }

        pre_mu = mu;  //未满足精度要求，记录下此次的\mu,然后开始下面的运算
        //扫描寻找最大偏差点newx
        x1 = a;
        newx = a;   //newx记录新找到的最大偏差点

        while (x1 < b) {
            s = (*f)(x1);
            t = p[5];

            for (i = 4; i >= 0; i--) {
                t = t * x1 + p[i];
            }

            if (fabs(s - t) > mu) {
                flagx = (s - t) > 0 ? 1 : -1;
                mu = fabs(s - t);
                newx = x1;
            }

            x1 = x1 + h;
        }

        //扫描寻找最大偏差点应处的位置m
        for (i = 0; i < 7; i++)
            if (newx > x[i]) {
                m = i;
            }

        //分情况替换，同时更改系数矩阵xx和存放函数值的结果向量ff
        if (newx < x[0]) {
            kk = 0;    //记录下待修改的行号
            s = (*f)(x[0]);
            t = p[5];

            for (i = 4; i >= 0; i--) {
                t = t * x[0] + p[i];
            }

            s = s - t;

            if (s * flagx < 0.0) { //异号，添加到最前
                for (k = 5; k >= 0; k--) {
                    ff[k + 1] = ff[k];
                    x[k + 1] = x[k];
                }

                double* tempxx = xx[6];

                for (i = 6; i > 0; i--) {
                    xx[i] = xx[i - 1];
                }

                xx[0] = tempxx;
            }
        } else if (newx > x[6]) {
            kk = 6;   //记录下待修改的行号
            s = (*f)(x[6]);
            t = p[5];

            for (i = 4; i >= 0; i--) {
                t = t * x[6] + p[i];
            }

            s = s - t;

            if (s * flagx < 0.0) { //异号，添加到最后
                for (k = 0; k < 6; k++) {
                    ff[k] = ff[k + 1];
                    x[k] = x[k + 1];
                }

                double* tempxx = xx[0];

                for (i = 0; i < 6; i++) {
                    xx[i] = xx[i + 1];
                }

                xx[6] = tempxx;
            }
        } else { //最大值在x[m]与x[m+1]之间
            s = (*f)(x[m]);
            t = p[5];

            for (i = 4; i >= 0; i--) {
                t = t * x[m] + p[i];
            }

            s = s - t;

            if (s * flagx > 0.0) { //同号，则替换x[m]
                kk = m;       //记录下待修改的行号
                xx[kk][6] = -xx[kk + 1][6];
            } else {       //异号，则替换x[m+1]
                kk = m + 1;   //记录下待修改的行号
                xx[kk][6] = -xx[m][6];
            }
        }

        x[kk] = newx;
        ff[kk] = (*f)(x[kk]);

        for (j = 1; j < 6; j++) {
            xx[kk][j] = x[kk] * xx[kk][j - 1];
        }

        times++;
    }
}
