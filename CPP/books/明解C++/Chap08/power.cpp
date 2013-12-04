// 傳回次方運算之值的函數

//--- 傳回x的n方  ---//
double power(double x, int n)
{
	double tmp = 1.0;

	while (n-- > 0)
		tmp *= x;	// 將tmp乘以x
	return tmp;
}


