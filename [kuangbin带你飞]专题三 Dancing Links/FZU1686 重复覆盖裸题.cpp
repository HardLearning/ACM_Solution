#include <cstdio>
#include <cstring>
using namespace std;

const int INF = 1<<20;
const int maxn = 400;
const int maxnode = 1000;

struct DLX{
   int n,m,sz;
   int U[maxnode],D[maxnode],R[maxnode],L[maxnode];
   int row[maxnode],col[maxnode];
   int H[maxn],S[maxn];
   int ansd;

   void init(int n, int m){
       this->n = n; this->m = m;
       for (int i=0; i<=m; i++) {
          S[i] = 0;
          U[i] = D[i] = i;
          L[i] = i-1;
          R[i] = i+1;
       }
       R[m] = 0; L[0] = m;
       sz = m;
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

   #define FOR(i,A,s) for (int i=A[s]; i!=s; i=A[i])
   void remove(int c){
      FOR(i,D,c) L[R[i]] = L[i],R[L[i]] = R[i];
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
      if (d>=ansd) return ;
      if (d+h()>=ansd) return;
      if (R[0]==0) {
         if (d<ansd) ansd = d;
         return;
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
int n,m;
int nx,my;
int a[20][20];
int b[20][20];

void build(int x,int y, int r){
    for (int i=x; i<=x+nx-1; i++) {
        for (int j=y; j<=y+my-1; j++)
            if (a[i][j]==1) solver.addRow(r,b[i][j]);
    }
}

int main(){
    while (scanf("%d%d",&n,&m)==2){
       for (int i=1; i<=n; i++)
         for (int j=1; j<=m; j++) scanf("%d",&a[i][j]);
       scanf("%d%d",&nx,&my);
       int k = 0;
       for (int i=1; i<=n; i++)
          for (int j=1; j<=m; j++) if (a[i][j]==1) b[i][j] = ++k;

       solver.init((n-nx+1)*(m-my+1),k);

       int idx = 0;
       for (int i=1; i<=n-nx+1; i++) {
          for (int j=1; j<=m-my+1; j++) {
              idx++;
              build(i,j,idx);
          }
       }

       solver.dfs(0);
       if (solver.ansd==INF) solver.ansd = 0;
       printf("%d\n",solver.ansd);
    }
    return 0;
}
