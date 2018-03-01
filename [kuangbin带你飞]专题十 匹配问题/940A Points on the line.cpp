#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100+5;
int n,d;
int a[maxn];
int cnt;

int main(){
    while (scanf("%d%d",&n,&d)==2){
        for (int i=1; i<=n; i++) scanf("%d",&a[i]);
        sort(a+1,a+n+1);

        cnt = 0;
        for (int i=1; i<=n; i++) {
            for (int j=i; j<=n; j++) if (a[j]-a[i]<=d) cnt = max(cnt,j-i+1);
        }
        printf("%d\n",n-cnt);
    }
    return 0;
}
