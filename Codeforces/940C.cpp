#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100000+5;
char s[maxn];
int n,k;
bool mark[30];

int main(){
    scanf("%d%d",&n,&k);
    scanf("%s",s);
    memset(mark,0,sizeof(mark));
    for (int i=0; i<n; i++) mark[s[i]-'a'] = 1;
    int mn = 0, mx = 29;
    while (mark[mx]==0) mx--;
    while (mark[mn]==0) mn++;

    if (n<k) {
       for (int i=n; i<k; i++) s[i] = mn+'a';
       for (int i=0; i<k; i++) printf("%c",s[i]);
       printf("\n");
       return 0;
    }

    int len = min(n,k);
    bool flag = 0;
    for (int i=len-1; i>=0; i--) {
        for (int j=s[i]-'a'+1; j<=mx; j++) if (mark[j]) {
            flag = 1;
            s[i] = j+'a';
            for (int f=i+1; f<k; f++) s[f] = mn+'a';
            break;
        }
        if (flag) break;
    }
    for (int i=0; i<k; i++) printf("%c",s[i]); printf("\n");
    return 0;
}
