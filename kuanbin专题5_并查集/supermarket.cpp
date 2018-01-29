#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 10000+5;
int n;
struct node{
   int p,d;
   bool operator <(const node &rhs) const {
       return p>rhs.p;
   }
}a[maxn];
int fa[maxn];

void init(){
    for (int i=1; i<=n; i++) scanf("%d %d",&a[i].p,&a[i].d);
    memset(fa,-1,sizeof(fa));
}

int Find(int x) {
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

int main(){
    while (scanf("%d",&n)==1) {
        init();
        sort(a+1,a+n+1);
        int ans = 0;
        for (int i=1; i<=n; i++) {
             int fd = Find(a[i].d);
             if (fd>0){
                ans+=a[i].p;
                fa[fd] = fd-1;
             }
        }
        printf("%d\n",ans);
    }
    return 0;
}
