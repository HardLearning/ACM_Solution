#include <cstdio>
#include <cstring>
using namespace std;

inline int Max(int x, int y) { return x>y?x:y; }
inline int Min(int x, int y) { return x<y?x:y; }
const int INF = 1<<30;
const int maxn = 200+5;
int w[maxn][maxn];
int Lx[maxn],Ly[maxn];
int n,m;
bool S[maxn],T[maxn];
int left[maxn];

bool match(int i){
   S[i] = 1;
   for (int j=1; j<=n; j++) if (Lx[i]+Ly[j]==w[i][j] && !T[j]){
       T[j] = 1;
       if (!left[j] || match(left[j])) {
           left[j] = i;
           return 1;
       }
   }
   return 0;
}

void update(){
   int a = INF;
   for (int i=1; i<=n; i++) if (S[i])
     for (int j=1; j<=n; j++) if (!T[j])
        a = Min(a,Lx[i]+Ly[j]-w[i][j]);
   for (int i=1; i<=n; i++) {
      if (S[i]) Lx[i] -= a;
      if (T[i]) Ly[i] += a;
   }
}

int KM(){
   for (int i=1; i<=n; i++) {
      Lx[i] = left[i] = Ly[i] = 0;
      for (int j=1; j<=n; j++) Lx[i] = Max(Lx[i],w[i][j]);
   }
   for (int i=1; i<=n; i++) {
       for (;;) {
           memset(S,0,sizeof(S));
           memset(T,0,sizeof(T));
           if (match(i)) break; else update();
       }
   }

   int ans = 0;
   for (int i=1; i<=n; i++) ans += w[left[i]][i];
   return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++) w[i][j] = -INF;

        int a,b,c;
        while (m--){
            scanf("%d%d%d",&a,&b,&c);
            w[a][b] = Max(w[a][b],-c);
        }

        int ans = KM();
        printf("%d\n",-ans);
    }
    return 0;
}
