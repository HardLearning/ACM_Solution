#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
vector<LL> G;
LL n,d;

void init(LL n){
   G.clear();
   for (LL i=1; i*i<=n; i++) if (n%i==0) {
       G.push_back(i);
       if ((n/i)>d && i*i<n) G.push_back(n/i);
   }
}

int main(){
    while (scanf("%I64d%I64d",&n,&d)==2){
        if (n==d) {
            if (n<=1) printf("2 1\n");
            else printf("%I64d 1\n",n+1);
            continue;
        }
        if (n<d)  { printf("2 0\n"); continue; }

        init(n-d);
        LL k = 2, r = 0;
        for (int i=1; i<G.size(); i++) {
            LL t = n;
            int sum = 0;
            while (t) {
                if (t%G[i]!=d) break;
                else {
                    t /= G[i];
                    sum++;
                }
            }

            if (sum>r) { k = G[i]; r = sum; }
            else if (sum == r && k>G[i]) {k = G[i]; }
        }
        printf("%I64d %I64d\n",k,r);
    }
    return 0;
}
