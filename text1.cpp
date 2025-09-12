#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
    while(1)
    {
        cout<<"请输入:";
        cin>>s;
        if(s=="Dian")   cout<<"2002"<<endl;
        else if(s=="Quit")  break;
        else    cout<<"Error"<<endl;
    }
    return 0;
}