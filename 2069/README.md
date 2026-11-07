## 细节与坑
1. 位运算中1按int计，1<<40❌ 应当1ULL
2. &运算中应先取掩码，避免高位0干扰（故应当把高位转成1）！（其实｜和^不会，但保险起见，可以先把高位变成0）
手段：~(1 << k)|原先（低位）
3. 
> 
```cpp
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
```
4. flip()有坑！如果先与掩码再取反，会导致高位都变成1！
5. 全1爆上限$\Rightarrow$`~(0ULL)`