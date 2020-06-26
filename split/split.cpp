#include<iostream>
#include<cstring>
#include<string>
#include<regex>
#include<vector>
#include<sstream>
#include<cstdio>
using std::cin;
using std::cout;
using std::endl;

// strtok
std::vector<std::string> split0(const std::string str, const std::string deli)
{
    std::vector<std::string> out;
    if(str.empty())
    {
        return out;
    }
    if(deli.empty())
    {
        out.emplace_back(str);
        return out;
    }
    // c_str()返回当前string对象的c 风格常量字符串,即const char *
    const char *del=deli.c_str();

    // 将str重新放入流中，再用char数组读取
    std::stringstream ot(str);
    char strTemp[str.size()+1];
    ot>>strTemp;
    char *p=strtok(strTemp,del);
    while(p != nullptr)
    {
        out.push_back(p);
        p = strtok(nullptr,del);
    }
    return out;
}
std::vector<std::string> split1(const std::string str, const std::string deli)
{
    std::vector<std::string> out;
    if(str.empty())
    {
        return out;
    }
    if(deli.empty())
    {
        out.emplace_back(str);
        return out;
    }
    // 直接处理字符串
    std::string p=str;
    p+=deli;                                // 保证结尾有一个定界符
    size_t cur;                             // 记录处理过的子串
    while((cur = p.find(deli)) != std::string ::npos)
    {
        out.emplace_back(p.substr(0,cur));  // 截取分割子串

        p=p.substr(cur+deli.size());        // 向后滑动
    }
    return out;
}
std::vector<std::string> split2(const std::string str, const std::string deli)
{
    std::vector<std::string> out;
    if(str.empty())
    {
        return out;
    }
    if(deli.empty())
    {
        out.emplace_back(str);
        return out;
    }

    // 构造定界符正则
    std::regex re(deli);

    // 获取匹配该定界符的串的前缀
    std::sregex_token_iterator p(str.begin(), str.end(), re, -1);
    std::sregex_token_iterator end;

    while (p != end)
    {
        out.emplace_back(*p++);
    }
    return out;
}
int main()
{
    freopen("E:\\in.txt","r",stdin);
    std::vector<std::string> spl;
    // 测试1
    std::string str;
    std::string deli;
    cin>>str>>deli;
    spl = split2(str,deli);
    cout<<"[ ";
    for(auto str:spl)
    {
        cout<<str<<' ';
    }
    cout<<']'<<endl;
    spl.clear();

    // 测试2
    cin>>str>>deli;
    spl = split2(str,deli);
    cout<<"[ ";
    for(auto str:spl)
    {
        cout<<str<<' ';
    }
    cout<<']'<<endl;
    spl.clear();

    // 测试3
    cin>>str>>deli;
    spl = split2(str,deli);
    cout<<"[ ";
    for(auto str:spl)
    {
        cout<<str<<' ';
    }
    cout<<']'<<endl;
    spl.clear();
    return 0;
}
