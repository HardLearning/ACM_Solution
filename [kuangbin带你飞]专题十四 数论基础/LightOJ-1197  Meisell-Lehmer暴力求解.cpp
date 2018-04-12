#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int maxn = 4e5+10;
typedef long long LL;
LL A,B;
bool np[maxn];
int prime[maxn],pi[maxn];

int getprime() {
    int cnt = 0;
    np[0] = np[1] = 1;
    pi[0] = pi[1] = 0;
    for (int i=2; i<maxn; i++) {
        if (!np[i]) prime[++cnt] = i;
        pi[i] = cnt;
        for (int j=1; j<=cnt && i*prime[j]<maxn; j++) {
            np[i*prime[j]] = 1;
            if (i%prime[j]==0) break;
        }
    }
    return cnt;
}

const int M = 7;
const int PM = 2*3*5*7*11*13*17;
int phi[PM+1][M+1],sz[M+1];
void init(){
    getprime();
    sz[0] = 1;
    for (int i=0; i<=PM; i++) phi[i][0] = i;
    for (int i=1; i<=M; i++) {
        sz[i] = prime[i]*sz[i-1];
        for (int j=1; j<=PM; j++) phi[j][i] = phi[j][i-1]-phi[j/prime[i]][i-1];
    }
}

int sqrt2(LL x) {
    LL r = (LL)sqrt(x-0.1);
    while (r*r<=x) r++;
    return int(r-1);
}

int sqrt3(LL x) {
    LL r = (LL)sqrt(x-0.1);
    while (r*r*r<=x) r++;
    return int(r-1);
}

LL getphi(LL x, int s) {
   if (s == 0) return x;
   if (s <= M) return phi[x%sz[s]][s] + (x/sz[s])*phi[sz[s]][s];
   if (x <= prime[s]*prime[s]) return pi[x]-s+1;
   if (x <= prime[s]*prime[s]*prime[s] && x<maxn) {
       int tmp = pi[sqrt2(x)];
       LL ans = pi[x] - (tmp+s-2)*(tmp-s+1)/2;
       for (int i=s+1; i<=tmp; i++) ans += pi[x/prime[i]];
       return ans;
   }
   return getphi(x,s-1)-getphi(x/prime[s],s-1);
}

LL getpi(LL x) {
    if (x < maxn) return pi[x];
    LL ans = getphi(x,pi[sqrt3(x)]) + pi[sqrt3(x)] - 1;
    for (int i=pi[sqrt3(x)]+1, ed=pi[sqrt2(x)]; i<=ed; i++) ans-=getpi(x/prime[i])-i+1;
    return ans;
}

LL lehmer(LL x){
    if (x<maxn) return pi[x];
    int a=(int)lehmer(sqrt2(sqrt2(x)));
    int b=(int)lehmer(sqrt2(x));
    int c=(int)lehmer(sqrt3(x));

    LL sum = getphi(x,a)+(LL)(b+a-2)*(b-a+1)/2;
    for (int i=a+1; i<=b; i++) {
        LL w = x/prime[i];
        sum -= lehmer(w);
        if (i>c) continue;
        LL lim = lehmer(sqrt2(w));
        for (int j=i; j<=lim; j++) sum -= lehmer(w/prime[j]) - (j-1);
    }
    return sum;
}

int main(){
    init();
    int T;
    scanf("%d",&T);
    int kase = 0;
    while (T--) {
       scanf("%lld%lld",&A,&B);
       printf("Case %d: %lld\n",++kase,lehmer(B)-lehmer(A-1));
    }
    return 0;
}
