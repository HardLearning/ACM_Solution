#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100000+10;
char b[maxn];
char a[maxn];
int n,nxt[maxn];

void get_next(){
    nxt[0] = nxt[1] = 0;
    int j = 0;
    for (int i=1; i<n; i++) {
        while (j && b[j]!=b[i]) j = nxt[j];
        if (b[j]==b[i]) j++;
        nxt[i+1] = j;
    }
}

int KMP(){
    int j = 0;
    for (int i=0; i<n; i++) {
        while (j && a[i]!=b[j]) j = nxt[j];
        if (a[i] == b[j]) j++;
        if (j == n) return n;
    }
    return j;
}


int main(){
    while (scanf("%s",a)!=EOF){
        n = strlen(a);
        for (int i=0; i<n; i++) b[i] = a[n-1-i];
        get_next();
        printf("%s",a);
        int s = KMP();
        for (int i=s; i<n; i++) printf("%c",b[i]);
        printf("\n");
    }
    return 0;
}
