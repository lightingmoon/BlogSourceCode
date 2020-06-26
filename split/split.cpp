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
    // c_str()���ص�ǰstring�����c ������ַ���,��const char *
    const char *del=deli.c_str();

    // ��str���·������У�����char�����ȡ
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
    // ֱ�Ӵ����ַ���
    std::string p=str;
    p+=deli;                                // ��֤��β��һ�������
    size_t cur;                             // ��¼��������Ӵ�
    while((cur = p.find(deli)) != std::string ::npos)
    {
        out.emplace_back(p.substr(0,cur));  // ��ȡ�ָ��Ӵ�

        p=p.substr(cur+deli.size());        // ��󻬶�
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

    // ���춨�������
    std::regex re(deli);

    // ��ȡƥ��ö�����Ĵ���ǰ׺
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
    // ����1
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

    // ����2
    cin>>str>>deli;
    spl = split2(str,deli);
    cout<<"[ ";
    for(auto str:spl)
    {
        cout<<str<<' ';
    }
    cout<<']'<<endl;
    spl.clear();

    // ����3
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
