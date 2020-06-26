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
    std::regex e("(\\d+)(\\s+)(\\d+)");		// 两边各最少一个数字，中间至少一个空格
    // 是否全词匹配成功
    if (std::regex_match (s,e))
    {
        cout << "the match is successful!";
    }
    else
    {
        cout<<"the match is failed!"<<endl;
    }
    // 捕获匹配内容
    //std::match_results<const char *> cm;
    std::cmatch cm;             // 同于std::match_results<const char *>
    std::regex_match (s.c_str(),cm,e);
    cout << "string literal with " << cm.size() << " matches\n";
    for(auto y:cm)
        cout<<"["<<y<<"]"<<endl;
    */


    //  regex_search()


    /*
    std::string s("sss666  333ff");
    std::regex e("(\\d+)(\\s+)(\\d+)");
    // 是否搜索匹配成功
    if (std::regex_search(s,e))
    {
        cout<<"the match is successful!"<<endl;
        // 捕获匹配内容组
        std::cmatch cm;             // 同于std::match_results<const char *>
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
    // 由一个及以上的空格开始，接下来是1~3个数字或字母的组合
    std::regex rgx("(\\s+[a-z0-9]{1,3})");
    std::string fmt="";
    cout<<"flags: "<<std::regex_replace(s,rgx,fmt,fonly)<<endl;
    cout<<"default: "<<std::regex_replace(s,rgx,fmt)<<endl;
    */
    std::string s="31234a,333sss,3435ss.dwa";

    // 匹配以任意符号开始，接下来是一个及以上的数字与2个及以上小写字母的组合
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
