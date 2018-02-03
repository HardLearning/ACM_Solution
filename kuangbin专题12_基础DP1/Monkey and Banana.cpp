#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 35;
struct node{
    int x,y,z,area;
    bool operator <(const node & rhs) const {
       return area < rhs.area;
    }
}block[maxn*6];
int dp[maxn*6];
int n,tot;
int x,y,z;

inline void add_block(int x, int y, int z){
      block[tot].x = x;
      block[tot].y = y;
      block[tot].z = z;
      block[tot].area = x*y;
      tot++;
}

inline int Max(int x, int y) {
    return x>y?x:y;
}

int main(){
    int kase = 0;
    while (scanf("%d",&n)==1 && n){
        tot = 0;
        for (int i=1; i<=n; i++) {
            scanf("%d %d %d",&x,&y,&z);
            add_block(x,y,z);
            add_block(x,z,y);
            add_block(y,x,z);
            add_block(y,z,x);
            add_block(z,x,y);
            add_block(z,y,x);
        }
        sort(block,block+tot);
        int max_h = -1;
        for (int i=0; i<tot; i++) {
            dp[i] = block[i].z;
            for (int j=0; j<i; j++)
                if (block[j].x<block[i].x && block[j].y<block[i].y) dp[i] = Max(dp[i],block[i].z+dp[j]);
            max_h = Max(max_h,dp[i]);
        }

        printf("Case %d: maximum height = %d\n",++kase,max_h);
    }
    return 0;
}
