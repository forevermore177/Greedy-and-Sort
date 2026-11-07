#include <cstddef>
#include <vector>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <algorithm>
const long long MOD=63;
const unsigned long long bas =1;
struct dynamic_bitset {
    std::vector<unsigned long long>datas;
    size_t lens = 0;
    // 默认构造函数，默认长度为0
    dynamic_bitset() = default;

    // 除非手动管理内存，否则 = default即可
    ~dynamic_bitset() = default;

    /**
     * @brief拷贝构造函数
     * 如果你用std::vector来实现，那么这个函数可以直接 = default
     * 如果你手动管理内存，则你可能需要自己实现这个函数
     */
    dynamic_bitset(const dynamic_bitset &) = default;

    /**
     * @brief拷贝赋值运算符
     * 如果你用std::vector来实现，那么这个函数可以直接 = default
     * 如果你手动管理内存，则你可能需要自己实现这个函数
     */
    dynamic_bitset &operator = (const dynamic_bitset &) = default;

    // 初始化bitset的大小为n ，且全为0.
    dynamic_bitset(std::size_t n){
        lens = n;
        size_t m=(n>>6);
        if ((n&MOD)!=0) m++;
        for (size_t i=0;i<m;i++)
            datas.push_back(0);
    }
    /**
     * @brief从一个字符串初始化bitset。
     * 保证字符串合法，且最低位在最前面。
     * 例如a =  "0010"，则有:
     * a的第0 位是0
     * a的第1 位是0
     * a的第2 位是1
     * a的第3 位是0
     */
    dynamic_bitset(const std::string &str){
        size_t pos=0;
        while (pos!=str.size()) {
            if ((pos&MOD) ==0){
                datas.push_back(0);
            }
            if (str[pos]-'0' == 1){
                datas[datas.size()-1]+=(bas << (pos&MOD));
            }
            pos++;
        }
        lens=str.size();
    }
    
    // 访问第n 个位的值，和vector一样是0-base
    bool operator [] (std::size_t n) const{
        unsigned long long num = datas[n>>6];
        if (((num >> (n&MOD))&1)==1) return true;
        return false;
    }
    // 把第n 位设置为指定值val
    dynamic_bitset &set(std::size_t n, bool val = true){
        unsigned long long &num = datas[n>>6];
        if (val){
            num|=(bas<<(n&MOD));
        }
        else {
            num&=~(bas<<(n&MOD));
        } 
        return *this;
    }
    // 在尾部插入一个位，并且长度加一
    /* 
    补充说明：这里指的是高位，
    比如0010后面push_back(1)应该变为00101
    */
    dynamic_bitset &push_back(bool val){
        if ((lens&MOD)==0){
            datas.push_back(val?bas:0ULL);
        }
        else{
            if (val)
                datas[lens>>6]|=(bas << (lens&63));
            else
                datas[lens>>6]&=(~(bas << (lens&63)));
        }
        lens++;
        return *this;
    }

    // 如果不存在1 ，则返回true。否则返回false
    bool none() const{
        size_t m = (lens >> 6);
        for (size_t i=0;i<m;i++){
            if (datas[i]!=0) return false;
        }
        if ((lens&MOD)!=0){
            if ((datas[m] & ((bas<<(lens&MOD))-1))!=0) return false;
        }
        return true;
    }       
    // 如果不存在0 ，则返回true。否则返回false
    bool all()  const{
        size_t m = (lens >> 6);
        for (size_t i=0;i<m;i++){
            if (~datas[i]!=0) return false;
        }
        if ((lens&MOD)!=0){
            if (((~datas[m]) & ((bas<<(lens&MOD))-1))!=0) return false;
        }
        return true;
    }

    // 返回自身的长度
    std::size_t size() const{
        return lens;
    }

    /**
     * 所有位运算操作均按照以下规则进行:
     * 取两者中较短的长度那个作为操作长度。
     * 换句话说，我们仅操作两者中重叠的部分，其他部分不变。
     * 在操作前后，bitset的长度不应该发生改变。
     * 
     * 比如a = "10101", b = "1100"
     * a |= b之后，a应该变成 "11101"
     * b |= a之后，b应该变成 "1110"
     * a &= b之后，a应该变成 "10001"
     * b &= a之后，b应该变成 "1000"
     * a ^= b之后，a应该变成 "01101"
     * b ^= a之后，b应该变成 "0110"
     */

