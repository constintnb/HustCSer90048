#include<bits/stdc++.h>
using namespace std;
struct sysdata
{
    int fx,fy;
    char key[100][100];
    char value[100][100];
    int cnt;
} sd;
struct edge
{
    char user[10];
    int state;
    bool ava;
}a[10][10][10][10];
//5层7天4行4列
int fx,fy,cnt;
string s;
string Date[]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

int get_date(string str)
{
    for(int i=0;i<7;i++)
        if(str==Date[i])
            return i;
    return -1;
}
void init()
{
    for(int i=1;i<=5;i++)
        for(int j=1;j<=7;j++)
            for(int k=1;k<=4;k++)
                for(int l=1;l<=4;l++)
                {
                    a[i][j][k][l].ava=true;
                }
    sd.cnt=0;
}
void help()
{
    cout<<"可用命令:"<<endl;
    cout<<"1. Reserve - 预约座位"<<endl;
    cout<<"2. Reservation - 查看已预约信息"<<endl;
    cout<<"3. Query - 查看特定日期和楼层的座位可用性"<<endl;
    cout<<"4. Exit - 登出系统"<<endl;
    cout<<"5. Quit - 退出程序"<<endl;
    cout<<"6. Help - 显示帮助信息"<<endl;

    cout<<"管理员命令:"<<endl;
    cout<<"注: 仅用户名为'Admin'的用户可使用管理员命令"<<endl;
    cout<<"1. Clear - 清除所有预约记录"<<endl;
    cout<<"2. Extend - 拓展图书馆座位"<<endl;
    cout<<"3. Reduce - 减少图书馆座位"<<endl;
    cout<<"4. Modify - 重置指定楼层或日期的用户预约信息"<<endl;
}
void read()
{
    ifstream file("lib2.bin",ios::binary);
    if(file.is_open())
    {
        file.read(reinterpret_cast<char*>(&sd), sizeof(sd));
        fx=sd.fx;
        fy=sd.fy;
        //cnt=sd.cnt;
        file.read(reinterpret_cast<char*>(&a), sizeof(a));
        file.close();
    }
    else init();
}
void save()
{
    ofstream file("lib2.bin",ios::binary);
    if(file.is_open())
    {
        sd.fx=fx;
        sd.fy=fy;
        //sd.cnt=cnt;
        file.write(reinterpret_cast<const char*>(&sd), sizeof(sd));
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
                    a[i][j][k][l].ava=false;
                }
    init();
    /*
    for(int i=0;i<100;i++)
    {
        strcpy(sd.key[i],"");
        strcpy(sd.value[i],"");
    }
    */
    save();    
}
void info(string name)
{
    bool exist=0;
    cout<<cnt<<endl;
    for(int i=0;i<=cnt;i++)
    {
        if(strcmp(sd.key[i],name.c_str())==0)
        {
            cout<<sd.value[i]<<endl;
            exist=1;
        }
    }
    if(!exist) cout<<"输出：No Reservation"<<endl;
}

