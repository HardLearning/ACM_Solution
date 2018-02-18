#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 5000+10;
bool flag;
int f[maxn];
int n;

int main(){
    while (scanf("%d",&n)==1){
        for (int i=1; i<=n; i++) scanf("%d",&f[i]);
        //for (int i=1; i<=n; i++) printf("%d\n",f[i]);

        flag = 0;
        for (int i=1; i<=n; i++) {
            if (f[f[f[i]]]==i) {flag = 1; break; }
        }
        if (flag) printf("YES\n"); else printf("NO\n");
    }
    return 0;
}
