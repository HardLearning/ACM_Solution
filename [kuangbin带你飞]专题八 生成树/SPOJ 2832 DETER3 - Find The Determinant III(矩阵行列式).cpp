#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int maxn = 210;
LL a[maxn][maxn];
int n;
LL p;

LL det(int n, LL p){
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
    while (scanf("%d%lld",&n,&p)==2) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) { scanf("%lld",&a[i][j]); a[i][j] %= p; }
        }
        LL ans = det(n,p);
        printf("%lld\n",ans);
    }
    return 0;
}
