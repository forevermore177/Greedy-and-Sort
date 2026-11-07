#include <iostream>
using namespace std;
int b[1000];int n;

int main(){
    cin>>n;
    int a[1000],idx[1000];
    for (int i=0;i<n;i++){
        cin>>a[i];
    }
    int cnt[256]={0};
    int exp = 0;
    for (int i=0;i<4;i++){
        int pre[256]={0};
        for (int j=0;j<n;j++){
            cnt[(a[j] >> exp)&0xFF]++;
        }
        pre[0]=cnt[0];
        for (int j=1;j<256;j++){
            pre[j]=pre[j-1]+cnt[j];
        }
        for (int j=0;j<n;j++){
            int k= (a[j]>>exp)&0xFF;
            b[pre[k]-cnt[k]]=a[j];
            cnt[k]--;
        }
        for (int j=0;j<n;j++){
            a[j]=b[j];
        }
        exp+=8;
    }
    for (int i=0;i<n;i++)
        cout<<a[i]<<" ";
}