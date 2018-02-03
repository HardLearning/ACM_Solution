#include <cstdio>
using namespace std;

const int maxn = 1e6+10;
int n,m;
int a[maxn],pre[maxn];

inline int Max(int x, int y) { return x>y?x:y; }
int main(){
    while (scanf("%d %d",&m,&n)==2){
        for (int i=1; i<=n; i++) {
            scanf("%d",&a[i]);
            pre[i] = 0;
        }

        int p ;
        for (int i=1; i<=m; i++) {
            p = 0;
            for (int j=1; j<=i; j++) p += a[j];
            pre[n] = p;

            for (int j=i+1; j<=n; j++) {
                p = Max(pre[j-1],p) + a[j];
                pre[j-1] = pre[n];
                pre[n] = Max(pre[n],p);
            }
        }
        printf("%d\n",pre[n]);
    }
    return 0;
}
