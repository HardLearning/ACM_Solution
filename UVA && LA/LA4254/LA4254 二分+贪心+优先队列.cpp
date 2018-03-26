#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int maxn = 10000+10;
struct node{
   int r,d,w;
   node () {}
   node (int r, int d, int w): r(r) , d(d) , w(w) {}
   bool operator <(const node &rhs) const {
       return d>rhs.d;
   }
}a[maxn];
int n;
int minr,maxd,sumw;

bool cmp(node a, node b) { return a.r<b.r || a.r==b.r && a.d<b.d; }

priority_queue<node>que;

inline int Max(int x, int y) {return x>y?x:y; }
inline int Min(int x, int y) {return x<y?x:y; }

bool judge(int mid){
   while (!que.empty()) que.pop();
   int idx = 1;
   int tmp;
   for (int i=minr; i<=maxd; i++) {
       while (idx<=n && a[idx].r<i) que.push(a[idx++]);
       tmp = mid;
       while (!que.empty() && tmp>0) {
           node now = que.top(); que.pop();
           if (now.d<i) return 0;
           if (tmp>=now.w) tmp -= now.w;
           else {
               now.w -= tmp;
               que.push(now);
               tmp = 0;
           }
       }
   }
   return que.empty();
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        int r,d,w;
        minr = INF;  maxd = 0; sumw = 0;
        for (int i=1; i<=n; i++) {
            scanf("%d%d%d",&r,&d,&w);
            a[i] = node(r,d,w);
            minr = Min(minr,r);
            maxd = Max(maxd,d);
            sumw += w;
        }
        sort(a+1,a+n+1,cmp);

        int left = 1, right = sumw;
        int mid , ans = 0;
        while (left<=right) {
            mid = (left+right)>>1;
            if (judge(mid)) {right = mid-1; ans = mid;}
            else left = mid+1;
        }

        printf("%d\n",ans);
    }
    return 0;
}
