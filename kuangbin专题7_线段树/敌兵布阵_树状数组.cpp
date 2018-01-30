#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 50000+10;
int n;
int c[maxn];
int x,y;

inline int lowbit(int x) { return x&(-x); }

void add(int x, int val){
     while (x<=n) {
          c[x] += val;
          x += lowbit(x);
     }
}

int sum(int x){
    int ans = 0;
    while (x) {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
        scanf("%d",&n);
        memset(c,0,sizeof(c));
        for (int i=1; i<=n; i++) {
             scanf("%d",&x);
             add(i,x);
        }
        printf("Case %d:\n",++kase);

        char str[10];
        while (scanf("%s",str)==1) {
            if (str[0]=='E') break;
            scanf("%d %d",&x,&y);

            if (str[0]=='A') add(x,y);
            else if (str[0]=='S') add(x,-y);
            else printf("%d\n",sum(y)-sum(x-1));
        }
    }
    return 0;
}
