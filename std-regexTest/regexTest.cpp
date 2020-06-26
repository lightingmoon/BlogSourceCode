#include<iostream>
#include<string>
#include<regex>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    // regex_match()


    /*              regex_match
     std::string s("122  622");
    std::regex e("(\\d+)(\\s+)(\\d+)");		// ���߸�����һ�����֣��м�����һ���ո�
    // �Ƿ�ȫ��ƥ��ɹ�
    if (std::regex_match (s,e))
    {
        cout << "the match is successful!";
    }
    else
    {
        cout<<"the match is failed!"<<endl;
    }
    // ����ƥ������
    //std::match_results<const char *> cm;
    std::cmatch cm;             // ͬ��std::match_results<const char *>
    std::regex_match (s.c_str(),cm,e);
    cout << "string literal with " << cm.size() << " matches\n";
    for(auto y:cm)
        cout<<"["<<y<<"]"<<endl;
    */


    //  regex_search()


    /*
    std::string s("sss666  333ff");
    std::regex e("(\\d+)(\\s+)(\\d+)");
    // �Ƿ�����ƥ��ɹ�
    if (std::regex_search(s,e))
    {
        cout<<"the match is successful!"<<endl;
        // ����ƥ��������
        std::cmatch cm;             // ͬ��std::match_results<const char *>
        std::regex_search(s.c_str(),cm,e);
        for(auto y:cm)
            cout<<"["<<y<<"]"<<endl;
        }
    else
    {
        cout<<"the match is failed!"<<endl;
    }
    */

    //       regex_replace()

    /*
    // Flags used to control how rgx is matched and how fmt is formatted.
    std::regex_constants::match_flag_type fonly =
        std::regex_constants::format_first_only;
    std::string s("  sss666  333ffF  d32132  ");
    // ��һ�������ϵĿո�ʼ����������1~3�����ֻ���ĸ�����
    std::regex rgx("(\\s+[a-z0-9]{1,3})");
    std::string fmt="";
    cout<<"flags: "<<std::regex_replace(s,rgx,fmt,fonly)<<endl;
    cout<<"default: "<<std::regex_replace(s,rgx,fmt)<<endl;
    */
    std::string s="31234a,333sss,3435ss.dwa";

    // ƥ����������ſ�ʼ����������һ�������ϵ�������2��������Сд��ĸ�����
    std::regex rgx("(\\d+)");

    // std::sregex_iterator == std::regex_iterator<std::string::const_iterator>
    std::regex_iterator<std::string::const_iterator> cbegin(s.begin(),s.end(),rgx);
    std::sregex_iterator cend;
    while(cbegin != cend)
    {
        cout<<cbegin->str()<<endl;
        ++cbegin;
    }
    return 0;
}
