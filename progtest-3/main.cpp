#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

class CBigInt;
int checkSize(const CBigInt &a, const CBigInt &b);
bool isEqual(vector<int> v1, char s1, vector<int> v2, char s2){
    return s1 == s2 && v1 == v2;
}


class CBigInt {
public:
    CBigInt(){
        bigInt.push_back(0);
        sign = '+';
    }
    explicit CBigInt(string x);    // string constructor
    explicit CBigInt(int bigInt1);       // int constructor
    explicit CBigInt(vector<int> x, char s);
    ~CBigInt() { this->bigInt.clear();}

    friend CBigInt operator + (const CBigInt &a, const CBigInt &b); // operator +, any combination {CBigInt/int/string} + {CBigInt/int/string}
    friend CBigInt operator + (const CBigInt &a, const char*b);
    friend CBigInt operator + (const char *a, const CBigInt &b);
    friend CBigInt operator + (const CBigInt &a, int b);
    friend CBigInt operator + (int a, const CBigInt &b);

    friend CBigInt operator * (const CBigInt &a, const CBigInt &b);
    friend CBigInt operator * (const CBigInt &a, const char*b);
    friend CBigInt operator * (const char *a, const CBigInt &b);
    friend CBigInt operator * (const CBigInt &a, int b);
    friend CBigInt operator * (int a, const CBigInt &b);

    CBigInt& operator += (const CBigInt &b);
    CBigInt& operator += (const char*b);
    CBigInt& operator += (int b);

    CBigInt& operator *= (const CBigInt &b);
    CBigInt& operator *= (const char*b);
    CBigInt& operator *= (int b);

    CBigInt& operator=(const CBigInt &a);
    CBigInt& operator=(const string &a);
    CBigInt& operator=(int a);

    friend bool operator<(const CBigInt &b, const CBigInt &a);
    friend bool operator<(const CBigInt &a, const char *b);
    friend bool operator<(const char *b, const CBigInt &a);
    friend bool operator<(const CBigInt &a, int b);
    friend bool operator<(int a, const CBigInt &b);

    friend bool operator<=(const CBigInt &b, const CBigInt &a);
    friend bool operator<=(const CBigInt &a, const char *b);
    friend bool operator<=(const char *b, const CBigInt &a);
    friend bool operator<=(const CBigInt &a, int b);
    friend bool operator<=(int a, const CBigInt &b);

    friend bool operator>(const CBigInt &b, const CBigInt &a);
    friend bool operator>(const CBigInt &a, const char *b);
    friend bool operator>(const char *b, const CBigInt &a);
    friend bool operator>(const CBigInt &a, int b);
    friend bool operator>(int a, const CBigInt &b);

    friend bool operator>=(const CBigInt &b, const CBigInt &a);
    friend bool operator>=(const CBigInt &a, const char *b);
    friend bool operator>=(const char *b, const CBigInt &a);
    friend bool operator>=(const CBigInt &a, int b);
    friend bool operator>=(int a, const CBigInt &b);

    friend bool operator==(const CBigInt &b, const CBigInt &a);
    friend bool operator==(const CBigInt &a, const char *b);
    friend bool operator==(const char *b, const CBigInt &a);
    friend bool operator==(const CBigInt &a, int b);
    friend bool operator==(int a, const CBigInt &b);

    friend bool operator!=(const CBigInt &b, const CBigInt &a);
    friend bool operator!=(const CBigInt &a, const char *b);
    friend bool operator!=(const char *b, const CBigInt &a);
    friend bool operator!=(const CBigInt &a, int b);
    friend bool operator!=(int a, const CBigInt &b);

    friend ostream& operator<<(ostream& os, const CBigInt& a);
    friend bool operator>>(istream& is, CBigInt& a);

//private:
    char sign;
    vector<int> bigInt;
};

//treba skipovat uvodne nuly, popripade medzery a nasledne zistit znamienko.
CBigInt::CBigInt(string x) {
    int current;
    unsigned i = 0;
    while (x.at(i) == ' ')
    {
        i++;
        if (i >= x.size())
            throw invalid_argument("Invalid input.");
    }
    if ( x.at(i) == '-')
    {
        sign = '-';
        i++;
    }
    else if (x.at(i) == '+')
    {
        sign = '+';
        i++;
    } else sign = '+';
    while ( x.at(i) == '0')
    {
        i++;
        if (i >= x.size())
        {
            sign = '+';
            bigInt.push_back(0);
            break;
        }
    }
    for (; i < x.size(); ++i) {
        current = x.at(i) - 48;
        if (current < 0 || current > 9)
            break;
        bigInt.push_back(current);
    }

    if (bigInt.empty())
        throw invalid_argument("Invalid input.");
}

