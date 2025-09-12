#include<stdio.h>
#include<string.h>
const int N=1e3;
struct node
{
    char k[N],v[N];
}a[N];
int n=1;
int main()
{
    FILE *f;
    f=fopen("text2.txt","r");
    while(1)
    {
        char s[N];
        int len1,len2,len;
        len=strlen(s);
        fgets(s,sizeof(s),f);
        for(int i=0;i<len;i++)
        {
            if(s[i]==':')
            {
                for(int j=0;j<i;j++)
                    a[n].k[++len1]=s[j];
                for(int j=i+1;j<len;j++)
                    a[n].v[++len2]=s[j];
                break;
            }
        }
    }
    fclose(f);
    for(int i=1;i<=n;i++)
        printf("%s\n",a[i].k);
}