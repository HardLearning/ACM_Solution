#include <cstdio>
using namespace std;

const int maxn = 10000+5;
int a[maxn];
int k;

bool judge(int x){
    int sum = 0;
    while (x) {
        sum += x%10;
        x/=10;
    }
    return sum == 10;
}

int main(){
    int tmp = 0;
    for (int i=1; i<=12000000; i++) {
        if (tmp == 10000) break;
        if (judge(i)) a[++tmp] = i;
    }

    scanf("%d",&k);
    printf("%d\n",a[k]);
    return 0;
}