    // 或操作，返回自身的引用。     a |= b 即a = a | b
    dynamic_bitset &operator |= (const dynamic_bitset &b){
        size_t newlen = std::min(lens,b.lens);
        size_t m=(newlen>>6);
        for (size_t i=0;i<m;i++){
            datas[i] |= b.datas[i];
        }
        if ((newlen&MOD)!=0){
            unsigned long long temp = b.datas[m];
            temp &= ((bas << (newlen&MOD))-1);
            datas[m] |= temp;
        }
        
        return *this;
    }
    // 与操作，返回自身的引用。     a &= b 即a = a & b
    dynamic_bitset &operator &= (const dynamic_bitset &b){
        size_t newlen = std::min(lens,b.lens);
        size_t m=(newlen>>6);
        for (size_t i=0;i<m;i++){
            datas[i] &= b.datas[i];
        }
        if ((newlen&MOD)!=0){
            unsigned long long temp = b.datas[m];
            temp |= (~((bas << (newlen&MOD))-1));
            datas[m] &= temp;
        }
        
        return *this;
    }
    // 异或操作，返回自身的引用。   a ^= b 即a = a ^ b
    dynamic_bitset &operator ^= (const dynamic_bitset &b){
        size_t newlen = std::min(lens,b.lens);
        size_t m=(newlen>>6);
        for (size_t i=0;i<m;i++){
            datas[i] ^= b.datas[i];
        }
        if ((newlen&MOD)!=0){
            unsigned long long temp = b.datas[m];
            temp &= ((bas << (newlen&MOD))-1);
            datas[m] ^= temp;
        }
        
        return *this;
    }

    /**
     * @brief左移n 位 。类似无符号整数的左移，最低位会补0.
     * 例如a = "1110"
     * a <<= 3之后，a应该变成 "0001110"
     * @return返回自身的引用
     */
    dynamic_bitset &operator <<= (std::size_t n){
        if (n==0){
            return *this;
        }
        size_t newlen = lens;
        if ((lens&MOD)!=0)
            newlen+=64-(lens&MOD);
        size_t preblock = (newlen>>6);
        newlen+=n;
        size_t m = (newlen >> 6),supple = (newlen&MOD),cur;
        if (supple!=0) m++;
        datas.resize(m,0);
        cur=m-1;
        if (supple==0){
            while (preblock!=0) {
                datas[cur]=datas[preblock-1];
                cur--;
                preblock--;
            }
            for (size_t i=0;i<=cur;i++){
                datas[i]=0;
            }
        }
        else{
            while (preblock!=0) {
                datas[cur]|=(datas[preblock-1] >> (64-supple));
                if (cur>=1){
                    cur--;
                    datas[cur]=((datas[preblock-1] & ((bas << (64-supple))-1)) << supple);
                }
                preblock--;
            }
            for (size_t i=0;i<cur;i++){
                datas[i]=0;
            }
        }
        lens=lens+n;
        
        return *this;
    }
    /**
     * @brief右移n 位 。类似无符号整数的右移，最低位丢弃。
     * 例如a = "10100"
     * a >>= 2之后，a应该变成 "100"
     * a >>= 9之后，a应该变成 "" (即长度为0)
     * @return返回自身的引用
     */
    dynamic_bitset &operator >>= (std::size_t n){
        if (n==0)
            return *this;
        if (n>=lens){
            datas.clear();
            lens=0;
            return *this;
        }
        if ((n&MOD) ==0){
            size_t j=(n>>6),st=0;
            while (j!=datas.size()){
                datas[st]=datas[j];
                st++;j++;
            }
            datas.resize(st);
        }
        else{
            size_t j=(n>>6),st=0,remain=(n&MOD);
            while (j!=datas.size()){
                datas[st]=(datas[j]>>remain);
                if (j+1!=datas.size()){
                    datas[st]+=((datas[j+1]&(bas<<remain)-1)<<(64-remain));
                    st++;
                }
                j++;
            }
            datas.resize(st+1);
        }
        lens-=n;
        
        return *this;
    }

    // 把所有位设置为1
    dynamic_bitset &set     (){
        size_t m=(lens>>6);
        for (size_t i=0;i<m;i++){
            datas[i] =(~(0ULL));
        }
        if ((lens&MOD)!=0){
            datas[m] =((bas << (lens&MOD))-1);
        }
        return *this;
    }
    
    // 把所有位取反
    dynamic_bitset &flip    (){
        size_t m=(lens>>6);
        for (size_t i=0;i<m;i++){
            datas[i] =(~datas[i]);
        }
        if ((lens&MOD)!=0){
            datas[m] =((~datas[m])&((bas<<(lens&MOD))-1));
        }
        return *this;
    }
    // 把所有位设置为0
    dynamic_bitset &reset   (){
        size_t m=(lens>>6);
        for (size_t i=0;i<m;i++){
            datas[i] =0;
        }
        if ((lens&MOD)!=0){
            datas[m] =0;
        }
        return *this;
    }
};
