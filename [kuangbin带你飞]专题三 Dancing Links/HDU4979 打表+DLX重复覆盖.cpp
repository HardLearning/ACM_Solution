#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 8;
const int maxr = 1000;
const int maxc = 1000;
const int maxnode = maxr*maxc;
const int INF = 1<<25;
int n,m,R;

struct DLX{
    int n,m,sz;
    int S[maxc],H[maxr];
    int row[maxnode],col[maxnode];
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
    int ansd;

    void init(int n, int m){
        this->n = n; this->m = m;
        for (int i=0; i<=m; i++) {
            D[i] = U[i] = i;
            L[i] = i-1; R[i] = i+1;
            S[i] = 0;
        }
        R[m] = 0; L[0] = m; sz = m;
        for (int i=1; i<=n; i++) H[i] = -1;

        ansd = INF;
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

    #define FOR(i,A,s) for (int i=A[s]; i!=s; i = A[i])
    void remove(int c){
        FOR(i,D,c) L[R[i]] = L[i], R[L[i]] = R[i];
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
        if (d+h()>=ansd) return;
        if (R[0]==0) {
            if (d<ansd) ansd = d;
            return ;
        }

        int c = R[0];
        FOR(i,R,0) if (S[i]<S[c]) c=i;
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

int C[maxn+1][maxn+1];
int bitcnt[1<<maxn+5];

int Bitcnt(int x){
    int ret = 0;
    while (x) {
        ret += (x&1);
        x>>=1;
    }
    return ret;
}

void GetBitCnt(){
   for (int i=0; i<(1<<maxn); i++) bitcnt[i] = Bitcnt(i);
}

void GetC(){
    for (int i=1; i<=maxn; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j=1; j<i; j++) C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
}

int cnt[1<<maxn+5];
void solve(int n, int m , int R){
    int ccnt = 0;
    solver.init(C[n][m],C[n][R]);
    for (int i=1; i<(1<<n); i++) if (bitcnt[i]==R) cnt[i] = ++ccnt;

    int rcnt = 0;
    for (int i=1; i<(1<<n); i++) if (bitcnt[i]==m) {
        ++rcnt;
        for (int j=i; j>0; j=(i&(j-1))) if(bitcnt[j]==R) solver.addRow(rcnt,cnt[j]);
    }
    solver.dfs(0);
    printf("%d",solver.ansd);
}

void WriteTable(){
     puts("{");
     for (int n=1; n<=maxn; n++) {
        puts("  {");
        for (int m=1; m<=n; m++) {
            printf("   {");
            for (int R=1; R<=m; R++) {
                if (R>1) printf(",");
                solve(n,m,R);
            }
            printf("}");
            if (m==n) puts(""); else puts(",");
        }
        printf("   }");
        if (n==maxn) puts(""); else puts(",");
     }
     puts("}");
}

int main(){
    freopen("table.txt","w",stdout);
    GetBitCnt();
    GetC();
    WriteTable();
    return 0;
}
