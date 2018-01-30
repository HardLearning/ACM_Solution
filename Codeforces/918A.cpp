#include <cstdio>
using namespace std;

int n;

int main(){
    scanf("%d",&n);
    int f1 = 1,f2 = 2,f3;
    for (int i=1; i<=n; i++) {
        if (i == f1) {
            printf("O");
            f3 = f1+f2;
            f1 = f2;
            f2 = f3;
        }
        else printf("o");
    }
    printf("\n");
    return 0;
}
