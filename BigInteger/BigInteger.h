#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED
#include<iostream>
#include<vector>
#include<string>
class BigInteger {
private:
    std::vector<int> bigInteger;  /* ����������ִ�    */
    size_t length;                /* ��ʾ����������    */
    int signum;                   /* ��ʾ���������� -1Ϊ���� 0��ʾ����0 1��ʾ���� */
public:
    // ���캯��
    BigInteger();                       /* ���޲ι��캯��      */
    BigInteger(const BigInteger &);     /* �������캯��       */
    BigInteger(const std::string &);    /* �ַ������������   */
    // ��Ա����
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