CBigInt::CBigInt(vector<int> x, char s) {
    bigInt = x;
    sign = s;
    while (bigInt.at(0) == 0)
    {
        bigInt.erase(bigInt.begin());
        if (bigInt.empty())
        {
            bigInt.push_back(0);
            sign = '+';
            break;
        }
    }
}

CBigInt::CBigInt(int bigInt1) {
    string curr = to_string(bigInt1);
    unsigned i = 0;
    if (curr.at(i) == '-')
    {
        sign = '-';
        i++;
    }
    else
        sign = '+';
    for ( ; i < curr.size(); i++) {
        bigInt.push_back(curr.at(i)-48);
    }



}

CBigInt operator+(const CBigInt &a, const CBigInt &b) {
    unsigned size;
    vector<int> x;
    int c;
    bool carry = false;

    if (a.bigInt.size() >= b.bigInt.size()) // kouknu co je vetsi
        size = a.bigInt.size();
    else
        size = b.bigInt.size();

    if ( (a.sign == '+' && b.sign == '+') || (a.sign == '-' && b.sign == '-'))
    {
        for (int i = 0; i < (int)size; ++i) {
            c = 0;
            if (carry) {
                c += 1;
                carry = false;
            }
            if ((int) a.bigInt.size() - 1 - i >= 0)
                c += a.bigInt.at(a.bigInt.size() - i - 1);
            if ((int)  b.bigInt.size() - 1 - i >= 0)
                c += b.bigInt.at(b.bigInt.size() - i - 1 );
            if (c > 9) {
                carry = true;
                c = c % 10;
            }
            x.insert(x.begin(), c);
        }
        if ( carry)
            x.insert(x.begin(), 1);
        if ( a.sign == '+' && b.sign == '+' )
            return CBigInt(x, '+');
        else  return CBigInt(x, '-');
    }
        // rovnaky algoritmus aj ked je a>b alebo a<b ALE, pri a<b to musim kontrolovat a zmenit znamenko
    else if ( a.sign == '+' && b.sign == '-')
    {
        int check = checkSize(a,b);
        if (check == 1) // a>b
        {
            for (int i = 0; i < (int) size; ++i) {
                c = 0;
                if (carry) {
                    c -= 1;
                    carry = false;
                }
                if ((int) a.bigInt.size() - 1 - i >= 0)
                    c += a.bigInt.at(a.bigInt.size() - i - 1);
                if ((int)  b.bigInt.size() - 1 - i >= 0)
                    c -= b.bigInt.at(b.bigInt.size() - i - 1 );
                if (c < 0) {
                    carry = true;
                    c = c + 10;
                }
                x.insert(x.begin(), c);
            }
            if ( carry)
                x.at(0)--;
            return CBigInt(x, '+');
        }

        else if (check == -1) // a<b
        {
            for (int i = 0; i < (int) size; ++i) {
                c = 0;
                if (carry) {
                    c -= 1;
                    carry = false;
                }
                if ((int) b.bigInt.size() - 1 - i >= 0)
                    c += b.bigInt.at(b.bigInt.size() - i - 1);
                if ((int)  a.bigInt.size() - 1 - i >= 0)
                    c -= a.bigInt.at(a.bigInt.size() - i - 1 );
                if (c < 0) {
                    carry = true;
                    c = c + 10;
                }
                x.insert(x.begin(), c);
            }
            if ( carry)
                x.at(0)--;
            return CBigInt(x, '-');
        }
    }
    else
    {
        int check = checkSize(a,b);
        if ( check  == 1) // a > b
        {
            for (int i = 0; i < (int)size; ++i) {
                c = 0;
                if (carry) {
                    c -= 1;
                    carry = false;
                }
                if ((int) a.bigInt.size() - 1 - i >= 0)
                    c += a.bigInt.at(a.bigInt.size() - i - 1);
                if ((int)  b.bigInt.size() - 1 - i >= 0)
                    c -= b.bigInt.at(b.bigInt.size() - i - 1 );
                if (c < 0) {
                    carry = true;
                    c = c + 10;
                }
                x.insert(x.begin(), c);
            }
            if ( carry)
                x.at(0)--;
            return CBigInt(x, '-');
        }
        else if ( check == -1) // a < b
        {
            for (int i = 0; i < (int)size; ++i) {
                c = 0;
                if (carry) {
                    c -= 1;
                    carry = false;
                }
                if ((int) b.bigInt.size() - 1 - i >= 0)
                    c += b.bigInt.at(b.bigInt.size() - i - 1);
                if ((int)  a.bigInt.size() - 1 - i >= 0)
                    c -= a.bigInt.at(a.bigInt.size() - i - 1 );
                if (c < 0) {
                    carry = true;
                    c = c + 10;
                }
                x.insert(x.begin(), c);
            }
            if ( carry)
                x.at(0)--;
            return CBigInt(x, '+');
        }
    }
    return CBigInt(x, '+');
}
CBigInt operator+(const CBigInt &a, const char *b) {
    CBigInt x(b);
    return a+x;
}
CBigInt operator+(const int a, const CBigInt &b) {
    CBigInt x(a);
    return b+x;
}
CBigInt operator+(const CBigInt &a, const int b) {
    CBigInt x(b);
    return  a+x;
}
CBigInt operator+(const char *a, const CBigInt &b) {
    CBigInt x(a);
    return b+x;
}