int main()
{
    read();
    if(fx<1||fx>9||fy<1||fy>9)
    {
        fx=4;fy=4;
    }
    cout<<"欢迎使用图书馆预约系统！"<<endl;
    cout<<"请输入“Login”以登录系统，或输入“Exit”以退出程序。"<<endl;
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
            help();

            bool flag=0;
            string cmd,date;
            int floor,x,y,n;
            while(1)
            {
                cout<<"输入：";
                cin>>cmd;
                if(cmd=="Quit"||cmd=="Exit")
                {
                    cout<<"输出：已登出"<<endl;
                    for(int i=0;i<6;i++)
                        for(int j=0;j<10;j++)
                            for(int k=0;k<10;k++)
                                for(int l=0;l<10;l++)
                                {
                                    if(a[i][j][k][l].state==2)
                                        a[i][j][k][l].state=1;
                                }
                    save();
                    if(cmd=="Quit")
                    {
                        cout<<"输出：退出成功"<<endl;
                        return 0;
                    }
                    break;
                    cout<<"输出：输入Login以登录，或输入Quit以退出程序"<<endl;
                }

                if(cmd=="Reserve")
                {
                    cout<<"输出：请输入日期"<<endl<<"输入：";
                    cin>>date;
                    cout<<"输出：请输入楼层"<<endl<<"输入：";
                    cin>>floor;
                    cout<<"输出：请输入座位位置（行 列）"<<endl<<"输入：";
                    cin>>x>>y;
                    n=get_date(date)+1;
                    if(name=="Admin")
                    {
                        string uname,op;
                        cout<<"输出：请输入用户名"<<endl<<"输入：";
                        cin>>uname;
                        cout<<"输出：请输入需要进行的预约操作（Add/Cancel）"<<endl<<"输入：";
                        cin>>op;
                        if(op=="Add")
                        {
                            if(a[floor][n][x][y].state==0&&a[floor][n][x][y].ava)
                            {
                                a[floor][n][x][y].state=1;

                                /*
                                strcpy(a[floor][n][x][y].user,uname.c_str());
                                strcpy(sd.key[cnt],uname.c_str());
                                strcpy(sd.value[cnt],(date+to_string(floor)+" "+to_string(x)+" "+to_string(y)).c_str());
                                cnt++;
                                */

                                cout<<"输出：OK"<<endl;
                                save();
                            }
                            else    cout<<"输出：Fail"<<endl;
                        }
                        else if(op=="Cancel")
                        {
                            if(a[floor][n][x][y].state!=0)
                            {
                                a[floor][n][x][y].state=0;
                                strcpy(a[floor][n][x][y].user,"");

                                for(int i=0;i<sd.cnt;i++)
                                {
                                    if(strcmp(sd.key[i],uname.c_str())==0)
                                    {
                                        strcpy(sd.key[i],"");
                                        strcpy(sd.value[i],"");
                                    }
                                }

                                cout<<"输出：OK"<<endl;
                                save();
                            }
                            else    cout<<"输出：Fail"<<endl;
                        }
                        else
                        {
                            cout<<"输出：指令错误"<<endl;
                        }
                    }
                    else if(a[floor][n][x][y].state==0)
                    {
                        strcpy(a[floor][n][x][y].user,name.c_str());
                        a[floor][n][x][y].state=2;

                        /*
                        strcpy(a[floor][n][x][y].user,name.c_str());
                        strcpy(sd.key[cnt],name.c_str());
                        strcpy(sd.value[cnt],(date+to_string(floor)+" "+to_string(x)+" "+to_string(y)).c_str());
                        cnt++;
                        */

                        cout<<"输出：OK"<<endl;
                        save();
                    }
                    else    cout<<"输出：Fail"<<endl;
                }
                else if(cmd=="Reservation")
                {
                    for(int i=1;i<=5;i++)
                    {
                        for(int j=1;j<=7;j++)
                        {
                            for(int k=1;k<=fx;k++)
                            {
                                for(int l=1;l<=fy;l++)
                                {
                                    if(strcmp(a[i][j][k][l].user,name.c_str())==0)
                                    {
                                        cout<<"输出："<<Date[j-1]<<" Floor "<<i<<" Seat "<<k<<" "<<l<<endl;
                                        flag=1;
                                    }
                                }
                            }
                        }
                    }
                    if(!flag) cout<<"输出：No reservation"<<endl;
                    /*
                    if(name=="Admin")
                    {
                        for(int i=0;i<cnt;i++)
                        {
                            if(strcmp(sd.key[i],"")!=0)
                                cout<<sd.key[i]<<" "<<sd.value[i]<<endl;
                        }
                    }
                    else info(name);
                    */
                    //if(flag)    cout<<"输出："<<date<<" floor "<<floor<<" Seat "<<x<<" "<<y<<endl;
                    //else    cout<<"输出：No reservation"<<endl;
                }
                else if(cmd=="Query")
                {
                    cout<<"输出：请输入日期"<<endl<<"输入：";
                    cin>>date;
                    n=get_date(date)+1;
                    //cout<<n<<endl;
                    cout<<"输出：请输入楼层"<<endl<<"输入：";
                    cin>>floor;
                    cout<<"输出："<<endl;
                    for(int i=1;i<=fx;i++)
                    {
                        for(int j=1;j<=fy;j++)
                        {
                            if(a[floor][n][i][j].ava==true)
                            {
                                if(a[floor][n][i][j].state!=0&&name=="Admin")   cout<<a[floor][n][i][j].user<<" ";
                                else if(strcmp(a[floor][n][i][j].user,name.c_str())==0&&a[floor][n][i][j].state==1) cout<<"2 ";
                                else cout<<a[floor][n][i][j].state<<" ";
                            }
                        }
                        cout<<endl;
                    }
                }
                else if(cmd=="Help")
                {
                    help();
                }
                else if(name=="Admin")
                {
                    if(cmd=="Clear")
                    {
                        clear();
                        cout<<"输出：清除成功"<<endl;
                    }
                    else if(cmd=="Extend")
                    {
                        if(fx<=9&&fy<=9)
                        {
                            cout<<"输出：请输入楼层号"<<endl<<"输入：";
                            cin>>floor;
                            cout<<"输出：请输入座位位置（行 列）"<<endl<<"输入：";
                            cin>>x>>y;
                            if(x<=9&&y<=9)
                            {
                                if(x>fx) fx++;
                                if(y>fy) fy++;
                                for(int i=1;i<=7;i++)
                                {
                                    a[floor][i][x][y].ava=true;
                                }
                                cout<<"输出：拓展成功"<<endl;
                                save();
                            }
                            else
                            {
                                cout<<"输出：输入位置超出当前范围，无法拓展"<<endl;
                            }
                        }
                        else
                            cout<<"输出：已达最大容量，无法拓展"<<endl;
                    }
                    else if(cmd=="Reduce")
                    {
                        if(fx>1&&fy>1)
                        {
                            cout<<"输出：请输入楼层号"<<endl<<"输入：";
                            cin>>floor;
                            cout<<"输出：请输入座位位置（行 列）"<<endl<<"输入：";
                            cin>>x>>y;

                            for(int i=1;i<=7;i++)
                            {
                                a[floor][i][x][y].ava=false;
                            }
                            cout<<"输出：减少成功"<<endl;
                            save();
                        }
                        else
                            cout<<"输出：已达最小容量，无法减少"<<endl;
                    }
                    else if(cmd=="Modify")
                    {
                        cout<<"输出：请输入下一步的修改命令（Floor/Date）"<<endl<<"输入：";
                        string op;
                        cin>>op;
                        if(op=="Floor")
                        {
                            cout<<"输出：请输入楼层号"<<endl<<"输入：";
                            cin>>floor;
                            for(int i=1;i<=7;i++)
                            {
                                for(int j=1;j<=fx;j++)
                                {
                                    for(int k=1;k<=fy;k++)
                                    {
                                        a[floor][i][j][k].state=0;
                                        strcpy(a[floor][i][j][k].user,"");
                                    }
                                }
                            }
                            cout<<"输出：修改完毕"<<endl;
                        }
                        else if(op=="Date")
                        {
                            string date;
                            cout<<"输出：请输入日期"<<endl<<"输入：";
                            cin>>date;
                            n=get_date(date)+1;
                            for(int i=1;i<=5;i++)
                            {
                                for(int j=1;j<=fx;j++)
                                {
                                    for(int k=1;k<=fy;k++)
                                    {
                                        a[i][n][j][k].state=0;
                                        strcpy(a[i][n][j][k].user,"");
                                    }
                                }
                            }
                            cout<<"输出：修改完毕"<<endl;
                        }
                        else
                        {
                            cout<<"输出：指令错误"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"输出：指令错误"<<endl;
                    }
                }
                else
                {
                    cout<<"输出：指令错误"<<endl;
                }
            }
        }
        else if(s=="Quit")
        {
            cout<<"输出：退出成功"<<endl;
            break;
        }
        else
        {
            cout<<"输出：指令错误"<<endl;
        }
    }
    return 0;
}