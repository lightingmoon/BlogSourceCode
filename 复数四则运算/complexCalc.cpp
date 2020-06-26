#include<bits/stdc++.h>
using namespace std;
typedef long int LL;
void printExp(double a, double b)
{
	if(abs(a) < 0.05 && abs(b) < 0.05)
	{
		printf("0.0");
	}
	else
	{
		// 实部
		if(abs(a) >= 0.05)
		{
			printf("%.1lf", a);
		}
		// 虚部
		if(abs(b) >= 0.05)
		{
			// 虚部的 + 符号
			if(b > 0 && abs(a) >= 0.05)
				printf("+");
			printf("%.1lfi", b);
		}
	}
}
void printExpTotal(double a1, double b1, double a2, double b2, char x)
{
	printf("(%.1lf", a1);
	if(b1 >= 0)
		printf("+");
	printf("%.1lfi)", b1);
	printf(" %c ", x);
	printf("(%.1lf", a2);
	if(b2 >= 0)
		printf("+");
	printf("%.1lfi)", b2);
	printf(" = ");
}
int main()
{
	double a1, b1, a2, b2;
	double a, b;
	scanf("%lf%lf%lf%lf", &a1, &b1, &a2, &b2);
	printExpTotal(a1, b1, a2, b2, '+');
	a = a1 + a2 ;
	b = b1 + b2;
	printExp(a, b);
	printf("\n");
	printExpTotal(a1, b1, a2, b2, '-');
	a = a1 - a2 ;
	b = b1 - b2 ;
	printExp(a, b);
	printf("\n");
	printExpTotal(a1, b1, a2, b2, '*');
	a = (a1 * a2) - (b1 * b2 );
	b = (a1 * b2) + (b1 * a2 );
	printExp(a, b);
	printf("\n");
	printExpTotal(a1, b1, a2, b2, '/');
	a = (a1 * a2 + b1 * b2) / (a2 * a2 + b2 * b2);
	b = (b1 * a2 - a1 * b2) / (a2 * a2 + b2 * b2);
	printExp(a, b);
	return 0;
}
