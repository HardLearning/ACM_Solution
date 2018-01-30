#include <cstdio>
using namespace std;

const int maxn = 1e4+10;
bool vis[maxn],flag;
int fa[maxn];
int x,y;

int main(){
    int kase = 0;
    while (scanf("%d %d",&x,&y) && x>0 && y>0) {
        for (int i=1; i<maxn; i++) fa[i] = i,vis[i] = 0;
        vis[x] = vis[y] = 1;
        fa[y] = x;

        flag = 1;
        while (scanf("%d %d",&x,&y)==2 &&x+y){
             if (!flag) continue;
             vis[x] = vis[y] = 1;
             if (fa[y]==y) fa[y] = x; else flag = 0;
        }

        if (flag) {
            int tot = 0;
            for (int i=1; i<maxn; i++) if (vis[i] &&fa[i]==i) tot++;
            if (tot!=1) flag = 0;
        }
        if (flag) printf("Case %d is a tree.\n",++kase);
        else printf("Case %d is not a tree.\n",++kase);
    }
    return 0;
}