CBigInt& CBigInt::operator=(const CBigInt &a) {
    this->bigInt = a.bigInt;
    this->sign = a.sign;
    return *this;
}
CBigInt& CBigInt::operator=(const string &a) {
    CBigInt x(a);
    this->bigInt = x.bigInt;
    this->sign = x.sign;
    return *this;
}
CBigInt& CBigInt::operator=(const int a) {
    CBigInt x(a);
    this->bigInt = x.bigInt;
    this->sign = x.sign;
    return *this;
}

CBigInt& CBigInt::operator+=(int b) {
    CBigInt x(b);
    *this = *this+x;
    return *this;

}
CBigInt& CBigInt::operator+=(const char *b) {
    CBigInt x(b);
    *this = *this+x;
    return *this;
}
CBigInt& CBigInt::operator+=(const CBigInt &b) {
    *this = *this + b;
    return *this;
}

bool operator<(const CBigInt &b, const CBigInt &a){
    if (b.sign == '+' && a.sign == '-')
        return false;
    else if (b.sign == '-' && a.sign == '+')
        return true;
    else if( b.sign == '+' && a.sign == '+')
    {
        if (b.bigInt.size() < a.bigInt.size())
            return true;
        else if(b.bigInt.size() > a.bigInt.size())
            return false;
        else{
            for (unsigned i = 0; i < a.bigInt.size(); ++i) {
                if ( b.bigInt.at(i) < a.bigInt.at(i))
                    return true;
                else if ( b.bigInt.at(i) > a.bigInt.at(i))
                    return false;
            }
            return false;
        }
    }
    else {
        if (b.bigInt.size() < a.bigInt.size())
            return false;
        else if(b.bigInt.size() > a.bigInt.size())
            return true;
        else{
            for (unsigned i = 0; i < a.bigInt.size(); ++i) {
                if ( b.bigInt.at(i) < a.bigInt.at(i))
                    return false;
                else if ( b.bigInt.at(i) > a.bigInt.at(i))
                    return true;
            }
            return false;
        }
    }
}
bool operator<(const CBigInt &a, const char *b) {
    CBigInt x(b);
    return a<x;
}
bool operator<(const char *b, const CBigInt &a) {
    CBigInt x(b);
    return x<a;
}
bool operator<(const CBigInt &a, int b) {
    CBigInt x(b);
    return a<x;
}
bool operator<(int a, const CBigInt &b){
    CBigInt x(a);
    return x<b;
}

