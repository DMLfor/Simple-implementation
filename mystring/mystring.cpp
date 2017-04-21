#include <iostream>
#include "mystring.h"
#include <cstring>
using std:: ostream;
using std:: istream;

using std:: cout;
using std:: cin;
int myString :: num_strings = 0;

int myString :: HowMany()
{
    return num_strings;
}
myString :: myString()
{
    len = 4;
    str = new char [len+1];
    num_strings ++;
    str[0] = '\0';
}
myString :: myString(const char * s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings ++;
}

myString :: myString(const myString & st)
{
    num_strings ++;
    len = st.len;
    str = new char[len + 1];
    std:: strcpy(str, st.str);
}

myString :: ~myString()
{
    num_strings --;
    delete [] str;
}

myString & myString :: operator = (const char * s)
{
    delete [] str;
    len = std::strlen(s);
    str = new char [len + 1];
    std::strcpy(str, s);
    return *this;
}

myString & myString :: operator = (const myString & st)
{
    if(st == *this)
        return *this;
    delete [] str;
    len = st.len;
    str = new char [len + 1];
    std::strcpy(str, st.str);
    return *this;
}

char & myString :: operator [] (int i)
{
    return str[i];
}

const char & myString :: operator [] (int i) const
{
    return str[i];
}

bool operator == (const myString & st1, const myString & st2)
{
    return (std::strcmp(st2.str, st1.str) == 0);
}

bool operator < (const myString & st1, const myString & st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator > (const myString & st1, const myString & st2)
{
    return st2 < st1;
}

ostream & operator << (ostream & os, const myString & st)
{
    os<<st.str;
    return os;
}

istream & operator >> (istream & is, myString & st)
{
    char temp [myString:: CINLIM];
    is.get(temp, myString :: CINLIM);
    if(is) st = temp;
    while(is && is.get() != '\n')
        continue;
    return is;
}
