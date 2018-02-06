#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long LL;
int x,p,k;
vector<int>factor;

void get_factor(int p){
    factor.clear();
    int tmp = p;
    for (int i=2; i*i<=tmp; i++) {
        if (tmp%i==0) {
            factor.pb(i);
            while (tmp%i==0) tmp /= i;
        }
    }
    if (tmp!=1) factor.pb(tmp);
}

bool judge(int num){
    int res = 0;
    int sz = factor.size();
    for (int i=1; i<(1<<sz); i++) {
        int v = __builtin_popcount(i);
        LL mul = 1;
        for (int j=0; j<sz; j++) {
            if ((i>>j)&1) mul *= factor[j];
        }
        res += ((v&1)?1:-1)*(num/mul-x/mul);
    }
    res = num - x - res;
    return res >= k;
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        scanf("%d %d %d",&x,&p,&k);
        get_factor(p);

        int left = x+1, right = 1e9, mid;
        while (left<right) {
            mid = (left+right)>>1;
            if (judge(mid)) right = mid;
            else left = mid+1;
        }
        printf("%d\n",right);
    }
    return 0;
}
