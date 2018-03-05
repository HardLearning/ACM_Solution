#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 600+5;
int a[maxn];
int n;

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) scanf("%d",&a[i]);
    sort(a,a+n);
    n = unique(a,a+n)-a;
    if (a[0]==0) n--;
    printf("%d\n",n);
    return 0;
}