bool operator<=(const CBigInt &b, const CBigInt &a) {
    if (b.sign == '+' && a.sign == '-')
        return false;
    else if (b.sign == '-' && a.sign == '+')
        return true;
    else if(b.sign == '+' && a.sign == '+')
    {
        if (b.bigInt.size() < a.bigInt.size())
            return true;
        else if(b.bigInt.size() > a.bigInt.size())
            return false;
        else{
            for (unsigned i = 0; i < a.bigInt.size(); ++i) {
                if ( b.bigInt.at(i) < a.bigInt.at(i))
                    return true;
                else if ( b.bigInt.at(i) > a.bigInt.at(i))
                    return false;
            }
            return true;
        }
    }
    else{
        if (b.bigInt.size() < a.bigInt.size())
            return false;
        else if(b.bigInt.size() > a.bigInt.size())
            return true;
        else{
            for (unsigned i = 0; i < a.bigInt.size(); ++i) {
                if ( b.bigInt.at(i) < a.bigInt.at(i))
                    return false;
                else if ( b.bigInt.at(i) > a.bigInt.at(i))
                    return true;
            }
            return true;
        }
    }
}
bool operator<=(const CBigInt &a, const char *b) {
    CBigInt x(b);
    return a<=x;
}
bool operator<=(const char *b, const CBigInt &a) {
    CBigInt x(b);
    return x<=a;
}
bool operator<=(const CBigInt &a, int b) {
    CBigInt x(b);
    return a<=x;
}
bool operator<=(int a, const CBigInt &b){
    CBigInt x(a);
    return x<=b;
}

bool operator>(const CBigInt &b, const CBigInt &a) {
    if (b.sign == '+' && a.sign == '-')
        return true;
    else if (b.sign == '-' && a.sign == '+')
        return false;
    else if( b.sign == '+' && a.sign == '+')
    {
        if (b.bigInt.size() < a.bigInt.size())
            return false;
        else if(b.bigInt.size() > a.bigInt.size())
            return true;
        else{
            for (unsigned i = 0; i < a.bigInt.size(); ++i) {
                if ( b.bigInt.at(i) < a.bigInt.at(i))
                    return false;
                else if ( b.bigInt.at(i) > a.bigInt.at(i))
                    return true;
            }
            return false;
        }
    }
    else{
        if (b.bigInt.size() < a.bigInt.size())
            return true;
        else if(b.bigInt.size() > a.bigInt.size())
            return false;
        else{
            for (unsigned i = 0; i < a.bigInt.size(); ++i) {
                if ( b.bigInt.at(i) < a.bigInt.at(i))
                    return true;
                else if ( b.bigInt.at(i) > a.bigInt.at(i))
                    return false;
            }
            return false;
        }
    }
}
bool operator>(const CBigInt &a, const char *b) {
    CBigInt x(b);
    return a>x;
}
bool operator>(const char *b, const CBigInt &a) {
    CBigInt x(b);
    return x>a;
}
bool operator>(int a, const CBigInt &b) {
    CBigInt x(a);
    return x > b;
}
bool operator>(const CBigInt &a, int b) {
    CBigInt x(b);
    return a>x;
}

bool operator>=(const CBigInt &b, const CBigInt &a) {
    if (b.sign == '+' && a.sign == '-')
        return true;
    else if (b.sign == '-' && a.sign == '+')
        return false;
    else if( b.sign == '+' && a.sign == '+')
    {
        if (b.bigInt.size() < a.bigInt.size())
            return false;
        else if(b.bigInt.size() > a.bigInt.size())
            return true;
        else{
            for (unsigned i = 0; i < a.bigInt.size(); ++i) {
                if ( b.bigInt.at(i) < a.bigInt.at(i))
                    return false;
                else if ( b.bigInt.at(i) > a.bigInt.at(i))
                    return true;
            }
            return true;
        }
    }
    else{
        if (b.bigInt.size() < a.bigInt.size())
            return true;
        else if(b.bigInt.size() > a.bigInt.size())
            return false;
        else{
            for (unsigned i = 0; i < a.bigInt.size(); ++i) {
                if ( b.bigInt.at(i) < a.bigInt.at(i))
                    return true;
                else if ( b.bigInt.at(i) > a.bigInt.at(i))
                    return false;
            }
            return true;
        }
    }
}
bool operator>=(const CBigInt &a, const char *b) {
    CBigInt x (b);
    return  a>=x;
}
bool operator>=(const char *b, const CBigInt &a) {
    CBigInt x (b);
    return  x >=a;
}
bool operator>=(const CBigInt &a, int b) {
    CBigInt x (b);
    return  a >=x;
}
bool operator>=(int a, const CBigInt &b) {
    CBigInt x (a);
    return  x >=b;
}

