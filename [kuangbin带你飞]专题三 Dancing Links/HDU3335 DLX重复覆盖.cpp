#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1<<20;
typedef long long LL;
const int maxm = 1000+5;
const int maxn = 1000+5;
const int maxnode = maxm*maxn;

struct DLX{
    int n,m,sz;
    int S[maxm],H[maxn];
    int row[maxnode],col[maxnode];
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
    int ansd;

    void init(int n, int m){
        this->n = n; this->m  = m;
        for (int i=0; i<=m; i++) {
            D[i] = U[i] = i;
            L[i] = i-1; R[i] = i+1;
            S[i] = 0;
        }
        R[m] = 0; L[0] = m;
        sz = m;
        for (int i=1; i<=n; i++) H[i] = -1;

        ansd = 0;
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
            R[H[r]] =sz;
        }
    }

    #define FOR(i,A,s) for(int i=A[s]; i!=s; i=A[i])

    void remove(int c){
       FOR(i,D,c) L[R[i]] = L[i], R[L[i]] = R[i];
    }

    void restore(int c){
        FOR(i,U,c) L[R[i]] = R[L[i]] =i;
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
        if (R[0]==0) {
            if (d>ansd) ansd = d;
            return;
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
int n;
LL num[maxn];

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%I64d",&num[i]);
        sort(num+1,num+n+1);
        solver.init(n,n);

        for (int i=1; i<=n; i++) {
           for (int j=i+1; j<=n; j++) if (num[j]%num[i]==0) solver.addRow(i,j),solver.addRow(j,i);
           solver.addRow(i,i);
        }

        solver.dfs(0);
        printf("%d\n",solver.ansd);
    }
    return 0;
}
