#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED
#include<iostream>
#include<vector>
#include<string>
class BigInteger {
private:
    std::vector<int> bigInteger;  /* 保存大整数字串    */
    size_t length;                /* 表示大整数长度    */
    int signum;                   /* 表示大整数正负 -1为负数 0表示数字0 1表示正数 */
public:
    // 构造函数
    BigInteger();                       /* 空无参构造函数      */
    BigInteger(const BigInteger &);     /* 拷贝构造函数       */
    BigInteger(const std::string &);    /* 字符串构造大整数   */
    // 成员函数
    friend std::ostream& operator<<(std::ostream&, BigInteger &);
    friend std::istream& operator>>(std::istream&, BigInteger &);
    void setLength(const int&);
    void setSignum(const int&);
    int getLength();
    int getSignum();
    bool operator==(const BigInteger &);
    bool operator>(const BigInteger &);
    void operator=(const BigInteger &);
    BigInteger operator+(const BigInteger &);
    BigInteger operator-(const BigInteger&);
    BigInteger operator*(const BigInteger &);
    BigInteger operator/(const BigInteger &);
    BigInteger operator%(const BigInteger &);
    long long operator%(const long long &);
};
#endif // BIGINTEGER_H_INCLUDED
