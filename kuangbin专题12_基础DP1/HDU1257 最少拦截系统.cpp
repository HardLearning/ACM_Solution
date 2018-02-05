#include <cstdio>
#include <cstring>
using namespace std;

const int maxn  =30000+10;
int h[maxn];
int tot,n;
bool flag;
int x;

int main(){
    while (scanf("%d",&n)==1) {
        memset(h,0,sizeof(h));
        tot = 0;
        for (int i=1; i<=n; i++) {
            flag = 0;
            scanf("%d",&x);
            for (int j=1; j<=tot; j++) {
                if (h[j]>=x) {
                    flag = 1;
                    h[j] = x;
                    break;
                }
            }
            if (!flag) {
                tot++;
                h[tot] = x;
            }
        }
        printf("%d\n",tot);
    }
    return 0;
}
