#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxm = 4000+5;
const int maxn = 1e6;
int a[maxn],sa[maxn],Rank[maxn],height[maxn],idx[maxn];
int t[maxn],t2[maxn],c[maxn];
char s[maxm];
int n,tot,len;

void build_sa(int n, int m){
    int *x = t, *y = t2;
    for (int i=0; i<m; i++) c[i] = 0;
    for (int i=0; i<n; i++) c[ x[i] = a[i] ]++;
    for (int i=1; i<m; i++) c[i] += c[i-1];
    for (int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;

    for (int k=1; k<=n; k<<=1) {
        int p=0;
        for (int i=n-k; i<n; i++) y[p++] = i;
        for (int i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i]-k;

        for (int i=0; i<m; i++) c[i] = 0;
        for (int i=0; i<n; i++) c[x[y[i]]]++;
        for (int i=1; i<m; i++) c[i] += c[i-1];
        for (int i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];

        swap(x,y);
        p = 1; x[sa[0]] = 0;
        for (int i=1; i<n; i++)
          x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1:p++;
        if (p>=n) break;
        m = p;
    }
}

void get_Height(int n) {
    int k = 0;
    for (int i=1; i<=n; i++) Rank[sa[i]] = i;
    for (int i=0; i<n; i++) {
        if (k) k--;
        int j = sa[Rank[i]-1];
        while (a[j+k]==a[i+k]) k++;
        height[Rank[i]] = k;
    }
}

bool vis[maxm];
char solve[maxn];
bool judge(int mid){
    int L,R;
    for (int i=1; i<=n; i++) {
       L = i;
       while (L<=n && height[L]<mid) L++;
       R = L;
       while (R<=n && height[R]>=mid) R++;
       for (int k=1; k<=tot; k++) vis[k] = 0;

       int tmp;
       for (int k=L-1; k<=R-1; k++) {
           tmp = idx[sa[k]];
           if (tmp<=tot) vis[tmp] = 1;
       }

       int j;
       for (j = 1; j<=tot; j++) if (!vis[j]) break;
       if (j>tot) {
           for (int k=0; k<mid; k++) solve[k] = a[sa[R-1]+k];
           solve[mid] = '\0';
           return 1;
       }
       i = R;
    }
    return 0;
}

int main(){
    while (scanf("%d",&tot)==1 && tot) {
       n = 0;
       for (int i=1; i<=tot; i++) {
           scanf("%s",s);
           len = strlen(s);
           for (int j=0; j<len; j++) a[n] = s[j], idx[n++] = i;
           a[n] = 'z'+i; idx[n++] = tot+i;
       }
       a[--n] = 0;
       build_sa(n+1,'z'+tot+5);
       get_Height(n);

       int left = 1, right = 210;
       int ans = -1, mid;

       while (left<=right) {
           mid = (left+right)>>1;
           if (judge(mid)) {
               ans = mid;
               left = mid+1;
           }
           else right = mid-1;
       }

       if (ans == -1) printf("IDENTITY LOST\n");
       else {
          printf("%s\n",solve);
       }
    }
    return 0;
}
