#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 200000+5;
char s[maxn];
int a[maxn];
int cnt[maxn][10];
int n;

void solve(){
   for (int i=n; i>=1; i--) {
       for (int j=a[i]-1; j>=(i==1); j--) {
           int res = 0;
           for (int k=0; k<10; k++) res += cnt[i-1][k]^(k==j);

           if (res<=n-i) {
               for (int k=1; k<i; k++) printf("%d",a[k]);
               printf("%d",j);
               for (int k=1; k<=n-i-res; k++) printf("9");
               for (int k=9; k>=0; k--) if (cnt[i-1][k]^(k==j)) printf("%d",k);
               printf("\n");
               return ;
           }
       }
   }

   for (int i=1; i<=n-2; i++) printf("9"); printf("\n");
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%s",s+1);
        n = strlen(s+1);
        for (int k=0; k<10; k++) cnt[0][k] = 0;
        for (int i=1; i<=n; i++) {
            a[i] = s[i]-'0';
            for (int k=0; k<10; k++) cnt[i][k] = cnt[i-1][k]^(k == a[i]);
        }

        solve();
    }
    return 0;
}
