#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED
#include <iostream>
using std::ostream;
using std::istream;

class myString
{
private:
    char * str;
    int len;
    static int num_strings;
    static const int CINLIM = 80;
public:
    myString (const char * s);
    myString();
    myString(const myString &);
    ~myString();
    int length() const
    {
        return len;
    }
    myString & operator = (const myString & st);
    myString & operator = (const char * s);
    char & operator [] (int i);
    const char & operator [] (int i) const;
    friend bool operator < (const myString & st1, const myString & st2);
    friend bool operator == (const myString & st1, const myString & st2);
    friend bool operator > (const myString & st1, const myString & st2);
    friend ostream & operator << (ostream & os, const myString & st);
    friend istream & operator >> (istream & is, myString & st);
    static int HowMany();
};

#endif // MYSTRING_H_INCLUDED
