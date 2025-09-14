#include<bits/stdc++.h>
using namespace std;
struct edge
{
    char user[10];
    int state;
}a[6][10][10][10];
//5层7天4行4列
string s;
string date[]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

int get_date(string str)
{
    for(int i=0;i<7;i++)
        if(str==date[i])
            return i;
    return -1;
}

void read()
{
    ifstream file("lib.bin",ios::binary);
    if(file.is_open())
    {
        file.read(reinterpret_cast<char*>(&a), sizeof(a));
        file.close();
    }
}
void save()
{
    ofstream file("lib.bin",ios::binary);
    if(file.is_open())
    {
        file.write(reinterpret_cast<const char*>(&a), sizeof(a));
        file.close();
    }
}
void clear()
{
    for(int i=0;i<6;i++)
        for(int j=0;j<10;j++)
            for(int k=0;k<10;k++)
                for(int l=0;l<10;l++)
                {
                    a[i][j][k][l].state=0;
                    strcpy(a[i][j][k][l].user,"");
                }
    save();    
}

int main()
{
    read();
    while(1)
    {
        cout<<"输入：";
        cin>>s;
        if(s=="Login")
        {
            string name;
            cout<<"输出：请输入用户名"<<endl<<"输入：";
            cin>>name;
            cout<<"输出：登陆成功"<<endl;
            
            bool flag=0;
            string cmd,date,t1,t2;
            int floor,x,y,n;
            while(1)
            {
                cout<<"输入：";
                cin>>cmd;
                if(cmd=="Quit")
                {
                    cout<<"输出：已登出"<<endl;
                    break;
                }
                if(cmd=="Reserve")
                {
                    cin>>date>>t1>>floor>>t2>>x>>y;
                    n=get_date(date)+1;
                    if(a[floor][n][x][y].state==0)
                    {
                        strcpy(a[floor][n][x][y].user,name.c_str());
                        a[floor][n][x][y].state=2;
                        cout<<"输出：OK"<<endl;
                        flag=1;
                        save();
                    }
                }
                else if(cmd=="Reservation")
                {
                    if(flag)    cout<<"输出："<<date<<" floor "<<floor<<" Seat "<<x<<" "<<y<<endl;
                    else    cout<<"输出：No reservation"<<endl;
                }
                else if(cmd=="Clear"&&name=="Admin")
                {
                    clear();
                    cout<<"输出：清除成功"<<endl;
                }
                else if(get_date(cmd)!=-1)
                {
                    cin>>t1>>floor;
                    n=get_date(cmd)+1;
                    cout<<"输出："<<endl;
                    for(int i=1;i<=4;i++)
                    {
                        for(int j=1;j<=4;j++)
                        {
                            cout<<a[floor][n][i][j].state;
                        }
                        cout<<endl;
                    }
                }
                else
                {
                    cout<<"输出：指令错误"<<endl;
                }
            }
        }
        else if(s=="Exit")
        {
            cout<<"输出：退出成功"<<endl;
            break;
        }
    }
    return 0;
}