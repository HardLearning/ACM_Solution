#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 6e4;
int idx[maxn];
int n,len,init_len;
char  s[maxn],p[5];

typedef unsigned long long ULL;
ULL Hash[maxn],mi[maxn];

inline void Build(int pos) {
    for (int i=pos; i<=len; i++) Hash[i] = Hash[i-1]*131+s[i];
}

inline int query(int x, int y) {
   if (x>y) swap(x,y);
   int left = 0, right = len-y+1;
   int mid , ans = 0;
   while (left<=right) {
      mid = (left+right)>>1;
      if (Hash[x+mid-1]-Hash[x-1]*mi[mid] == Hash[y+mid-1] - Hash[y-1]*mi[mid]) {
          left = mid+1;
          ans = mid;
      }
      else right = mid-1;
   }
   return ans;
}

int main(){
    scanf("%s",s+1);
    init_len = len = strlen(s+1);
    mi[0] = 1;
    for (int i=1; i<=init_len; i++) mi[i] = mi[i-1]*131;
    for (int i=1; i<=init_len; i++) idx[i] = i;
    Build(1);

    scanf("%d",&n);
    while (n--){
       scanf("%s",p);
       if (p[0]=='I') {
           scanf("%s",p);
           int pos; scanf("%d",&pos);
           if (pos>len) pos = len+1;
           for (int i=len; i>=pos; i--) s[i+1] = s[i];
           s[pos] = p[0];
           len++;

           for (int i=init_len; i>=1; i--) if (idx[i]>=pos) idx[i]++; else break;
           Build(pos);
       }
       else {
          int L,R;
          scanf("%d%d",&L,&R);
          printf("%d\n",query(idx[L],idx[R]));
       }
    }

    return 0;
}
