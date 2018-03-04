#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define pb push_back
const int maxn = 9*9*4+5;
const int maxr = 9*9*9+5;
const int maxnode = maxn*maxr;

struct DLX{
    int n,sz;
    int S[maxn];

    int row[maxnode],col[maxnode];
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
    int ansd,ans[maxr];

    void init(int n){
        this->n = n;

        for (int i=0; i<=n; i++) {
            U[i] = D[i] = i; L[i] = i-1; R[i] = i+1;
        }
        R[n] = 0; L[0] = n;
        sz = n+1;
        memset(S,0,sizeof(S));
    }

    void addRow(int r, vector<int>columns){
        int first = sz;
        for (int i=0; i<columns.size(); i++) {
            int c = columns[i];
            L[sz] = sz-1; R[sz] = sz+1; D[sz] = c; U[sz] = U[c];
            D[U[c]] = sz; U[c] = sz;
            row[sz] = r; col[sz] = c;
            S[c]++; sz++;
        }
        R[sz-1] = first;
        L[first] = sz-1;
    }

    #define FOR(i,A,s) for (int i=A[s]; i!=s; i=A[i])

    void remove(int c){
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        FOR(i,D,c)
          FOR(j,R,i) {U[D[j]] = U[j]; D[U[j]] = D[j]; --S[col[j]]; }
    }

    void restore(int c){
        FOR(i,U,c)
          FOR(j,L,i) {++S[col[j]]; U[D[j]] = D[U[j]] = j;}
        L[R[c]] = R[L[c]] = c;
    }

    bool dfs(int d){
       if (R[0]==0) {ansd = d; return 1;}
       int c = R[0];
       FOR(i,R,0) if (S[i]<S[c]) c = i;

       remove(c);
       FOR(i,D,c) {
          ans[d] = row[i];
          FOR(j,R,i) remove(col[j]);
          if (dfs(d+1)) return 1;
          FOR(j,L,i) restore(col[j]);
       }
       restore(c);

       return 0;
    }

    bool solve(vector<int>& v){
      v.clear();
      if (!dfs(0)) return 0;
      for (int i=0; i<ansd; i++) v.pb(ans[i]);
      return 1;
    }

};
DLX solver;

const int SLOT  = 0;
const int ROW = 1;
const int COL = 2;
const int SUB = 3;

int encode(int a, int b, int c){
    return a*81+b*9+c+1;
}

int decode(int code, int& a, int& b, int& c){
   code--;
   c = code%9; code/=9;
   b = code%9; code/=9;
   a = code;
}

char str[100];
char puzzle[12][12];

int main(){
    while (scanf("%s",str)==1){
        if (strcmp(str,"end")==0) break;
        int k=0;
        for (int i=0; i<9; i++)
            for (int j=0; j<9; j++) puzzle[i][j] = str[k++];

        solver.init(9*9*4);
        for (int r=0; r<9; r++)
            for (int c=0; c<9; c++)
               for (int v=0; v<9; v++)
                  if (puzzle[r][c]=='.' || puzzle[r][c]=='1'+v) {
                         vector<int>columns;
                         columns.pb(encode(SLOT,r,c));
                         columns.pb(encode(ROW,r,v));
                         columns.pb(encode(COL,c,v));
                         columns.pb(encode(SUB,(r/3)*3+c/3,v));
                         solver.addRow(encode(r,c,v),columns);
                  }

        vector<int> ans;
        solver.solve(ans);
        for (int i=0; i<ans.size(); i++) {
            int r,c,v;
            decode(ans[i],r,c,v);
            puzzle[r][c] = '1'+v;
        }
        for (int i=0; i<9; i++) printf("%s",puzzle[i]);
        printf("\n");
    }
    return 0;
}
