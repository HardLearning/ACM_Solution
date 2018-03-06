#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000000+5;
char s[maxn];
int nxt[maxn];
int n;

void KMP(){
   n = strlen(s);
   nxt[0] = nxt[1] = 0;
   for (int i=1; i<n; i++) {
      int j = nxt[i];
      while (j && s[j]!=s[i]) j = nxt[j];
      if (s[i]==s[j]) j++;
      nxt[i+1] = j;
   }
}

int main(){
    while (scanf("%s",s)==1){
        if (strcmp(s,".")==0) break;
        KMP();
        if (n%(n-nxt[n])==0) printf("%d\n",n/(n-nxt[n]));
        else printf("1\n");
    }
    return 0;
}
