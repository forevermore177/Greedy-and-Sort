#include <iostream>
#include <vector>
using ll =unsigned long long;

int n,k;
ll arr[100001];
ll Cyrene_operation();

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;std::cin>>t;
    for (int i=0;i<t;i++){
        std::cout<<Cyrene_operation()<<"\n";
    }
}
ll Cyrene_operation(){
    std::cin>>n>>k;
    std::vector<int>preidx;
    for (int i=0;i<n;i++){
        std::cin>>arr[i];
        preidx.push_back(i);
    }
    std::vector<int>idx;
    ll ans=0;
    for (int level = 60;level>=0;level--){
        for (auto it = preidx.begin();it!=preidx.end();it++){
            if (((arr[*it]>>level)&1)==1){
                idx.push_back(*it);
            }
        }
        if (idx.size()<k){
            idx.clear();
        }
        else if (idx.size()==k) {
            ans=arr[idx[0]];
            for (int j=1;j<idx.size();j++){
                ans&=arr[idx[j]];
            }
            return ans;
        }
        else{
            preidx=idx;
            idx.clear();
        }
    }
    if (preidx.size()>k){
        ans=arr[preidx[0]];
        for (int j=1;j<k;j++){
                ans&=arr[preidx[j]];
        }
    }
    return ans;
}
