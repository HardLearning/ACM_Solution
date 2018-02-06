#include <cstdio>
#include <algorithm>
using namespace std;

double p;
int n,m;
int x,y;

int main(){
    while (scanf("%d %d",&n,&m)==2){
        p = 1e15;
        while (n--) {
            scanf("%d %d",&x,&y);
            p = min(p,1.0*x/y);
        }
        printf("%0.8f\n",p*m);
    }
    return 0;
}
