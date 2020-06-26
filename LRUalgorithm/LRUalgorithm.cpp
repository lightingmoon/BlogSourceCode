#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#define CAPACITY 3

typedef struct page
{
	int pageNum = -1;    // ϵͳ����ҳ��
	int time = 0;       // ϵͳ���ڴ�����ܴ���
	page() {}                                       // ���޲ι���
	page(const int p): pageNum(p) {}                // ���캯��
	friend bool operator<(page &p1, page &p2)       // ����Ƚ���
	{
		return p1.time < p2.time;
	}
}pageNode;
void foldPage(int page, std::vector<pageNode> &mainMem)
{
	if(CAPACITY == mainMem.size())                  // �ڴ��ŵ�ҳ��
	{
		mainMem.back().pageNum = page;
		mainMem.back().time = 0;
	}
	else
	{
		mainMem.emplace_back(page);                 // emplace_back()ֱ�ӵ����乹�캯����������vector���
	}
}
bool isMissing(std::vector<pageNode> &mainMem, int page)
{
	for(auto e : mainMem)
	{
		if(e.pageNum == page)
		{
			return false;
		}
	}
	return true;
}
int main()
{
	// pageDirection[]��ʾҳ������pageNum Ϊ���� pageDirection[]��Ԫ�ظ���
	int pageDirection[] = {4, 3, 2, 1, 4, 3, 5, 4, 3, 2, 1, 5, 1, 4, 3}, pageNum = 15;
	std::vector<pageNode> mainMem;                 // ģ���ڴ棬���ҳ��Ϊ3
	int RequstCount = 0, Requst = 0; 			   // RequstCount ��ʾ�жϴ�����Requst Ϊȱҳ��־

	std::cout << "ʱ��  ����ҳ   �ڴ�״̬  ȱҳ�ж� ����ҳ" << std::endl;
	std::cout.setf(std::ios::left);
	for(int i = 0; i < pageNum; i++)
	{
		std::cout << std::setw(8) << i + 1;
		std::cout << std::setw(8) << pageDirection[i];
		Requst = 0;
		if( true == isMissing(mainMem, pageDirection[i]))       //����Ƿ�ȱҳ
		{
			foldPage(pageDirection[i], mainMem);                //����ҳ�û�
			RequstCount++;
			Requst = 1;
		}
		else
		{
			for(auto e : mainMem)
			{
				if(e.pageNum == pageDirection[i])
				{
					e.time++;
				}
			}
			std::sort(mainMem.begin(), mainMem.end());
		}
		for(auto e : mainMem)
		{
			std::cout << " " << e.pageNum;
		}
		for(int i = CAPACITY - mainMem.size(); i >= 0; i--)     // ��ʽ���հ�
		{
			std::cout << "  ";
		}
		if(Requst == 1)
		{
			std::cout << "     +      ";
			std::cout << pageDirection[i];
		}
		std::cout << std::endl;
	}
	std::cout << "ȱҳ�жϴ���Ϊ" << RequstCount << std::endl;
	std::cout.setf(std::ios::fixed);                            // ����С��
	std::cout << std::setprecision(2) << "ȱҳ��" << RequstCount << "/" << pageNum << "=" << (float)RequstCount / pageNum * 100 << "%%";
	return 0;
}
