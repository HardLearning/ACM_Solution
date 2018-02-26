#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 55;
struct node{
   int l,r,x;
}a[maxn];
int n;

inline int Max(int x, int y) { return x>y?x:y; }

int main(){
    while (scanf("%d",&n)==1 && n) {
        for (int i=1; i<=n; i++) {
            scanf("%d",&a[i].x);
            a[i].l = a[i].r  = 0;

            for (int j=1; j<i; j++) a[i].l = Max(a[i].l,a[j].r-abs(a[i].x-a[j].x));
            a[i].r = a[i].l+2*a[i].x;
        }

        for (int i=1; i<=n; i++)
          for (int j=1; j<i; j++) if (a[j].r>a[i].l) {
              if (a[i].x>a[j].x) a[j].r = a[i].l;
              else a[i].l = a[j].r;
          }

        bool isFirst = 1;
        for (int i=1; i<=n; i++) {
            if (a[i].l>=a[i].r) continue;
            if (isFirst) printf("%d",i); else printf(" %d",i);
            isFirst = 0;
        }
        printf("\n");
    }
    return 0;
}
