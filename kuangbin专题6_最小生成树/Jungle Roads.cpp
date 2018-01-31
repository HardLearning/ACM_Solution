#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 50;
struct edge{
   int u,v,w;
   bool operator <(const edge &rhs) const {
       return w<rhs.w;
   }
}e[maxn*maxn];
int tot,n;

inline void add_edge(int u, int v, int w){
     e[tot].u = u;
     e[tot].v = v;
     e[tot].w = w;
     tot++;
}

char s1[maxn],s2[maxn];
int num;
void init(){
    tot = 0;

    int u,v,w;
    for (int i=1; i<n; i++) {
        scanf("%s",s1);
        u = s1[0] - '0';
        scanf("%d",&num);
        for (int j=1; j<=num; j++){
            scanf("%s %d",s2,&w);
            v = s2[0]-'0';
            add_edge(u,v,w);
        }
    }
}

int fa[maxn];
int Find(int x){
    if (fa[x] == -1) return x;
    return fa[x] = Find(fa[x]);
}

int main(){
    while (scanf("%d",&n)==1 && n){
        init();
        sort(e,e+tot);
        memset(fa,-1,sizeof(fa));

        int ru,rv;
        int ans = 0;
        for (int i=0; i<tot; i++){
            ru = Find(e[i].u);
            rv = Find(e[i].v);
            if (ru!=rv) {
                ans += e[i].w;
                fa[ru] = rv;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
