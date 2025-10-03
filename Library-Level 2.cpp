#include<bits/stdc++.h>
using namespace std;
struct sysdata
{
    int fx,fy;
    int cnt;
} sd;
struct lib
{
    char user[100];
    int state,idx;
    bool ava;
}a[10][10][10][10];
//5层7天4行4列
struct res
{
    char name[100];
    int date,floor,x,y;
}info[1000];

int fx,fy,cnt;
string s;
string Date[]={"monday","tuesday","wednesday","thursday","friday","saturday","sunday"};

void lower(string &s)
{
    for(int i=0;i<s.size();i++)
        if(s[i]>='A'&&s[i]<='Z')
            s[i]=s[i]-'A'+'a';
}
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
    fx=fy=4;
    cnt=0;
}
void help()
{
    cout<<"可用命令:"<<endl;
    cout<<"1. Reserve - 预约座位"<<endl;
    cout<<"2. Cancel - 取消预约"<<endl;
    cout<<"3. Reservation - 查看已预约信息"<<endl;
    cout<<"4. Query - 查看特定日期和楼层的座位可用性"<<endl;
    cout<<"5. Exit - 登出系统"<<endl;
    cout<<"6. Quit - 退出程序"<<endl;
    cout<<"7. Help - 显示帮助信息"<<endl;

    cout<<"管理员命令:"<<endl;
    cout<<"注: 仅用户名为'Admin'的用户可使用管理员命令"<<endl;
    cout<<"1. Clear - 清除所有预约记录"<<endl;
    cout<<"2. Extend - 拓展图书馆座位"<<endl;
    cout<<"3. Reduce - 减少图书馆座位"<<endl;
    cout<<"4. Modify - 重置指定楼层或日期的用户预约信息"<<endl;

    cout<<"座位状态说明:"<<endl;
    cout<<"0 - 空闲，1 - 已预约，2 - 当前预约"<<endl;
}
void read()
{
    ifstream file("lib2.bin",ios::binary);
    if(file.is_open())
    {
        file.read(reinterpret_cast<char*>(&sd), sizeof(sd));
        fx=sd.fx;
        fy=sd.fy;
        cnt=sd.cnt;
        file.read(reinterpret_cast<char*>(&a), sizeof(a));
        file.read(reinterpret_cast<char*>(&info), sizeof(info));
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
        sd.cnt=cnt;
        file.write(reinterpret_cast<const char*>(&sd), sizeof(sd));
        file.write(reinterpret_cast<const char*>(&a), sizeof(a));
        file.write(reinterpret_cast<const char*>(&info), sizeof(info));
        file.close();
    }
    else cout<<"输出：无法保存数据"<<endl;
}
void update(int idx,string name,int n,int floor,int x,int y)
{
    strcpy(info[idx].name,name.c_str());
    info[idx].date=n;
    info[idx].floor=floor;
    info[idx].x=x;
    info[idx].y=y;
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
                    a[i][j][k][l].idx=0;
                }
    for(int i=1;i<=cnt;i++)
    {
        update(i,"",0,0,0,0);
    }
    init();
    save();    
}
void get_info(string name)
{
    bool exist=0;
    for(int i=1;i<=cnt;i++)
    {
        if(strcmp(info[i].name,name.c_str())==0)
        {
            cout<<i<<". "<<info[i].name<<" "<<Date[info[i].date-1]<<" Floor "<<info[i].floor<<" Seat "<<info[i].x<<" "<<info[i].y<<endl;
            exist=1;
        }
    }
    if(!exist) cout<<"输出：No Reservation"<<endl;
}
void cover(int idx)
{
    for(int i=idx;i<cnt;i++)
    {
        strcpy(info[i].name,info[i+1].name);
        info[i].date=info[i+1].date;
        info[i].floor=info[i+1].floor;
        info[i].x=info[i+1].x;
        info[i].y=info[i+1].y;
    }
    cnt--;
}

