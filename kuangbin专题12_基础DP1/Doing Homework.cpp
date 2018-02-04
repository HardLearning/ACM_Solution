#include <cstdio>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int maxn = 16;
struct node {
   char name[100+5];
   int ddl,cost;
}a[20];
int n;
int dp[1<<maxn];
int pre[1<<maxn];

void Print(int x){
    if (x==0) return;
    int i;
    for (i=0; i<n; i++) if ((x&(1<<i)) && (pre[x]&(1<<i))==0) break;
    Print(pre[x]);
    printf("%s\n",a[i].name);
}

inline int Max(int x, int y) { return x>y?x:y; }
int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        scanf("%d",&n);
        for (int i=0; i<n; i++) scanf("%s%d%d",a[i].name,&a[i].ddl,&a[i].cost);
        for (int i=0; i<(1<<n); i++) dp[i] = INF,pre[i] = 0;
        dp[0] = 0;

        for (int i=0; i<(1<<n); i++) {
             int cur_cost = 0;
             for (int k=0; k<n; k++) if (i&(1<<k)) cur_cost += a[k].cost;

             for (int j=0; j<n; j++) {
                if (i&(1<<j)) continue;
                int tmp = cur_cost + a[j].cost - a[j].ddl;
                tmp = Max(tmp,0);

                if (dp[i|(1<<j)]>dp[i]+tmp) {
                     dp[i|(1<<j)] = dp[i] + tmp;
                     pre[i|(1<<j)] = i;
                }
             }
        }

        printf("%d\n",dp[(1<<n)-1]);
        Print((1<<n)-1);
    }
    return 0;
}
