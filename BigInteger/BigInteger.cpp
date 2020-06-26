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
/* vector每个元素存的整数的位数，因为vector<int>每个元素都存一个范围为
 -2^31 至2^31 - 1，最大的数位数为9位，考虑到最大的4位数相乘,也只有8位，故不会溢出int，所以选择存储4位数
*/
BigInteger::BigInteger() {}
BigInteger::BigInteger(const std::string &tmp)
{
    string T(tmp);
    assert(T.size() != 0);
    if(T.at(0) == '-') {        // 去符号
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
//////////////////////////////////////////////////////////////////////// 重载比较、赋值、输入、输出，以供后面调试
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

        if(s.signum == -1) cout << '-';         // 判断是否为负数
        cout << s.bigInteger.at(siz - 1);      // 首位不够四位不用补0
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
    if(T.at(0) == '-') {        // 去符号
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
    if(t > q)  swap(t, q);                          /*前面重载了 > 和 == 运算符,选择位数多的加位*/
    len1 = t.bigInteger.size();                     /* 数少的，再更新它的属性，作为返回值。*/
    len2 = q.bigInteger.size();
    bool flag = false;
    for(size_t i = 0; i < len2; i++) {
        if(i < len1)                                /* 防止越界            */
            q.bigInteger[i] += t.bigInteger[i];
        if(q.bigInteger[i] >= CARRY) {
            if(i == len2 - 1) {                      /* 最高位进位增加位数 */
                q.bigInteger.push_back(1);           /*进1                 */
                q.bigInteger[i] -= CARRY;
                flag = true;
            } else {                                /* 高位进位          */
                q.bigInteger[i + 1]++;
                q.bigInteger[i] -= CARRY;           /*更新本位的值           */
            }
        }
    }
    if(flag) q.length++;                            /* 最高位有进位       */
    return q;
}
BigInteger BigInteger::operator-(const BigInteger &tmp)
{
    BigInteger q = *this, t = tmp;
    size_t len1, len2;
    if(q == t) {                                    /*两数相等则直接返回0*/
        BigInteger r("0");
        return r;
    }
    if(q > t) {
        len1 = q.bigInteger.size();
        len2 = t.bigInteger.size();
        for(size_t i = 0; i < len1; i++) {
            if(i < len2)                            /*防止越界          */
                q.bigInteger[i] -= t.bigInteger[i];
            if(q.bigInteger[i] < 0) {               /* 本位所减的结果小于0则向高位借位 */
                q.bigInteger[i + 1]--;
                q.bigInteger[i] += CARRY;           /*  更新本位        */
            }
        }
        // 高位去0
        for(int i = len1 - 1; i >= 0; i--) {        /* 因为q的最高位 只能大于等于t的最高位，         */
            if(q.bigInteger[i] == 0) {              /* 当它们最高位相等时,此时最高位为0，用此算法    */
                q.length -= LIMIT;                  /* 把高位的0去掉                                 */
                q.bigInteger.pop_back();
            } else break;                           /* 从最高位开始扫描，遇到第一个不为0的数则跳出   */
        }
        // 更新大数的长度
        q.length = (q.bigInteger.size() - 1) * LIMIT;   /* 重新计算最高位的位数                   */
        int k = q.bigInteger.back();
        while(k) {                                  /*  计算位数        */
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
        // 大数符号
        t.signum = -1;                              /*  反过来减，结果为负数*/
        // 高位去0
        for(int i = len1 - 1; i >= 0; i--) {
            if(t.bigInteger[i] == 0) {
                t.length -= LIMIT;
                t.bigInteger.pop_back();
            } else break;
        }
        // 大数位数
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
            int temp = t.bigInteger[i] * q.bigInteger[j] + T[i + j] + carry;  /* 保存第i位与第j位的乘积并加上本位与进位值*/
            if(temp >= CARRY) {
                carry = temp / CARRY;                                         /* 保存进位值 */
                T[i + j] = temp % CARRY;                                      /* 更新本位值 */
            } else {
                carry = 0;
                T[i + j] = temp;
            }
        }
        if(carry != 0) T[i + j] = carry;                                      /* 最高位进位 */
    }
    // 处理符号
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
    // 处理长度
    if(r.signum != 0) {                         /* 先判断结果的符号 */
        //  高位去0
        for(int i = T.size() - 1; i >= 0; i--) {
            if(T[i] == 0) {
                T.pop_back();
            } else {
                break;
            }
        }
        // 数字串长度
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
BigInteger BigInteger::operator/(const BigInteger &tmp)     // 最基础的算法，效率上可能有不足
{
    BigInteger q = *this , t = tmp, ans, ZERO("0");
    assert(!(t == ZERO));                       /* 除数不为0                */
    if(q == ZERO) return ZERO;                  /* 被除数为0返回0           */
    if(q == t) {                                /* 两数相等则直接返回1      */
        ans.signum = 1;
        ans.length = 1;
        ans.bigInteger.push_back(1);
    } else {
        if(q > t) {                             /* 被除数大于除数，开始整除 */
            vector<int> T(250, 0);
            int index = 0, maxl = 0;
            while(true) {
                q = q - t;
                if(ZERO > q) {
                    if(!(ZERO == q)) break;     /* 直到减到q小于零，当能整除的时候要将商加1 */
                }
                T[index]++;
                if(T[index] >= CARRY) {         /*判定进位              */
                    T[index] = 0;
                    T[++index]++;
                    maxl = max(maxl, index);
                    for(int i = index; i < maxl; i++) {
                        if(T[i] >= CARRY) {
                            T[i + 1]++;
                            T[i] = 0;
                        }
                    }
                    index = 0;                  /* 重回最低位累加      */
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
    cout << "开始测试" << endl;
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
    cout<<"结束测试"<<endl;
    return 0;
}