int main()
{
    read();
    cout<<"欢迎使用图书馆预约系统！"<<endl;
    while(1)
    {
        cout<<"请输入“Login”以登录系统，或输入“Quit”以退出程序。"<<endl;
        cout<<"输入：";
        cin>>s;
        lower(s);
        if(s=="login")
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
                lower(cmd);
                if(cmd=="quit"||cmd=="exit")
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
                    if(cmd=="quit")
                    {
                        cout<<"输出：退出成功"<<endl;
                        return 0;
                    }
                    break;
                    cout<<"输出：输入Login以登录，或输入Quit以退出程序"<<endl;
                }

                if(cmd=="reserve")
                {
                    read();

                    string name1;
                    if(name=="Admin")   
                    {
                        cout<<"输出：请输入用户名"<<endl<<"输入：";
                        cin>>name1;
                    }
                    else name1=name;

                    cout<<"输出：请输入日期"<<endl<<"输入：";
                    cin>>date;
                    lower(date);
                    cout<<"输出：请输入楼层"<<endl<<"输入：";
                    cin>>floor;
                    cout<<"输出：请输入座位位置（行 列）"<<endl<<"输入：";
                    cin>>x>>y;
                    n=get_date(date)+1;
                    if(n==0)
                    {
                        cout<<"输出：日期输入错误"<<endl;
                        continue;
                    }

                    if(a[floor][n][x][y].state==0&&a[floor][n][x][y].ava)
                    {
                        cnt++;
                        update(cnt,name1,n,floor,x,y);
                        a[floor][n][x][y].state=1;
                        strcpy(a[floor][n][x][y].user,name1.c_str());
                        a[floor][n][x][y].idx=cnt;
                        cout<<"输出：OK"<<endl;
                        save();
                    }
                    else    cout<<"输出：Fail"<<endl;
                }
                else if(cmd=="cancel")
                {
                    read();

                    string name1;
                    if(name=="Admin")
                    {
                        cout<<"输出：请输入用户名"<<endl<<"输入：";
                        cin>>name1;
                    }
                    else name1=name;
                    int idx;
                    cout<<"输出：请输入需要取消的预约序号"<<endl;
                    get_info(name1);
                    cout<<"输入：";
                    cin>>idx;
                    a[info[idx].floor][info[idx].date][info[idx].x][info[idx].y].state=0;
                    strcpy(a[info[idx].floor][info[idx].date][info[idx].x][info[idx].y].user,"");
                    update(idx,"",0,0,0,0);
                    cover(idx);
                    save();
                    cout<<"输出：取消成功"<<endl;
                }
                else if(cmd=="reservation")
                {
                    read();

                    if(name=="Admin")
                    {
                        bool isempty=0;
                        
                        for(int i=1;i<=cnt;i++)
                        {
                            if(strcmp(info[i].name,"")!=0)
                            {
                                cout<<info[i].name<<" "<<Date[info[i].date-1]<<" Floor "<<info[i].floor<<" Seat "<<info[i].x<<" "<<info[i].y<<endl;
                                isempty=1;
                            }
                        }
                        if(!isempty)
                            cout<<"输出：No reservation"<<endl;
                    }
                    else get_info(name);
                }
                else if(cmd=="query")
                {
                    read();

                    cout<<"输出：请输入日期"<<endl<<"输入：";
                    cin>>date;
                    lower(date);
                    n=get_date(date)+1;
                    if(n==0)
                    {
                        cout<<"输出：日期输入错误"<<endl;
                        continue;
                    }
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
                            else cout<<"   ";
                        }
                        cout<<endl;
                    }
                }
                else if(cmd=="help")
                {
                    help();
                }
                else if(name=="Admin")
                {
                    if(cmd=="clear")
                    {
                        clear();
                        cout<<"输出：清除成功"<<endl;
                    }
                    else if(cmd=="extend")
                    {
                        if(fx<=9&&fy<=9)
                        {
                            cout<<"输出：请输入楼层号"<<endl<<"输入：";
                            cin>>floor;
                            cout<<"输出：请输入座位位置（行 列）"<<endl<<"输入：";
                            cin>>x>>y;
                            if(x<=9&&y<=9)
                            {
                                fx=max(fx,x);
                                fy=max(fy,y);
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
                    else if(cmd=="reduce")
                    {
                        read();
                        if(fx>1&&fy>1)
                        {
                            cout<<"输出：请输入楼层号"<<endl<<"输入：";
                            cin>>floor;
                            cout<<"输出：请输入座位位置（行 列）"<<endl<<"输入：";
                            cin>>x>>y;
                            for(int i=1;i<=7;i++)
                            {
                                a[floor][i][x][y].ava=false;
                                if(a[floor][i][x][y].state==1||a[floor][i][x][y].state==2)
                                {
                                    update(a[floor][i][x][y].idx,"",0,0,0,0);
                                    cover(a[floor][i][x][y].idx);
                                    a[floor][i][x][y].state=0;
                                    strcpy(a[floor][i][x][y].user,"");
                                    a[floor][i][x][y].idx=0;
                                }
                            }
                            cout<<"输出：减少成功"<<endl;
                            save();
                        }
                        else
                            cout<<"输出：已达最小容量，无法减少"<<endl;
                    }
                    else if(cmd=="modify")
                    {
                        cout<<"输出：请输入修改目标（Floor/Date）"<<endl<<"输入：";
                        string op;
                        cin>>op;
                        lower(op);
                        if(op=="floor")
                        {
                            cout<<"输出：请输入楼层号"<<endl<<"输入：";
                            cin>>floor;

                            cout<<"输出：请输入修改方向（Actv/Forb）"<<endl<<"输入：";
                            string op2;
                            cin>>op2;
                            lower(op2);
                            int x;
                            if(op2=="actv") x=1;
                            else if(op2=="forb") x=0;
                            else
                            {
                                cout<<"输出：指令错误"<<endl;
                                continue;
                            }

                            for(int i=1;i<=7;i++)
                            {
                                for(int j=1;j<=fx;j++)
                                {
                                    for(int k=1;k<=fy;k++)
                                    {
                                        if(!x)   
                                        {
                                            update(a[floor][i][j][k].idx,"",0,0,0,0);
                                            cover(a[floor][i][j][k].idx);
                                            a[floor][i][j][k].idx=0;
                                            a[floor][i][j][k].state=0;
                                            strcpy(a[floor][i][j][k].user,"");
                                        }
                                        a[floor][i][j][k].ava=x;
                                    }
                                }
                            }
                            save();
                            cout<<"输出：修改完毕"<<endl;
                        }
                        else if(op=="date")
                        {
                            read();
                            string date;
                            cout<<"输出：请输入日期"<<endl<<"输入：";
                            cin>>date;
                            n=get_date(date)+1;
                            if(n==0)
                            {
                                cout<<"输出：日期输入错误"<<endl;
                                continue;
                            }
                            cout<<"输出：请输入修改方向（Actv/Forb）"<<endl<<"输入：";

                            string op2;
                            cin>>op2;
                            lower(op2);
                            int x;
                            if(op2=="actv") x=1;
                            else if(op2=="forb") x=0;
                            else
                            {
                                cout<<"输出：指令错误"<<endl;
                                continue;
                            }

                            for(int i=1;i<=5;i++)
                            {
                                for(int j=1;j<=fx;j++)
                                {
                                    for(int k=1;k<=fy;k++)
                                    {
                                        if(!x)   
                                        {
                                            update(a[i][n][j][k].idx,"",0,0,0,0);
                                            cover(a[i][n][j][k].idx);
                                            a[i][n][j][k].idx=0;
                                            a[i][n][j][k].state=0;
                                            strcpy(a[i][n][j][k].user,"");
                                        }
                                        a[i][n][j][k].ava=x;
                                    }
                                }
                            }
                            save();
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
        else if(s=="quit")
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