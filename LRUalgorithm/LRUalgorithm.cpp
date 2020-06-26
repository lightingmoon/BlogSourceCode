#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#define CAPACITY 3

typedef struct page
{
	int pageNum = -1;    // 系统访问页码
	int time = 0;       // 系统在内存访问总次数
	page() {}                                       // 空无参构造
	page(const int p): pageNum(p) {}                // 构造函数
	friend bool operator<(page &p1, page &p2)       // 排序比较器
	{
		return p1.time < p2.time;
	}
}pageNode;
void foldPage(int page, std::vector<pageNode> &mainMem)
{
	if(CAPACITY == mainMem.size())                  // 内存存放的页满
	{
		mainMem.back().pageNum = page;
		mainMem.back().time = 0;
	}
	else
	{
		mainMem.emplace_back(page);                 // emplace_back()直接调用其构造函数，并加在vector最后。
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
	// pageDirection[]表示页的走向，pageNum 为数组 pageDirection[]中元素个数
	int pageDirection[] = {4, 3, 2, 1, 4, 3, 5, 4, 3, 2, 1, 5, 1, 4, 3}, pageNum = 15;
	std::vector<pageNode> mainMem;                 // 模拟内存，最大页数为3
	int RequstCount = 0, Requst = 0; 			   // RequstCount 表示中断次数，Requst 为缺页标志

	std::cout << "时间  访问页   内存状态  缺页中断 调入页" << std::endl;
	std::cout.setf(std::ios::left);
	for(int i = 0; i < pageNum; i++)
	{
		std::cout << std::setw(8) << i + 1;
		std::cout << std::setw(8) << pageDirection[i];
		Requst = 0;
		if( true == isMissing(mainMem, pageDirection[i]))       //检查是否缺页
		{
			foldPage(pageDirection[i], mainMem);                //进行页置换
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
		for(int i = CAPACITY - mainMem.size(); i >= 0; i--)     // 格式化空白
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
	std::cout << "缺页中断次数为" << RequstCount << std::endl;
	std::cout.setf(std::ios::fixed);                            // 定点小数
	std::cout << std::setprecision(2) << "缺页率" << RequstCount << "/" << pageNum << "=" << (float)RequstCount / pageNum * 100 << "%%";
	return 0;
}