bool operator==(const CBigInt &b, const CBigInt &a) {
    return isEqual(b.bigInt, b.sign, a.bigInt, a.sign);
}
bool operator==(const CBigInt &a, const char *b) {
    CBigInt x(b);
    return a==x;
}
bool operator==(const char *b, const CBigInt &a) {
    CBigInt x(b);
    return a==x;
}
bool operator==(const CBigInt &a, int b) {
    CBigInt x(b);
    return a==x;
}
bool operator==(int a, const CBigInt &b) {
    CBigInt x(a);
    return b==x;
}

bool operator!=(const CBigInt &b, const CBigInt &a) {
    return !isEqual(b.bigInt, b.sign, a.bigInt, a.sign);
}
bool operator!=(const CBigInt &a, const char *b) {
    CBigInt x(b);
    return a!=x;
}
bool operator!=(const char *b, const CBigInt &a) {
    CBigInt x(b);
    return a!=x;
}
bool operator!=(const CBigInt &a, int b) {
    CBigInt x(b);
    return a!=x;
}
bool operator!=(int a, const CBigInt &b) {
    CBigInt x(a);
    return b!=x;
}

ostream &operator<<(ostream &os, const CBigInt &a) {
    string x;
    for (unsigned i = 0; i < a.bigInt.size(); ++i) {
        x.push_back(a.bigInt.at(i)+48);
    }
    if (a.sign == '-')
        os << a.sign << x;
    else
        os << x;
    return os;
}
bool operator>>(istream &is, CBigInt &a) {
    string x;
    vector<int> bigInt;
    is >> x;
    int current;
    unsigned i = 0;
    while (x.at(i) == ' ')
    {
        i++;
        if (i >= x.size())
            return false;
    }
    if ( x.at(i) == '-')
        i++;
    else if (x.at(i) == '+')
        i++;
    if ( i >= x.size())
        return false;
    while ( x.at(i) == '0')
    {
        i++;
        if (i >= x.size())
        {
            bigInt.push_back(0);
            break;
        }
    }
    for (; i < x.size(); ++i) {
        current = x.at(i) - 48;
        if (current < 0 || current > 9)
            break;
        bigInt.push_back(current);
    }
    if (bigInt.empty())
        return false;
    CBigInt b(x);
    a.bigInt = b.bigInt;
    a.sign = b.sign;
    return true;
}
// with help of: https://www.geeksforgeeks.org/multiply-large-numbers-represented-as-strings/
CBigInt operator*(const CBigInt &a, const CBigInt &b) {
    CBigInt x;
    int len1 = a.bigInt.size();
    int len2 = b.bigInt.size();
    if (a == 0 || b == 0)
        return x;

    vector<int> result(len1 + len2, 0);

    int i_n1 = 0;
    int i_n2 = 0;

    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = a.bigInt[i];

        i_n2 = 0;

        for (int j=len2-1; j>=0; j--)
        {
            int n2 = b.bigInt[j];

            int sum = n1*n2 + result[i_n1 + i_n2] + carry;

            carry = sum/10;

            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        i_n1++;
    }

    int i = (int)result.size() - 1;
    while (i>=0 && result[i] == 0)
        i--;

    x.bigInt.clear();
    while (i >= 0)
        x.bigInt.push_back(result[i--]);

    if ((a.sign == '+' && b.sign == '+') || (a.sign == '-' && b.sign == '-'))
        x.sign = '+';
    else
        x.sign = '-';
    return x;
}
CBigInt operator*(const CBigInt &a, const char *b) {
    CBigInt x(b);
    return a*x;
}
CBigInt operator*(const char *a, const CBigInt &b) {
    CBigInt x(a);
    return b*x;
}
CBigInt operator*(const CBigInt &a, int b) {
    CBigInt x(b);
    return a*x;
}
CBigInt operator*(int a, const CBigInt &b) {
    CBigInt x(a);
    return b*x;
}

CBigInt &CBigInt::operator*=(const CBigInt &b) {
    *this = *this *b;
    return *this;
}
CBigInt &CBigInt::operator*=(const char *b) {
    CBigInt x(b);
    *this = *this * x;
    return *this;

}
CBigInt &CBigInt::operator*=(int b) {
    CBigInt x(b);
    *this = *this * x;
    return *this;
}

