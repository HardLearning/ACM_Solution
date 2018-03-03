#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxm = 1000+5;
const int maxn = 500+5;
const int maxnode = 100000;

struct DLX{
    int n,m,sz;
    int S[maxm],H[maxn];
    int row[maxnode],col[maxnode];
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
    int ansd;

    void init(int n, int m){
       this->n = n;  this->m = m;
       for (int i=0; i<=m; i++) {
          U[i] = D[i] = i;
          L[i] = i-1; R[i] = i+1;
          S[i] = 0;
       }
       R[m] = 0;
       L[0] = m;
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

    #define FOR(i,A,s) for(int i=A[s]; i!=s; i=A[i])

    void remove(int c){
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        FOR(i,D,c)
          FOR(j,R,i) {U[D[j]] = U[j]; D[U[j]] = D[j]; --S[col[j]];}
    }

    void restore(int c){
        FOR(i,U,c)
          FOR(j,L,i) { ++S[col[j]]; U[D[j]] = j; D[U[j]] = j; }
        L[R[c]] = c;
        R[L[c]] = c;
    }

    void dfs(int d){
        if (ansd!=-1 && d>=ansd) return;
        if (R[0]==0) {
            if (ansd==-1) ansd = d;
            else if (d<ansd) ansd = d;
            return ;
        }

        int c = R[0];
        FOR(i,R,0) if (S[i]<S[c]) c = i;

        remove(c);
        FOR(i,D,c) {
            FOR(j,R,i) remove(col[j]);
            dfs(d+1);
            FOR(j,L,i) restore(col[j]);
        }
        restore(c);
    }
};
DLX solver;
int n,m,p;

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d%d",&n,&m,&p);
        solver.init(p,n*m);

        int x1,y1,x2,y2;
        for (int k=1; k<=p; k++) {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            for (int i=x1+1; i<=x2; i++) {
                for (int j=y1+1; j<=y2; j++) solver.addRow(k,(i-1)*m+j);
            }
        }

        solver.dfs(0);
        printf("%d\n",solver.ansd);
    }
    return 0;
}
