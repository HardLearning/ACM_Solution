#include <cstdio>
using namespace std;

const int maxn = 100000+5;
int a[maxn];
int n;
int s,f;

int main(){
    while (scanf("%d",&n)==1) {
        for (int i=1; i<=n; i++) scanf("%d",&a[i%n]);
        scanf("%d%d",&s,&f);
        int cnt = 0;
        for (int i=s; i<=f; i++) cnt += a[i%n];
        int mx = 0,idx=-1;
        int left,right;
        for (int i=0; i<n; i++) {
             left = (s-i+n)%n;
             right = (f-i+n)%n;
             cnt = cnt+a[left]-a[right];
             if (cnt>mx) {
                mx = cnt;
                idx = i;
             }
        }
        printf("%d\n",idx+1);
    }
    return 0;
}
