//队列中存放长度≧1的区间，否则不会再被调用
//注意到左半区间长度不大于右半区间
#include <iostream>
struct interval{
    int l,r;
};
int ans[100001];
void swaplr(interval target){
    int l=target.l,r=target.r;
    int mid = (r-l)/2+l;
    int i=l,j=mid,st=l;
    for (int pos=l;pos!=mid;pos++){
        int temp=ans[pos+mid-l];
        ans[pos+mid-l]=ans[pos];
        ans[pos]=temp;
    }
}
int main(){
    int n,k;std::cin>>n>>k;
    if (k%2==0 || k>2*n-1){
        std::cout<<-1;
        return 0;
    }
    for (int i=0;i<n;i++)
        ans[i]=i+1;
    interval arr[200001];
    int head=0,tail=1,dot=1;
    arr[0]={0,n};
    while(dot<k){
        int mid=arr[head].l+(arr[head].r-arr[head].l)/2;
        if (mid>arr[head].l+1){
            arr[tail]={arr[head].l,mid};tail++;
        }
        if (arr[head].r>mid+1){
            arr[tail]={mid,arr[head].r};tail++;
        }
        swaplr(arr[head]);
        dot+=2;
        head++;
    }
    for (int i=0;i<n;i++){
        std::cout<<ans[i]<<" ";
    }
}