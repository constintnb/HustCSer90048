#include <bits/stdc++.h>
using namespace std;
map<string,string> m;
string s,st;
int main()
{
    ifstream fin("text2.txt");
    while(getline(fin,s))
    {
        string s1,s2;
        int n=0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]==':')
                n=i;
        }
        if(n==0||n==s.size()-1)    continue;
        s1=s.substr(0,n);
        s2=s.substr(n+1);
        m[s1]=s2;
    }
    fin.close();
    while(getline(cin,st))
    {
        if(st=="Quit")  break;
        if(m.find(st)==m.end()) cout<<"Error"<<endl;
        else cout<<m[st]<<endl;
    }
    return 0;
}