#include <iostream>
#include "mystring.h"
using namespace std;
const int ArSize = 10;
const int Maxlen = 80;
int main()
{
    myString name;
    cout<< "Hi, what's your name?\n>>";
    cin>>name;
    cout<< name << ", please enter up to "<< ArSize << " short sayings < empty line to quit>:\n";
    myString saying[ArSize];
    char temp[Maxlen];
    int i;
    for(i = 0; i<ArSize; i++)
    {
        cout<< i + 1<<": ";
        cin.get(temp, Maxlen);
        while(cin && cin.get() != '\n')
            continue;
        if(!cin || temp == '\0')
            break;
        else saying[i] = temp;
    }
    int total = i;
    if(total > 0)
    {
        cout<<total<<endl;
        cout<< "Here are your sayings: \n";
        for(i = 0; i<total; i++)
            cout<< saying[i][0] <<": "<<saying[i]<<endl;
        int shorest = 0;
        int first = 0;
        for(i = 1; i<total; i++)
        {
            if(saying[i].length() < saying[shorest].length())
                shorest = i;
            if(saying[i] < saying[first])
                first = i;
        }
        cout<< "Shortest saying :\n" << saying[shorest]<<endl;
        cout<< "First alphabetically:\n" << saying[first]<<endl;
        cout<< "This program used " <<myString::HowMany()<< " myString object. Bye.\n";
    }
    else
    {
        cout<<"No input! Bye.\n";
    }
    return 0;
}
