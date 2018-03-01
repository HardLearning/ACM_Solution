#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 300+5;
int w[maxn][maxn],n;
int Lx[maxn],Ly[maxn];
int left[maxn];
bool S[maxn],T[maxn];

inline int Max(int x, int y) {return x>y?x:y;}
inline int Min(int x, int y) {return x<y?x:y;}

bool match(int i){
    S[i] = 1;
    for (int j=1; j<=n; j++) if (Lx[i]+Ly[j]==w[i][j] && !T[j]) {
        T[j] = 1;
        if (!left[j] || match(left[j])) {
            left[j] = i;
            return 1;
        }
    }
    return 0;
}

void update(){
    int a = 1<<30;
    for (int i=1; i<=n; i++) if (S[i])
        for (int j=1; j<=n; j++) if (!T[j])
           a = Min(a,Lx[i]+Ly[j]-w[i][j]);
    for (int i=1; i<=n; i++) {
        if (S[i]) Lx[i] -= a;
        if (T[i]) Ly[i] += a;
    }
}

void KM(){
    for (int i=1; i<=n; i++) {
        left[i] = Lx[i] = Ly[i] = 0;
        for (int j=1; j<=n; j++) Lx[i] = Max(Lx[i],w[i][j]);
    }

    for (int i=1; i<=n; i++) {
        for (;;) {
            for (int j=1; j<=n; j++) S[j] = T[j] = 0;
            if (match(i)) break; else update();
        }
    }
}

int main(){
    while (scanf("%d",&n)==1){
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++) scanf("%d",&w[i][j]);
        KM();

        int ans = 0;
        for (int i=1; i<=n; i++) ans += w[left[i]][i];
        printf("%d\n",ans);
    }
    return 0;
}
