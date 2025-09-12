#include<bits/stdc++.h>
using namespace std;
struct edge
{
    char user[10];
    int state;
}a[5][7][4][4];



void read()
{
    ifstream file(lib.bin,ios::binary);
    file.read(reinterpret_cast<char*>(&a), sizeof(a));
    file.close();
}
void write()
{
    ofstream file(lib.bin,ios::binary);
    file.write(reinterpret_cast<const char*>(&a), sizeof(a));
    file.close();
}
void query()
{
    
}
int main()
{
    
}