#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int maxn = 1000+5;
int sx,sy,n,max_h;
struct node{
    int x1,x2,h;
    bool operator <(const node &rhs) const {
        return h>rhs.h;
    }
}a[maxn];

int dp[maxn][2];

int DFS(int id, bool isleft){
    int y = a[id].h;
    int x;
    if (isleft) x = a[id].x1; else x = a[id].x2;

    int pt=-1;
    for (int i=id+1; i<=n; i++) if (a[i].x1<=x && a[i].x2>=x) {pt = i; break; }

    if (pt==-1){
        if (y>max_h) return INF;
        else return y;
    }
    else if (y-a[pt].h>max_h) return INF;
    if (dp[pt][0] == -1) dp[pt][0] = DFS(pt,1);
    if (dp[pt][1] == -1) dp[pt][1] = DFS(pt,0);

    int left_t = y-a[pt].h+x-a[pt].x1+dp[pt][0];
    int right_t = y-a[pt].h+a[pt].x2-x+dp[pt][1];

    if (left_t>right_t) return right_t;
    return left_t;
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        scanf("%d %d %d %d",&n,&sx,&sy,&max_h);
        for (int i=1; i<=n; i++) scanf("%d %d %d",&a[i].x1,&a[i].x2,&a[i].h);
        sort(a+1,a+n+1);
        memset(dp,-1,sizeof(dp));
        a[0].x1 = sx; a[0].x2 = sx; a[0].h = sy;

        printf("%d\n",DFS(0,1));
    }
    return 0;
}
