#include <cstdio>
#include <cstdint>

typedef uint32_t u32;
const u32 maxn = 2e7 + 2;

u32 n, a[maxn], seed;
u32 b[maxn];
inline u32 nextInteger(u32 x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

bool outputArr(void *a, u32 size) {
    if (size % 4) {
        return puts("-1"), 0;
    }

    u32 blocks = size / 4;
    u32 *A = (u32 *)a;
    u32 ret = size;
    u32 x = 23333333;
    for (u32 i = 0; i < blocks; i++) {
        ret = ret ^ (A[i] + x);
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
    }
    return printf("%u\n", ret), 1;
}

int main() {
    scanf("%d%d", &n, &seed);
    for (u32 i = 0; i < n; ++i) {
        seed = nextInteger(seed);
        a[i] = seed;
    }
    u32 cnt[256]={0};
    int exp = 0;
    for (int i=0;i<4;i++){
        u32 pre[256]={0};
        for (u32 j=0;j<n;j++){
            cnt[(a[j] >> exp)&0xFF]++;
        }
        pre[0]=cnt[0];
        for (int j=1;j<256;j++){
            pre[j]=pre[j-1]+cnt[j];
        }
        for (u32 j=0;j<n;j++){
            int k= (a[j]>>exp)&0xFF;
            b[pre[k]-cnt[k]]=a[j];
            cnt[k]--;
        }
        for (u32 j=0;j<n;j++){
            a[j]=b[j];
        }
        exp+=8;
    }
    outputArr(a, n * sizeof(u32));
    return 0;
}
/*
统计每个桶有几个->前缀和算出每段位置->扫描原数组，逐个元素看它属于哪个桶->把它放进那个桶对应的区间里
*/