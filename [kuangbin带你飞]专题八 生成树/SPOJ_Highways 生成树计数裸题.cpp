#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 20;
typedef long long LL;
LL mat[maxn][maxn];
int n,m;

LL det(int n){
   LL ret = 1;
   bool flag;
   for (int i=1; i<=n; i++) {
      if (mat[i][i]==0) {
          flag = 0;
          for (int j=i+1; j<=n; j++) if (mat[j][i]) {
              flag = 1;
              for (int k=i; k<=n; k++) swap(mat[i][k],mat[j][k]);
              ret = -ret;
              break;
          }
          if (flag == 0) return 0;
      }

      for (int j=i+1; j<=n; j++) {
          while (mat[j][i]) {
              LL t = mat[i][i]/mat[j][i];
              for (int k=i; k<=n; k++) {
                  mat[i][k] -= t*mat[j][k];
                  swap(mat[i][k],mat[j][k]);
              }
              ret = -ret;
          }
      }

      ret *= mat[i][i];
   }
   return ret;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
       memset(mat,0,sizeof(mat));
       scanf("%d%d",&n,&m);

       int x,y;
       while (m--){
          scanf("%d%d",&x,&y);
          if (x==y) continue;
          mat[x][x]++;
          mat[y][y]++;
          mat[x][y] = mat[y][x] = -1;
       }

       LL ans = det(n-1);
       printf("%lld\n",ans);
    }
    return 0;
}
