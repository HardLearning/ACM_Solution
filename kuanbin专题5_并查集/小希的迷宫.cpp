#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100000+5;
int x,y;
int fa[maxn],r[maxn];
int q[maxn],cnt;
bool vis[maxn];
bool flag;

int Find(int x) {
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

void Merge(int x, int y){
    x = Find(x); y = Find(y);
    if (r[x]>r[y]) fa[y] = x;
    else {
        fa[x] = y;
        if (r[x] == r[y]) r[y]++;
    }
}

int main(){
    while (scanf("%d %d",&x,&y)==2) {
        if (x == -1 && y==-1) break;
        if (x == 0 && y == 0) {
            printf("Yes\n");
            continue;
        }
        memset(fa,-1,sizeof(fa));
        memset(r,0,sizeof(r));
        memset(vis,0,sizeof(vis));
        Merge(x,y);
        vis[x] = vis[y] = 1;
        q[1] = x; q[2] = y;
        cnt = 2;

        flag = 1;
        int rx,ry;
        while (scanf("%d %d",&x,&y)==2) {
            if (x == 0 && y ==0) break;
            rx = Find(x); ry = Find(y);
            if (rx == ry) flag = 0;
            else {
                Merge(x,y);
                if (!vis[x]) q[++cnt] = x,vis[x] = 1;
                if (!vis[y]) q[++cnt] = y,vis[y] = 1;
            }
        }

        int tot = 0;
        for (int i=1; i<=cnt; i++) if (fa[q[i]] == -1) tot++;
        if (tot>1) flag = 0;
        if (flag) printf("Yes\n"); else printf("No\n");
    }
    return 0;
}
