/************************************************************************/
/*问题描述:                                                          ****/
/*用遗传算法求解函数 f(x)=x*sin(10л+x)+1.0 在区间[-1，2]             ****/
/*的最大值.                                                          ****/
/*author: lightdm													 ****/
/*date: 20190101                                                     ****/
/************************************************************************/
#include<iostream>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<unordered_set>
#include<numeric>

// 命名空间
using std::cin;
using std::cout;
using std::endl;

const double PI = 3.1415927;             	// π
#define N 50 							 	// 群体规模
#define T 500                       		// 进化代数
#define PC  0.75                  			// 参加交配概率
#define PM 0.0875                			// 变异概率
std::vector<double> group(N, 0);            // 种群
std::vector<double> adaptValue(N, 0);       		// 种群个体对应适应值
std::vector<double> Prob(N, 0);             		// 个体选中概率

std::pair<int, double> nowBest;          	// 记录当前当前代数最优个体、记录当前代数最优个体适应值

#define f(x) ((x)*sin(10*PI+(x))+1.0)    // 选择评估函数

// 选择算子-轮盘赌，获取一个[x,y]的随机数
double getRand(int x, int y)
{
	return (((rand() % (100 * y)) + 1) + x) * 0.01;
}

// 计算当前种群适应值
std::pair<size_t, double> calcAdaptValue()
{
	double maxEvaluate = -1.0;          // 最优适应值
	size_t index = -1;                  // 最优个体
	for(int i = 0; i < N; i++)
	{
		adaptValue[i] = f(group[i]);
		if(adaptValue[i] > maxEvaluate)
		{
			index = i;
			maxEvaluate = adaptValue[i];
		}
	}
	return std::make_pair(index, maxEvaluate); // 返回最优个体及适应值
}

// 初始化函数
void init()
{
	// 初始化初代种群
	for(size_t i = 0; i < N; i++)
	{
		group[i] = (((rand() % (300 + 1))) * 0.01) - 1;    // 产生[-1,2]之间的随机数
	}
}

// 选中概率
void calcPSelection(double &total)
{
	for(int i = 0; i < N; i++)
	{
		Prob[i] = adaptValue.at(i) / total;
	}
}
// 轮盘赌选择个体
int select()
{
	double r, s = 0;
	int i;
	r = getRand(0, 1);
	for(i = 0; i < N; i++)
	{
		s += Prob.at(i);
		if(r <= s)
		{
			break;
		}
	}
	return i;
}
// 轮盘赌
void roulette()
{
	int sel;
	std::vector<double> temp;
	for(int i = 0; i < N; i++)
	{
		sel = select();
		temp.push_back(group[sel]);
	}
	group.assign(temp.begin(), temp.end());
}
// 交叉配对产生子代个体
void mating()
{
	std::unordered_set<int> join;		// 判重复
	double p = 0;
	for(int i = 0; i < N; i++) 			// 选择参与交配的个体
	{
		p = getRand(0, 1);
		if(p > PC)
		{
			join.insert(i);
		}
	}
	if(join.size() & 1)     			// 选出的个体为奇数，则再选择一次，凑成偶数。
	{
		size_t r = rand() % N;
		while(join.count(r))
		{
			r = rand() % N;
		}
		join.insert(r);
	}
	// 进行算数交叉， 模拟交配过程
	std::vector<int> temp;
	for(auto it = join.begin(); it != join.end(); it++)
	{
		temp.push_back(*it);
	}
	for(int i = 0; i < temp.size() - 1; i += 2)
	{
		auto t1 = temp.at(i);
		auto t2 = temp.at(i + 1);
		double Lambda = getRand(0, 1);
		group[t1] = Lambda * group[t1] + (1 - Lambda) * group[t2];
		group[t2] = (1 - Lambda) * group[t1] + Lambda * group[t2];
	}
}
void variation()					// 变异过程
{
	for(int i = 0; i < N; i++)
	{
		auto p = getRand(0, 1);
		if(p < PM)					// 小于变异概率则进行变异
		{
			group[i] += getRand(0, 1);
		}
	}
}
int main()
{

	srand((int)time(0));

	// 初始化
	init();
	nowBest = calcAdaptValue();
	int t = 0;
	while(t < T)
	{

		// 求总体适应值
		double totalAdaptValue = std::accumulate(adaptValue.begin(), adaptValue.end(), 0.0);
		calcPSelection(totalAdaptValue);
		// 选择
		roulette();     		// 轮盘赌

		// 交叉配对
		mating();

		// 变异
		variation();

		// 计算种群个体适应度
		nowBest = calcAdaptValue();

		// 繁衍代数+1
		t++;

		//cout << nowBest.first << "--" << nowBest.second << endl;
	}
	cout << "得到最优解为: " << endl;
	cout << nowBest.second << endl;
	return 0;
}









