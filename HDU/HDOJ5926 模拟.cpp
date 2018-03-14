#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 40;
int a[maxn][maxn];
int n,m;
bool flag;

bool Find(){
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (i<n && a[i][j]==a[i+1][j]) return 1;
            if (j<m && a[i][j]==a[i][j+1]) return 1;
        }
    }

    for (int i=1; i<=m; i++) {
        for (int j=i+1; j<=m; j++) if (a[1][i]==a[1][j] || a[n][i]==a[n][j]) return 1;
    }

    for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=n; j++) if (a[i][1]==a[j][1] || a[i][m]==a[j][m]) return 1;
    }

    return 0;
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
        scanf("%d%d",&n,&m);
        for (int i=1; i<=n; i++)
           for (int j=1; j<=m; j++) scanf("%d",&a[i][j]);
        if (Find()) printf("Case #%d: Yes\n",++kase);
        else printf("Case #%d: No\n",++kase);
    }
    return 0;
}
