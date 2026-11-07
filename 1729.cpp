#include<cstring>
#include <string>
using namespace std;

void Init(char **&p,int n){//初始化，n为string的个数,传入的p指向nullptr
    p=new char*[n+1];
    for (int i=1;i<=n;i++){
        p[i]=new char[1];
        p[i][0]='\0';
    }
}
void Assign_String(char **&p,int x,std::string str){//将str赋值给第x个string
    delete [] p[x];
    p[x]=new char[str.size()+1];
    for (int i=0;i<str.size();i++){
        p[x][i]=str[i];
    }
    p[x][str.size()]='\0';
}
void Merge_String(char **&p,int x,int y,int z){//把第y个string拼接到第x个string后面，赋给第z个string(x,y,z互不相等) (第x和y个string不变)
    delete [] p[z];
    int cnt=strlen(p[x])+strlen(p[y])+1;
    p[z]=new char[cnt];
    int pos=0;
    while (p[x][pos]!='\0'){
        p[z][pos]=p[x][pos];
        pos++;
    }
    for (int i=0;p[y][i]!='\0';i++){
        p[z][pos]=p[y][i];
        pos++;
    }
    p[z][pos]='\0';
}
void Double_String(char **&p,int x){//把第x个string复制两遍前后拼接起来，再赋给第x个string
    int cnt=strlen(p[x]);
    char *temp=new char[2*cnt+1];
    for (int i=0;i<cnt;i++){
        temp[i]=p[x][i];
        temp[i+cnt]=p[x][i];
    }
    temp[2*cnt]='\0';
    delete []p[x];
    p[x]=temp;
}
char* Get_String(char **&p,int x){//返回第x个string
    return p[x];
}
void Clear(char **&p,int n){//回收空间
    for (int i=1;i<=n;i++){
        delete [] p[i];
    }
    delete [] p;
}