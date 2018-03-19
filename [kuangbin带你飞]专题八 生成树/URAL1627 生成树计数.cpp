#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const LL p = 1000000000;
const int maxm = 15;
const int maxn = 100;
char s[maxm][maxm];
int idx[maxm][maxm],tot;
int n,m;

int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};

bool v[maxn][maxn];
LL a[maxn][maxn];

void add(int x, int y) {
   int tx,ty;
   for (int i=0; i<4; i++) {
      tx = x+dx[i];
      ty = y+dy[i];
      if (tx<0 || tx>=n || ty<0 || ty>=m) continue;
      if (s[tx][ty]=='*') continue;
      a[idx[x][y]][idx[x][y]]++;
      a[idx[x][y]][idx[tx][ty]] = -1;
   }
}

LL det(int n){
   LL ans = 1;
   bool flag;

   for (int i=1; i<=n; i++) {
       if (!a[i][i]) {
           flag = 0;
           for (int j=i+1; j<=n; j++) if (a[j][i]) {
              flag = 1;
              for (int k=i; k<=n; k++) swap(a[i][k],a[j][k]);
              ans = -ans;
              break;
           }
           if (!flag) return 0;
       }

       for (int j=i+1; j<=n; j++) {
          while (a[j][i]) {
              LL t = a[i][i]/a[j][i];
              for (int k=i; k<=n; k++) {
                 a[i][k] -= t*a[j][k];
                 a[i][k] %= p;
                 swap(a[i][k],a[j][k]);
              }
              ans = -ans;
          }
       }
       ans *= a[i][i];
       ans %= p;
   }
   return (ans+p)%p;
}

int main(){
    while (scanf("%d%d",&n,&m)==2) {
        for (int i=0; i<n; i++) scanf("%s",s[i]);
        tot = 0;
        memset(idx,-1,sizeof(idx));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) if (s[i][j]=='.') {
                idx[i][j] = tot++;
            }
        }

        memset(a,0,sizeof(a));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) if (s[i][j]=='.') {
                add(i,j);
            }
        }

        LL ans = det(tot-1);
        printf("%I64d\n",ans);
    }
    return 0;
}
