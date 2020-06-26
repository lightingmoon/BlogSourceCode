/************************************************************************/
/*��������:                                                          ****/
/*���Ŵ��㷨��⺯�� f(x)=x*sin(10��+x)+1.0 ������[-1��2]             ****/
/*�����ֵ.                                                          ****/
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

// �����ռ�
using std::cin;
using std::cout;
using std::endl;

const double PI = 3.1415927;             	// ��
#define N 50 							 	// Ⱥ���ģ
#define T 500                       		// ��������
#define PC  0.75                  			// �μӽ������
#define PM 0.0875                			// �������
std::vector<double> group(N, 0);            // ��Ⱥ
std::vector<double> adaptValue(N, 0);       		// ��Ⱥ�����Ӧ��Ӧֵ
std::vector<double> Prob(N, 0);             		// ����ѡ�и���

std::pair<int, double> nowBest;          	// ��¼��ǰ��ǰ�������Ÿ��塢��¼��ǰ�������Ÿ�����Ӧֵ

#define f(x) ((x)*sin(10*PI+(x))+1.0)    // ѡ����������

// ѡ������-���̶ģ���ȡһ��[x,y]�������
double getRand(int x, int y)
{
	return (((rand() % (100 * y)) + 1) + x) * 0.01;
}

// ���㵱ǰ��Ⱥ��Ӧֵ
std::pair<size_t, double> calcAdaptValue()
{
	double maxEvaluate = -1.0;          // ������Ӧֵ
	size_t index = -1;                  // ���Ÿ���
	for(int i = 0; i < N; i++)
	{
		adaptValue[i] = f(group[i]);
		if(adaptValue[i] > maxEvaluate)
		{
			index = i;
			maxEvaluate = adaptValue[i];
		}
	}
	return std::make_pair(index, maxEvaluate); // �������Ÿ��弰��Ӧֵ
}

// ��ʼ������
void init()
{
	// ��ʼ��������Ⱥ
	for(size_t i = 0; i < N; i++)
	{
		group[i] = (((rand() % (300 + 1))) * 0.01) - 1;    // ����[-1,2]֮��������
	}
}

// ѡ�и���
void calcPSelection(double &total)
{
	for(int i = 0; i < N; i++)
	{
		Prob[i] = adaptValue.at(i) / total;
	}
}
// ���̶�ѡ�����
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
// ���̶�
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
// ������Բ����Ӵ�����
void mating()
{
	std::unordered_set<int> join;		// ���ظ�
	double p = 0;
	for(int i = 0; i < N; i++) 			// ѡ����뽻��ĸ���
	{
		p = getRand(0, 1);
		if(p > PC)
		{
			join.insert(i);
		}
	}
	if(join.size() & 1)     			// ѡ���ĸ���Ϊ����������ѡ��һ�Σ��ճ�ż����
	{
		size_t r = rand() % N;
		while(join.count(r))
		{
			r = rand() % N;
		}
		join.insert(r);
	}
	// �����������棬 ģ�⽻�����
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
void variation()					// �������
{
	for(int i = 0; i < N; i++)
	{
		auto p = getRand(0, 1);
		if(p < PM)					// С�ڱ����������б���
		{
			group[i] += getRand(0, 1);
		}
	}
}
int main()
{

	srand((int)time(0));

	// ��ʼ��
	init();
	nowBest = calcAdaptValue();
	int t = 0;
	while(t < T)
	{

		// ��������Ӧֵ
		double totalAdaptValue = std::accumulate(adaptValue.begin(), adaptValue.end(), 0.0);
		calcPSelection(totalAdaptValue);
		// ѡ��
		roulette();     		// ���̶�

		// �������
		mating();

		// ����
		variation();

		// ������Ⱥ������Ӧ��
		nowBest = calcAdaptValue();

		// ���ܴ���+1
		t++;

		//cout << nowBest.first << "--" << nowBest.second << endl;
	}
	cout << "�õ����Ž�Ϊ: " << endl;
	cout << nowBest.second << endl;
	return 0;
}









