#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 2e5+5;
vector<int> v[maxn];
char s[maxn];
int n,tot,maxx;

int main(){
    scanf("%s",s+1); n = strlen(s+1);
    maxx = 0; tot = 0;
    for (int i=1; i<=n; i++){
        if (s[i]=='0') v[++tot].push_back(i);
        else {
            v[tot].push_back(i);
            tot--;
            if (tot<0)  { printf("-1\n"); return 0; }
        }
        maxx = max(maxx,tot);
    }
    if (maxx>tot) printf("-1\n");
    else {
        printf("%d\n",maxx);
        for (int i=1; i<=maxx; i++){
            printf("%d",v[i].size());
            for (int k=0; k<v[i].size(); k++) printf(" %d",v[i][k]);
            printf("\n");
        }
    }
    return 0;
}
