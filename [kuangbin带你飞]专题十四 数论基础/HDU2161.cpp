#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int maxn = 16000+10;
bool isprime[maxn];

void get_prime(){
    memset(isprime,1,sizeof(isprime));
    int m = sqrt(maxn+0.5);
    for (int i=2; i<=m; i++) if (isprime[i]) {
        for (int j=i+i; j<maxn; j+=i) isprime[j] = 0;
    }
    isprime[2] = isprime[1] = 0;
}

int main(){
    int x;
    int kase = 0;
    get_prime();
    while (scanf("%d",&x)==1) {
        if (x<=0) break;
        kase++;
        if (isprime[x]) printf("%d: yes\n",kase);
        else printf("%d: no\n",kase);
    }
    return 0;
}
