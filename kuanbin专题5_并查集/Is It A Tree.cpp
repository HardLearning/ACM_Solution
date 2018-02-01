#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1e4+10;
int fa[maxn];
int que[maxn],tot;
int in[maxn];
bool vis[maxn];

void init(){
   memset(in,0,sizeof(in));
   memset(fa,-1,sizeof(fa));
   memset(vis,0,sizeof(vis));
   tot = 0;
}

int Find(int x){
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

void Merge(int x, int y){
   x = Find(x); y = Find(y);
   if (x!=y) fa[y] = x;
}

int main(){
    int a,b;
    int ra,rb;

    int kase = 0;
    while (scanf("%d %d",&a,&b)==2){
        if (a==-1 && b==-1) break;
        if (a==0 && b==0) {
            printf("Case %d is a tree.\n",++kase);
            continue;
        }

        init();
        in[b] = 1;
        Merge(a,b);
        if (!vis[a]) { que[tot++] = a; vis[a] = 1; }
        if (!vis[b]) { que[tot++] = b; vis[b] = 1; }

        bool flag = 1;
        while (scanf("%d %d",&a,&b)==2 && a+b){
              if (!flag) continue;
              ra = Find(a); rb = Find(b);
              if (ra == rb) { flag = 0; continue; }
              Merge(a,b);
              if (!vis[a]) { que[tot++] = a; vis[a] = 1; }
              if (!vis[b]) { que[tot++] = b; vis[b] = 1; }
              in[b]++;
        }

        if (flag) {
            int sum = 0; //the number of root
            for (int i=0; i<tot; i++) {
                if (Find(que[i]) != Find(que[0])) { flag = 0; break; }
                if (in[que[i]] > 1) { flag = 0; break;}
                if (in[que[i]] == 0) sum++;
            }
            if (sum!=1) flag = 0;
        }

        if (flag) printf("Case %d is a tree.\n",++kase);
        else printf("Case %d is not a tree.\n",++kase);
    }
    return 0;
}