int checkSize(const CBigInt &a, const CBigInt &b){
    if ( a.bigInt.size() > b.bigInt.size())
        return 1;
    else if ( a.bigInt.size() < b.bigInt.size())
        return -1;
    else{
        for (unsigned i = 0; i < a.bigInt.size(); ++i) {
            if (a.bigInt.at(i) > b.bigInt.at(i))
                return 1; // a>b
            else if (a.bigInt.at(i) < b.bigInt.at(i))
                return -1; // a<b || a==b
        }
        return 1;
    }
}
#ifndef __PROGTEST__
static bool equal ( const CBigInt & x, const char * val )
{
    ostringstream oss;
    oss << x;
    return oss . str () == val;
}
int main ( void )
{
    CBigInt a, b;
    istringstream is;
    a = 10;
    a += 20;
    assert ( equal ( a, "30" ) );
    a *= 5;
    assert ( equal ( a, "150" ) );
    b = a + 3;
    assert ( equal ( b, "153" ) );
    b = a * 7;
    assert ( equal ( b, "1050" ) );
    assert ( equal ( a, "150" ) );

    a = 10;
    a += -20;
    assert ( equal ( a, "-10" ) );
    a *= 5;
    assert ( equal ( a, "-50" ) );
    b = a + 73;
    assert ( equal ( b, "23" ) );
    b = a * -7;
    assert ( equal ( b, "350" ) );
    assert ( equal ( a, "-50" ) );

    a = "12345678901234567890";
    a += "-99999999999999999999";
    assert ( equal ( a, "-87654321098765432109" ) );
    a *= "54321987654321987654";
    assert ( equal ( a, "-4761556948575111126880627366067073182286" ) );
    a *= 0;
    assert ( equal ( a, "0" ) );
    a = 10;
    b = a + "400";
    assert ( equal ( b, "410" ) );
    b = a * "15";
    assert ( equal ( b, "150" ) );
    assert ( equal ( a, "10" ) );

    is . clear ();
    is . str ( " 1234" );
    assert ( is >> b );
    assert ( equal ( b, "1234" ) );
    is . clear ();
    is . str ( " 12 34" );
    assert ( is >> b );
    assert ( equal ( b, "12" ) );
    is . clear ();
    is . str ( "999z" );
    assert ( is >> b );
    assert ( equal ( b, "999" ) );
    is . clear ();
    is . str ( "abcd" );
    assert ( ! ( is >> b ) );
    is . clear ();
    is . str ( "- 758" );
    assert ( ! ( is >> b ) );
    try
    {
        a = "-xyz";
        assert ( "missing an exception" == NULL );
    }
    catch ( const invalid_argument & e )
    {
    }

    a = "73786976294838206464";
    assert ( a < "1361129467683753853853498429727072845824" );
    assert ( a <= "1361129467683753853853498429727072845824" );
    assert ( ! ( a > "1361129467683753853853498429727072845824" ) );
    assert ( ! ( a >= "1361129467683753853853498429727072845824" ) );
    assert ( ! ( a == "1361129467683753853853498429727072845824" ) );
    assert ( a != "1361129467683753853853498429727072845824" );
    assert ( ! ( a < "73786976294838206464" ) );
    assert ( a <= "73786976294838206464" );
    assert ( ! ( a > "73786976294838206464" ) );
    assert ( a >= "73786976294838206464" );
    assert ( a == "73786976294838206464" );
    assert ( ! ( a != "73786976294838206464" ) );
    assert ( a < "73786976294838206465" );
    assert ( a <= "73786976294838206465" );
    assert ( ! ( a > "73786976294838206465" ) );
    assert ( ! ( a >= "73786976294838206465" ) );
    assert ( ! ( a == "73786976294838206465" ) );
    assert ( a != "73786976294838206465" );
    a = "2147483648";
    assert ( ! ( a < -2147483648 ) );
    assert ( ! ( a <= -2147483648 ) );
    assert ( a > -2147483648 );
    assert ( a >= -2147483648 );
    assert ( ! ( a == -2147483648 ) );
    assert ( a != -2147483648 );

}
#endif /* __PROGTEST__ */
