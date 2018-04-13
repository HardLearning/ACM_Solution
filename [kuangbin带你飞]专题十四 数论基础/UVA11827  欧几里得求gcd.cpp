#include <cstdio>
#include <cmath>
using namespace std;

const int maxn = 100+5;
int a[maxn],n;
int gcd(int x, int y) {
    return y==0?x:gcd(y,x%y);
}
inline int Max(int x, int y) {return x>y?x:y; }

char ch;

int main(){
    int T;
    scanf("%d",&T);
    while (getchar() != '\n');
    while (T--){
        n = 0;
        while ((ch = getchar()) != '\n') {
            if (ch>='0' && ch<='9') {
                a[n] = 0;
                while (ch>='0' && ch<='9') a[n] = (a[n]<<3)+(a[n]<<1) + ch-'0', ch=getchar();
                n++;
            }
            if (ch=='\n') break;
        }

        int mx = 1;
        for (int i=0; i<n; i++)
            for (int j=i+1; j<n; j++) mx = Max(mx,gcd(a[i],a[j]));
        printf("%d\n",mx);
    }
    return 0;
}
