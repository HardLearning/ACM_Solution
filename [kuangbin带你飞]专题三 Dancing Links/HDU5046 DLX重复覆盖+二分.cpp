#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;
const int maxn = 60+5;
const int maxm = 60+5;
const int maxnode = maxn*maxm;

int n,K;
LL d[maxn][maxn];
LL x[maxn],y[maxn];

struct DLX{
    int n,m,sz;
    int S[maxm],H[maxn];
    int row[maxnode],col[maxnode];
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
    int ansd;

    void init(int n,int m){
        this->n = n; this->m = m;
        for (int i=0; i<=m; i++) {
            U[i] = D[i] = i;
            L[i] = i-1; R[i] = i+1;
            S[i] = 0;
        }
        R[m] = 0; L[0] = m;
        sz = m;
        for (int i=1; i<=n; i++) H[i] = -1;
        ansd = -1;
    }

    void addRow(int r, int c){
        ++S[col[++sz]=c];
        row[sz] = r;
        D[sz] = D[c];
        U[D[c]] = sz;
        U[sz] = c;
        D[c] = sz;
        if (H[r]<0) H[r] = L[sz] = R[sz] = sz;
        else {
            R[sz] = R[H[r]];
            L[R[H[r]]] = sz;
            L[sz] = H[r];
            R[H[r]] = sz;
        }
    }

    #define FOR(i,A,s) for (int i=A[s]; i!=s; i=A[i])
    void remove(int c){
        FOR(i,D,c) L[R[i]] = L[i] , R[L[i]] = R[i];
    }

    void restore(int c){
        FOR(i,U,c) L[R[i]] = R[L[i]] = i;
    }

    bool v[maxnode];
    int h(){
        int ret = 0;
        FOR(c,R,0) v[c] = 1;
        FOR(c,R,0) if (v[c]) {
           ret++;
           v[c] = 0;
           FOR(i,D,c)
             FOR(j,R,i) v[col[j]] = 0;
        }
        return ret;
    }

    void dfs(int d){
       int H = h();
       if (d+H>K) return ;
       if (ansd!=-1 && d+H>=ansd) return;
       if (R[0]==0) {
         if (ansd == -1) ansd = d;
         else if (d<ansd) ansd = d;
         return ;
       }

       int c = R[0];
       FOR(i,R,0) if (S[i]<S[c]) c = i;
       FOR(i,D,c) {
          remove(i);
          FOR(j,R,i) remove(j);
          dfs(d+1);
          FOR(j,L,i) restore(j);
          restore(i);
       }
    }
};
DLX solver;

int cnt;
LL D[maxnode];

bool judge(LL dis){
    solver.init(n,n);
    for (int i=1; i<=n; i++)
       for (int j=1; j<=n; j++) if (d[i][j]<=dis) solver.addRow(i,j);
    solver.dfs(0);
    if (solver.ansd!=-1 && solver.ansd<=K) return 1;
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
        scanf("%d%d",&n,&K);
        for (int i=1; i<=n; i++) scanf("%I64d%I64d",&x[i],&y[i]);
        for (int i=1; i<=n; i++)
          for (int j=1; j<=n; j++) d[i][j] = abs(x[i]-x[j])+abs(y[i]-y[j]);
        cnt = 0;
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++) D[cnt++] = d[i][j];
        sort(D,D+cnt);
        cnt = unique(D,D+cnt) - D;

        int left = 0, right = cnt-1;
        int mid,ans=0;
        while (left<=right) {
            mid = (left+right)>>1;
            if (judge(D[mid])) {
                right = mid-1;
                ans = mid;
            }
            else left = mid+1;
        }
        printf("Case #%d: %I64d\n",++kase,D[ans]);
    }
    return 0;
}
