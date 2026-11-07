#include <iostream>
using ll = long long;
const int maxn = 100001;
bool judge(){
    int n;std::cin>>n;
    std::string s1,s2;
    std::cin>>s1>>s2;
    bool state1[maxn],state2[maxn];
    for (int i=0;i<maxn;i++){
        state1[i]=state2[i]=true;
    }
    if (s1[0] == '1' && s2[0] == '1'){
        if (s1[1]!='0' || s2[1]!= '0')
            return false;
        state1[0]=state1[1]=state2[0]=state2[1]=false;
    }
    else if (!(s1[0]=='0' && s2[0]=='0')) {
        state1[0]=state2[0]=false;
    }
    for (int i=1;i<n;i++){
        if (s1[i]=='1' && s2[i]=='1'){
            if (!state1[i-1]){
                if (i+1>=n || s1[i+1] == '1') return false;
                state1[i]=state1[i+1]=false;
            }
            else
                state1[i]=false;
            if (!state2[i-1]){
                if (i+1>=n || s2[i+1] == '1') return false;
                state2[i]=state2[i+1]=false;
            }
            else
                state2[i]=false;
        }
        else if (s1[i]=='1' && s2[i]=='0'){
            if (state1[i-1])
                state1[i]=false;
            else if (state2[i]) 
                state2[i]=state1[i]=false;
            else{
                if (i+1>=n || s1[i+1]=='1') return false;
                state1[i+1]=false;
            }
        }
        else if (s1[i]=='0' && s2[i]=='1'){
            if (state2[i-1])
                state2[i]=false;
            else if (state1[i])
                state1[i]=state2[i]=false;
            else{
                if (i+1>=n || s2[i+1]=='1') return false;
                state2[i+1]=false;
            }
        }
    }
    return true;
}
int main(){
    ll T;
    std::cin>>T;
    for (int i=0;i<T;i++){
        std::cout<<(judge()?"Yes":"No")<<"\n";
    }
}