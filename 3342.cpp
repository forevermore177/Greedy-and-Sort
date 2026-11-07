// $$\Leftrightarrow \color{red}\text{min}(a_i,b_j)\leq\text{min}(a_j,b_i)$$
#include <iostream>
#include <algorithm>
using ll =long long;
int n;
struct task{
    ll a,b;
    bool operator < (const task &another) const{
        if (std::min(a,another.b)==std::min(b,another.a)){
            if (a!=another.a) return a<another.a;
            else return b<another.b;
        }
        else
            return std::min(a,another.b)<std::min(b,another.a);
    }
};
task arr[20001],temp[20001];
ll presum[20001];
void mergesort(const int &st,const int &mid,const int &ed){
    int i=st,j=mid+1,pos=st;
    while (i<=mid && j<=ed){
        if (arr[i] < arr[j]){
            temp[pos++]=arr[i++];
        }
        else{
            temp[pos++]=arr[j++];
        }
    }
    while (i<=mid){
        temp[pos++]=arr[i++];
    }
    while (j<=ed){
        temp[pos++]=arr[j++];
    }
    for (int i=st;i<=ed;i++){
        arr[i]=temp[i];
    }
}
void conquersort(const int &st,const int &ed){
    if (ed<=st) return;
    int mid=st+(ed-st)/2;
    conquersort(st,mid);
    conquersort(mid+1,ed);
    mergesort(st,mid,ed);
}
ll dispatch(){
    std::cin>>n;
    for (int i=0;i<n;i++){
        std::cin>>arr[i].a>>arr[i].b;
    }
    conquersort(0,n-1);
    presum[0]=arr[0].a;
    for (int i=1;i<n;i++){
        presum[i]=presum[i-1]+arr[i].a;
    }
    ll ans = arr[0].a+arr[0].b;
    for (int i=1;i<n;i++){
        ans=std::max(ans,presum[i])+arr[i].b;
    }
    return ans;
}
int main(){
    int T;
    std::cin>>T;
    for (int i=0;i<T;i++){
        std::cout<<dispatch()<<'\n';
    }
}