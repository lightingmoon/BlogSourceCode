#include "BigInteger.h"
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cassert>
#include<algorithm>
#include<cstdio>
using namespace std;
const int LIMIT = 4;
const int CARRY = 1e4;
/* vectorÿ��Ԫ�ش��������λ������Ϊvector<int>ÿ��Ԫ�ض���һ����ΧΪ
 -2^31 ��2^31 - 1��������λ��Ϊ9λ�����ǵ�����4λ�����,Ҳֻ��8λ���ʲ������int������ѡ��洢4λ��
*/
BigInteger::BigInteger() {}
BigInteger::BigInteger(const std::string &tmp)
{
    string T(tmp);
    assert(T.size() != 0);
    if(T.at(0) == '-') {        // ȥ����
        this->signum = -1;
        T = T.substr(1);
    } else if(T.at(0) == '0') {
        assert(T.length() == 1);
        this->signum = 0;
    } else {
        this->signum = 1;
    }
    int len = T.size();
    this->length = len;

    for(int i = len - 1; i >= 0; i -= LIMIT) {
        int k = 0, r = i - LIMIT + 1 < 0 ? (0) : i - LIMIT + 1;
        for(int j = r; j <= i; j++) {
            k = k * 10 + T.at(j) - '0';
        }
        this->bigInteger.push_back(k);
    }
    this->bigInteger.shrink_to_fit();
}
BigInteger::BigInteger(const BigInteger &tmp)
{
    this->length = tmp.length;
    this->signum = tmp.signum;
    this->bigInteger = tmp.bigInteger;
}
int BigInteger::getLength()
{
    return this->length;
}
void BigInteger::setLength(const int &t)
{
    this->length = t;
}
int BigInteger::getSignum()
{
    return this->signum;
}
void BigInteger::setSignum(const int &t)
{
    this->signum = t;
}
//////////////////////////////////////////////////////////////////////// ���رȽϡ���ֵ�����롢������Թ��������
bool BigInteger::operator==(const BigInteger &tmp)
{
    BigInteger q = *this, t = tmp;
    if(q.signum != t.signum) return false;
    if(q.length != t.length) return false;
    bool flag = true;
    for(int i = q.bigInteger.size() - 1; i >= 0; i--) {
        if((unsigned int)i >= tmp.bigInteger.size()) continue;
        if(q.bigInteger.at(i) != t.bigInteger.at(i)) {
            flag = false;
            break;
        }
    }
    if(flag) return true;
    else return false;
}
bool BigInteger::operator>(const BigInteger &tmp)
{
    if(this->signum > 0 && tmp.signum <= 0 ) return true;
    else if(this->signum == 0 && tmp.signum < 0) return true;
    else if(this->length > tmp.length) return true;
    else if(this->length < tmp.length) return false;
    else if(this->length == tmp.length){
        bool flag = false;
        for(int i = this->bigInteger.size() - 1; i >= 0; i--) {
            if(this->bigInteger[i] > tmp.bigInteger[i]) {
                flag = true;
                break;
            }
        }
        if(flag) return true;
        else return false;
    }
    return false;
}
void BigInteger::operator=(const BigInteger &tmp)
{
    this->length = tmp.length;
    this->signum = tmp.signum;
    this->bigInteger = tmp.bigInteger;
}
ostream& operator<<(ostream &out, BigInteger &s)
{
    size_t siz = s.bigInteger.size();
    assert(siz != 0);
    if(s.signum == 0)   cout << '0';
    else {

        if(s.signum == -1) cout << '-';         // �ж��Ƿ�Ϊ����
        cout << s.bigInteger.at(siz - 1);      // ��λ������λ���ò�0
        for(int i = siz - 2; i >= 0; i--) {
            cout.width(LIMIT);
            cout.fill('0');
            cout << s.bigInteger.at(i);
        }
    }
    return out;
}
istream& operator>>(istream &in, BigInteger &s)
{
    cout << "constructing..." << endl;
    s.bigInteger.clear();
    string T;
    getline(in, T);
    assert(T.length() != 0);
    if(T.at(0) == '-') {        // ȥ����
        s.signum = -1;
        T = T.substr(1);
    } else if(T.at(0) == '0') {
        assert(T.length() == 1);
        s.signum = 0;
    } else {
        s.signum = 1;
    }
    int len = T.size();
    s.length = len ;
    for(int i = len - 1; i >= 0; i -= LIMIT) {
        int k = 0, r = i - LIMIT + 1 < 0 ? (0) : i - LIMIT + 1;
        for(int j = r; j <= i; j++) {
            k = k * 10 + T.at(j) - '0';
        }
        s.bigInteger.push_back(k);
    }
    s.bigInteger.shrink_to_fit();
    return in;
}
/////////////////////////////////////////////////////////////////////////
BigInteger BigInteger::operator+(const BigInteger &tmp)
{
    BigInteger t = *this, q = tmp;
    size_t len1, len2;
    if(t > q)  swap(t, q);                          /*ǰ�������� > �� == �����,ѡ��λ����ļ�λ*/
    len1 = t.bigInteger.size();                     /* ���ٵģ��ٸ����������ԣ���Ϊ����ֵ��*/
    len2 = q.bigInteger.size();
    bool flag = false;
    for(size_t i = 0; i < len2; i++) {
        if(i < len1)                                /* ��ֹԽ��            */
            q.bigInteger[i] += t.bigInteger[i];
        if(q.bigInteger[i] >= CARRY) {
            if(i == len2 - 1) {                      /* ���λ��λ����λ�� */
                q.bigInteger.push_back(1);           /*��1                 */
                q.bigInteger[i] -= CARRY;
                flag = true;
            } else {                                /* ��λ��λ          */
                q.bigInteger[i + 1]++;
                q.bigInteger[i] -= CARRY;           /*���±�λ��ֵ           */
            }
        }
    }
    if(flag) q.length++;                            /* ���λ�н�λ       */
    return q;
}
BigInteger BigInteger::operator-(const BigInteger &tmp)
{
    BigInteger q = *this, t = tmp;
    size_t len1, len2;
    if(q == t) {                                    /*���������ֱ�ӷ���0*/
        BigInteger r("0");
        return r;
    }
    if(q > t) {
        len1 = q.bigInteger.size();
        len2 = t.bigInteger.size();
        for(size_t i = 0; i < len1; i++) {
            if(i < len2)                            /*��ֹԽ��          */
                q.bigInteger[i] -= t.bigInteger[i];
            if(q.bigInteger[i] < 0) {               /* ��λ�����Ľ��С��0�����λ��λ */
                q.bigInteger[i + 1]--;
                q.bigInteger[i] += CARRY;           /*  ���±�λ        */
            }
        }
        // ��λȥ0
        for(int i = len1 - 1; i >= 0; i--) {        /* ��Ϊq�����λ ֻ�ܴ��ڵ���t�����λ��         */
            if(q.bigInteger[i] == 0) {              /* ���������λ���ʱ,��ʱ���λΪ0���ô��㷨    */
                q.length -= LIMIT;                  /* �Ѹ�λ��0ȥ��                                 */
                q.bigInteger.pop_back();
            } else break;                           /* �����λ��ʼɨ�裬������һ����Ϊ0����������   */
        }
        // ���´����ĳ���
        q.length = (q.bigInteger.size() - 1) * LIMIT;   /* ���¼������λ��λ��                   */
        int k = q.bigInteger.back();
        while(k) {                                  /*  ����λ��        */
            k /= 10;
            q.length++;
        }
        return q;
    } else {
        len1 = t.bigInteger.size();
        len2 = q.bigInteger.size();
        for(size_t i = 0; i < len1; i++) {
            if(i < len2)
                t.bigInteger[i] -= q.bigInteger[i];
            if(t.bigInteger[i] < 0) {
                t.bigInteger[i + 1]--;
                t.bigInteger[i] += CARRY;
            }
        }
        // ��������
        t.signum = -1;                              /*  �������������Ϊ����*/
        // ��λȥ0
        for(int i = len1 - 1; i >= 0; i--) {
            if(t.bigInteger[i] == 0) {
                t.length -= LIMIT;
                t.bigInteger.pop_back();
            } else break;
        }
        // ����λ��
        if(t.bigInteger.size() == 1)
            t.length = 0;
        else
            t.length = (t.bigInteger.size() - 1) * LIMIT;
        int k = t.bigInteger.back();
        while(k) {
            k /= 10;
            t.length++;
        }
        return t;
    }
}
BigInteger BigInteger::operator*(const BigInteger &tmp)
{
    BigInteger t = *this, q = tmp, r;
    int carry;
    size_t i, j;
    size_t len1 = t.bigInteger.size(), len2 = q.bigInteger.size();
    vector<int> T(len1 + len2, 0);
    for(i = 0; i < len1; i++) {
        carry = 0;
        for(j = 0; j < len2; j++) {
            int temp = t.bigInteger[i] * q.bigInteger[j] + T[i + j] + carry;  /* �����iλ���jλ�ĳ˻������ϱ�λ���λֵ*/
            if(temp >= CARRY) {
                carry = temp / CARRY;                                         /* �����λֵ */
                T[i + j] = temp % CARRY;                                      /* ���±�λֵ */
            } else {
                carry = 0;
                T[i + j] = temp;
            }
        }
        if(carry != 0) T[i + j] = carry;                                      /* ���λ��λ */
    }
    // �������
    if(t.signum < 0 && q.signum < 0)
        r.signum = 1;
    else {
        if(t.signum < 0 || q.signum < 0)
            q.signum = -1;
        else if(t.signum == 0 || q.signum == 0) {
            r.signum = 0;
        } else {
            r.signum = 1;
        }
    }
    // ������
    if(r.signum != 0) {                         /* ���жϽ���ķ��� */
        //  ��λȥ0
        for(int i = T.size() - 1; i >= 0; i--) {
            if(T[i] == 0) {
                T.pop_back();
            } else {
                break;
            }
        }
        // ���ִ�����
        r.length = (T.size() - 1) * LIMIT;
        int k = T.back();
        while(k) {
            k /= 10;
            r.length++;
        }
        r.bigInteger = T;
    } else {
        r.length = 1;
        T.resize(1);
        r.bigInteger = T;
    }
    return r;
}
BigInteger BigInteger::operator/(const BigInteger &tmp)     // ��������㷨��Ч���Ͽ����в���
{
    BigInteger q = *this , t = tmp, ans, ZERO("0");
    assert(!(t == ZERO));                       /* ������Ϊ0                */
    if(q == ZERO) return ZERO;                  /* ������Ϊ0����0           */
    if(q == t) {                                /* ���������ֱ�ӷ���1      */
        ans.signum = 1;
        ans.length = 1;
        ans.bigInteger.push_back(1);
    } else {
        if(q > t) {                             /* ���������ڳ�������ʼ���� */
            vector<int> T(250, 0);
            int index = 0, maxl = 0;
            while(true) {
                q = q - t;
                if(ZERO > q) {
                    if(!(ZERO == q)) break;     /* ֱ������qС���㣬����������ʱ��Ҫ���̼�1 */
                }
                T[index]++;
                if(T[index] >= CARRY) {         /*�ж���λ              */
                    T[index] = 0;
                    T[++index]++;
                    maxl = max(maxl, index);
                    for(int i = index; i < maxl; i++) {
                        if(T[i] >= CARRY) {
                            T[i + 1]++;
                            T[i] = 0;
                        }
                    }
                    index = 0;                  /* �ػ����λ�ۼ�      */
                }
            }
            T.resize(maxl + 1);
            if(q.signum < 0 && t.signum < 0)
                q.signum = 1;
            else {
                if(q.signum < 0 || t.signum < 0)
                    q.signum = -1;
                else {
                    q.signum = 1;
                }
            }
            ans.bigInteger = T;
        } else {
            ans = ZERO;
        }
    }
    return ans;
}
BigInteger BigInteger::operator%(const BigInteger &tmp)
{
    BigInteger q = *this, t = tmp, ZERO("0"), m;
    assert(!(q == ZERO));
    assert(!(t == ZERO));
    m = q / t;
    return q - (m * t);

}
long long BigInteger::operator%(const long long &tmp)
{
    BigInteger q = *this;
    long long mod = 0, len = q.bigInteger.size();
    for(int i = len - 1; i >= 0; i--) {
        mod = ((mod * CARRY) % tmp + q.bigInteger[i]) % tmp;
    }
    return mod;
}
int main()
{
    const int IntegerMod=1234567890;
    BigInteger p, q, t;
    cout << "��ʼ����" << endl;
    cin>>p;
    cin>>q;
    t = p - q;
    cout << "p - q = " << t << endl;
    t = p + q;
    cout << "p + q = " << t << endl;
    t = p * q;
    cout << "p * q = " << t << endl;
    t = p / q;
    cout <<left<< "p / q = " << t << endl;
    t = p % q;
    cout << "p % q = " << t << endl;
    cout<< "p % " <<IntegerMod <<" = "<<p%IntegerMod <<endl;
    cout<<"��������"<<endl;
    return 0;
}
