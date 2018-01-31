#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 10000+10;
const int HASH = 10000+7;
int n,m;
int fa[maxn],parity[maxn];

inline void Swap(int &x, int &y) {
   int t = x; x = y; y = t;
}

int Find(int x){
   if (fa[x] == -1) return x;
   int tmp = Find(fa[x]);
   parity[x] ^= parity[fa[x]];
   return fa[x] = tmp;
}

struct Hash{
    int head[HASH];
    int next[maxn];
    int a[maxn];
    int sz;

    void init(){
       sz = 0;
       memset(head,-1,sizeof(head));
    }

    int push(int x){
        int h = x%HASH;
        for (int i=head[h]; i!=-1; i=next[i]) if (a[i]==x) return i;
        a[sz] = x;
        next[sz] = head[h];
        head[h] = sz;
        sz++;
        return sz-1;
    }
}mp;

int main(){
    while (scanf("%d %d",&n,&m)==2){
        memset(fa,-1,sizeof(fa));
        memset(parity,0,sizeof(parity));
        mp.init();

        int ans = m;
        int a,b;
        char str[10];
        for (int k=0; k<m; k++) {
            scanf("%d %d %s",&a,&b,str);
            if (ans < m) continue;
            if (a>b) Swap(a,b);

            a = mp.push(a-1);
            b = mp.push(b);

            int f;
            if (str[0]=='e') f = 0; else f = 1;
            int ra = Find(a);
            int rb = Find(b);

            if (ra == rb) {
                if (parity[a]^parity[b] != f) ans = k;
            }
            else {
                fa[rb] = ra;
                parity[rb] = f^parity[b]^parity[a];
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
