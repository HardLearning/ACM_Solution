#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 2000+5;
char s[maxn][maxn];
int n,m,k;
int ans;

int main(){
    while (scanf("%d %d %d",&n,&m,&k)==3){
        for (int i=0; i<n; i++) scanf("%s",s[i]);
        ans = 0;

        for (int i=0; i<n; i++) {
            int num = 0;
            for (int j=0; j<m; j++) {
                if (s[i][j]=='.') num++;
                else {
                    num = num - k+1;
                    if (num>0) ans+=num;
                    num = 0;
                }
            }
            num = num - k + 1;
            if (num>0) ans += num;
        }

        if (k == 1) {
            printf("%d\n",ans);
            continue;
        }

        for (int i=0; i<m; i++) {
            int num = 0;
            for (int j=0; j<n; j++) {
                if (s[j][i]=='.') num++;
                else {
                    num = num - k + 1;
                    if (num>0) ans += num;
                    num = 0;
                }
            }
            num = num - k + 1;
            if (num>0) ans += num;
        }
        printf("%d\n",ans);
    }
    return 0;
}
