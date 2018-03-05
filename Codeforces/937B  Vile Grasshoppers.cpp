#include <cstdio>
#include <cmath>
using namespace std;

int p,y;
bool flag;
int main(){
    scanf("%d%d",&p,&y);
    if (y%2==0) y--;
    flag = 0;

    while (y>p) {
        flag = 1;
        for (int i=3; i<=sqrt(y) && i<=p; i++) if (y%i==0) {flag = 0 ; break;}
        if (flag==1) break;
        else y-=2;
    }
    if (flag) printf("%d\n",y); else printf("-1\n");
    return 0;
}
