#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long int LL;
const int maxn = 65;
LL b[maxn][maxn];
bool v[maxn][maxn];
int n,m,K;

LL det(int n) {
    LL ans = 1;
    bool flag;

    for (int i=1; i<=n; i++) {
        if (!b[i][i]) {
            flag = 0;
            for (int j=i+1; j<=n; j++) if (b[j][i]) {
                flag  = 1;
                for (int k=i; k<n; k++) swap(b[i][k],b[j][k]);
                ans = -ans;
                break;
            }
            if (!flag) return 0;
        }

        for (int j=i+1; j<=n; j++) {
            while (b[j][i]) {
                LL t = b[i][i]/b[j][i];
                for (int k=i; k<=n; k++) {
                    b[i][k] -= t*b[j][k];
                    swap(b[i][k],b[j][k]);
                }
                ans = -ans;
            }
        }
        ans *= b[i][i];
    }
    return ans;
}

int main(){
    while (~scanf("%d%d%d",&n,&m,&K)){
        memset(v,1,sizeof(v));
        memset(b,0,sizeof(b));

        int x,y;
        for (int i=0; i<m; i++) {
           scanf("%d%d",&x,&y);
           v[x][y] = v[y][x] = 0;
        }

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) if (v[i][j] && i!=j) {
                b[i][i]++;
                b[i][j] = -1;
            }
        }

        LL ans = det(n-1);
        printf("%lld\n",ans);
    }
    return 0;
}
