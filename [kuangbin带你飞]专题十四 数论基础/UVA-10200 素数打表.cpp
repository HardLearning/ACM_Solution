#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxm = 10000+10;
const int maxn = 20000+10;
bool isprime[maxn];
vector<int> prime;
int sum[maxm];
int a,b;

void get_prime(int n) {
    prime.clear();
    memset(isprime,1,sizeof(isprime));
    for (int i=2; i*i<n; i++) if (isprime[i]) {
        for (int j=i*i; j<n; j+=i) isprime[j] = 0;
    }
    for (int i=2; i<n; i++) if (isprime[i]) prime.push_back(i);
}

void init(){
   sum[0] = 0;
   for (int i=1; i<=10000; i++) {
       int t = i*i+i+41;
       bool flag = 1;
       for (int k=0; k<prime.size() && prime[k]<t; k++) if (t%prime[k]==0) {flag = 0; break; }
       if (flag == 0) sum[i] = sum[i-1]+1; else sum[i] = sum[i-1];
   }
}

int main(){
    get_prime(maxn);
    init();
    int x,y;
    while (scanf("%d%d",&a,&b)==2) {
         if (a==0) x = b-sum[b]+1; else x = (b-a+1)-(sum[b]-sum[a-1]);
         y = b-a+1;
         printf("%.2f\n",x*100.0/y+1e-8);
    }
    return 0;
}
