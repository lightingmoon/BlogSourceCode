/************************************************************************/
/*问题描述:                                                          ****/
/* 算法笔记 p134      						 ****/
/*     								     ****/
/*author: @ldm						             ****/
/*date: 20190213                                                     ****/
/************************************************************************/
#include<bits/stdc++.h>
#define DEBUG 0
using namespace std;
typedef long long LL;

class Solution
{
public:
	array<double, 100003> s;
	double getRadian1(int n, double r)
	{
		double radian = 0.0;
		for(int i = 0; i < n; i++)
		{
			radian += acos(s.at(i) / 2 / r) * 2;    // 解三角形
		}
		return radian;
	}
	void entry1()
	{
		int n;
		double eps = 1e-5, PI = acos(-1.0);
		while(cin >> n)
		{
			double maxL = -1.0;
			for(int i = 0; i < n; i++)
			{
				cin >> s[i];
				maxL = max(s[i], maxL);
			}
			double nowRadian = getRadian1(n, maxL / 2);  // 最大边为外接圆直径
			cout.setf(ios::fixed);
			if(abs(nowRadian - PI * (n - 2)) < eps)
			{
				cout << setprecision(2) << "the max Radius is " << maxL / 2 << endl;
				continue;
			}
			double l = 0.0, r = 10000000, mid;    // 最大半径小于四边形周长
			while(r - l > eps)
			{
				mid = (l + r) / 2;
				nowRadian = getRadian1(n, mid);
				if(nowRadian > PI * (n - 2))
					r = mid;
				else
					l = mid;
			}
			cout << setprecision(2) << "the max Radius is " << mid << endl;
		}
	}
	double getRadian2(int n, double r)
	{
		double radian = 0.0;
		for(int i = 0; i < n; i++)
		{
			radian += asin(s.at(i) / 2 / r) * 2;    // 解三角形
		}
		return radian;
	}
	void entry2()
	{
		int n;
		double eps = 1e-5, SPI = 2 * acos(-1.0);
		while(cin >> n)
		{
			double maxL = -1.0;
			for(int i = 0; i < n; i++)
			{
				cin >> s[i];
				maxL = max(s[i], maxL);
			}
			cout.setf(ios::fixed);
			// 最大边为外接圆直径
			if(abs(getRadian2(n, maxL / 2) - SPI) < eps)
			{
				cout << setprecision(3) << "the max Radius is " << maxL / 2 << endl;
				continue;
			}
			double l = 0.0, r = 10000000, mid;    // 最大半径小于四边形周长
			while(r - l > eps)
			{
				mid = (l + r) / 2;
				// 圆心角不够2π，r过大
				if(getRadian2(n, mid) < SPI)
					r = mid;
				else
					l = mid;
			}
			cout << setprecision(3) << "the max Radius is " << mid << endl;
		}
	}
};
int main()
{
#if DEBUG
	freopen("E:\\in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(0);
	Solution S;
	S.entry2();
	return 0;
}
