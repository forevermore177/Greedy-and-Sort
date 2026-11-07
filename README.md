## 3342
先考虑开头：
$$
T_{i,j}=\text{max}(a_i+b_i,a_i+a_j)+b_j;T_{j,i}=\text{max}(a_j+b_j,a_j+a_i)+b_i. \\
T_{i,j}\leq T_{j,i}\Leftrightarrow a_i+\text{max}(b_i,a_j)+b_j\leq a_j+\text{max}(b_j,a_i)+b_i.\\
\text{use max}(x,y)=x+y-\text{min}(x,y);\\
\Leftrightarrow \color{red}\text{min}(a_i,b_j)\leq\text{min}(a_j,b_i)
$$

### 事实上猜测成立：
假设在这两个任务开始之前：
- 机器 1 刚刚空闲下来，当前时间是 \(t_1\)
- 机器 2 开工可用时间是 \(t_2\)

#### 场景 A：先 \(i\) 后 \(j\) (\(i \to j\))
*   机器 1 加工 \(i\) 完成时间：\(t_1 + a_i\)
*   机器 1 加工 \(j\) 完成时间：\(t_1 + a_i + a_j\)
*   机器 2 开始加工 \(i\) 的时间：\(\max(t_1 + a_i, t_2)\)
*   机器 2 加工完 \(i\) 的时间：\(\max(t_1 + a_i, t_2) + b_i\)
*   **机器 2 加工完 \(j\) 的时间**（也就是这两个任务的总完成时间）：
    \(C_{i \to j} = \max \Big( t_1 + a_i + a_j, \ \max(t_1 + a_i, t_2) + b_i \Big) + b_j\)

\[
C_{i \to j} = \max \Big( t_1 + a_i + a_j + b_j, \ \max(t_1 + a_i + b_i + b_j, \ t_2 + b_i + b_j) \Big)
\]
展开：
\[
C_{i \to j} = \max \Big( t_1 + a_i + a_j + b_j, \quad t_1 + a_i + b_i + b_j, \quad t_2 + b_i + b_j \Big)
\]

#### 场景 B：先 \(j\) 后 \(i\) (\(j \to i\))
同理，把上面公式里的 \(i\) 和 \(j\) 互换，得到：
\[
C_{j \to i} = \max \Big( t_1 + a_j + a_i + b_i, \quad t_1 + a_j + b_j + b_i, \quad t_2 + b_j + b_i \Big)
\]

只需要比较：
**集合 A**：\(\{ a_i+a_j+b_j, \ a_i+b_i+b_j \}\)
**集合 B**：\(\{ a_j+a_i+b_i, \ a_j+b_j+b_i \}\)

减掉公共：**\(a_i + a_j + b_i + b_j\)**
*   集合 A 剩下：\(\max(-b_i, -a_j)\)
*   集合 B 剩下：\(\max(-b_j, -a_i)\)

根据 \(\max(-x, -y) = -\min(x, y)\)，等价于比较：
*   集合 A：\(-\min(b_i, a_j)\)
*   集合 B：\(-\min(b_j, a_i)\)

$$\Leftrightarrow \color{red}\text{min}(a_i,b_j)\leq\text{min}(a_j,b_i)$$

### Failed
```cpp
struct task{
    ll a,b;
    bool operator < (const task &another) const{
        return std::min(a,another.b)<std::min(b,another.a);
    }
};
```
不具有传递性
### Correct
```cpp
    bool operator < (const task &another) const{
        if (std::min(a,another.b)==std::min(b,another.a)){
            if (a!=another.a) return a<another.a;
            else return b<another.b;
        }
        else
            return std::min(a,another.b)<std::min(b,another.a);
    }
```
标准答案：
分两组：
第一组：a <= b，放在前面；组内按 a 从小到大 排序。
第二组：a > b，放在后面；组内按 b 从大到小 排序。
最后把第一组和第二组直接拼接：第一组 + 第二组。