#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxm = 20;
const int maxn = 1000;
int a[maxn],sa[maxn],Rank[maxn],height[maxn],idx[maxn];
int t[maxn],t2[maxn],c[maxn];
int n,len,tot;
char s[maxn];

void build_sa(int n, int m){
    int *x = t, *y = t2;
    for (int i=0; i<m; i++) c[i] = 0;
    for (int i=0; i<n; i++) c[x[i] = a[i]]++;
    for (int i=1; i<m; i++) c[i] += c[i-1];
    for (int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;

    for (int k=1; k<=n; k<<=1) {
        int p = 0;
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

char solve[maxn];
bool vis[maxm];
bool judge(int mid){
    int cnt = 0;
    memset(vis,0,sizeof(vis));
    for (int i=2; i<=n; i++) {
        if (height[i]<mid) {
            cnt = 0 ;
            memset(vis,0,sizeof(vis));
            continue;
        }
        if (!vis[idx[sa[i-1]]]) vis[idx[sa[i-1]]] = 1, cnt++;
        if (!vis[idx[sa[i]]]) vis[idx[sa[i]]] = 1, cnt++;
        if (cnt>=tot) {
            for (int k=0; k<mid; k++) solve[k] = a[sa[i]+k];
            solve[mid] = '\0';
            return 1;
        }
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&tot);
        n = 0;
        for (int i=1; i<=tot; i++) {
            scanf("%s",s);
            len = strlen(s);
            for (int j=0; j<len; j++) a[n] = s[j], idx[n++] = i;
            a[n] = 'Z'+i; idx[n++] = tot+i;
        }
        a[--n] = 0;

        build_sa(n+1,'Z'+tot+5);
        get_Height(n);

        int left = 3, right = 65;
        int ans = -1, mid;
        while (left<=right) {
            mid = (left+right)>>1;
            if (judge(mid)) {
                ans = mid;
                left = mid+1;
            }
            else right = mid-1;
        }

        if (ans==-1) printf("no significant commonalities\n");
        else printf("%s\n",solve);
    }
    return 0;
}
