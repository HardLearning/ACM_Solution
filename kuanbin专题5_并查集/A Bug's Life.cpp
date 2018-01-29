#include <cstdio>
using namespace std;

const int maxn = 2000+5;
int fa[maxn*2],r[maxn*2];
int n,m;

void init(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n*2; i++) fa[i] = i, r[i] = 0;
}

int Find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}

bool same(int x, int y) {return Find(x) == Find(y); }

void Merge(int x, int y){
    x = Find(x); y = Find(y);
    if (r[x]>r[y]) fa[y] = x;
    else {
        fa[x] = y;
        if (r[x] == r[y]) r[y]++;
    }
}

int main(){
    int T,kase = 0;
    scanf("%d",&T);

    while (T--){
        init();
        int a,b;
        bool flag = 1;
        for (int i=1; i<=m; i++) {
            scanf("%d %d",&a,&b);
            if (!flag) continue;
            if (same(a,b) || same(a+n,b+n)) {
                flag = 0;
                continue;
            }
            Merge(a,b+n);
            Merge(a+n,b);
        }
        printf("Scenario #%d:\n",++kase);
        if (flag) printf("No suspicious bugs found!\n");
        else printf("Suspicious bugs found!\n");
        if (T) printf("\n");
    }
    return 0;
}
