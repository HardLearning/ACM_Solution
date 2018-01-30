#include <cstdio>
using namespace std;

const int maxn = 50000+5;
int n,q;
int h[maxn];
int fmax[maxn][20],fmin[maxn][20];

inline int Max(int x, int y) { return x>y?x:y; }
inline int Min(int x, int y) { return x<y?x:y; }

void RMQ_init(){
    for (int i=0; i<n; i++) fmax[i][0] = fmin[i][0] = h[i];
    for (int j=1; (1<<j)<=n; j++) {
        for (int i=0; i+(1<<j)<=n; i++) {
            fmax[i][j] = Max(fmax[i][j-1],fmax[i+(1<<(j-1))][j-1]);
            fmin[i][j] = Min(fmin[i][j-1],fmin[i+(1<<(j-1))][j-1]);
        }
    }
}

int RMQ(int L, int R){
   int k = 0;
   while ((1<<(k+1)) <= R-L+1) k++;
   int mn = Min(fmin[L][k],fmin[R-(1<<k)+1][k]);
   int mx = Max(fmax[L][k],fmax[R-(1<<k)+1][k]);
   return mx-mn;
}

int main(){
    while (scanf("%d %d",&n,&q)==2){
        for (int i=0; i<n; i++) scanf("%d",&h[i]);
        RMQ_init();

        int a,b;
        while (q--){
           scanf("%d %d",&a,&b);
           printf("%d\n",RMQ(a-1,b-1));
        }
    }
    return 0;
}
