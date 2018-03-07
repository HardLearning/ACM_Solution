#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;

typedef long long LL;
const int maxn = 2*100000+5;
char s1[maxn],s2[maxn];
int a[maxn],sa[maxn];
int t[maxn],t2[maxn],c[maxn];
int Rank[maxn],height[maxn];
int n,len,K;

void build_sa(int n, int m){
   int *x = t, *y = t2;
   for (int i=0; i<m; i++) c[i] = 0;
   for (int i=0; i<n; i++) c[x[i] = a[i]]++;
   for (int i=1; i<m; i++) c[i] += c[i-1];
   for (int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;

   for (int k=1; k<=n; k<<=1){
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

void get_Height(int n){
   int k = 0;
   for (int i=0; i<=n; i++) Rank[sa[i]] = i;
   for (int i=0; i<n; i++) {
       if (k) k--;
       int j = sa[Rank[i]-1];
       while (a[i+k]==a[j+k]) k++;
       height[Rank[i]] = k;
   }
}

struct node{
   int h,cnt;
};
stack<node>st;

int main(){
    while (scanf("%d",&K)==1 && K){
       scanf("%s%s",s1,s2);
       n = 0;
       len = strlen(s1);
       for (int i=0; i<len; i++) a[n++] = s1[i];
       a[n++] = '$';
       len = strlen(s2);
       for (int i=0; i<len; i++) a[n++] = s2[i];
       a[n] = '0';

       build_sa(n+1,200);
       get_Height(n);
       len = strlen(s1);

       LL ans = 0, tot = 0;

       while (!st.empty()) st.pop();
       for (int i=1; i<=n; i++) {
          if (height[i]<K) {
             while (!st.empty()) st.pop();
             tot = 0;
          }
          else {
             int cnt = 0;
             if (sa[i-1]<len) {
                cnt++; tot += height[i]-K+1;
             }
             node u;
             while (!st.empty()) {
                  u = st.top();
                  if (u.h<height[i]) break;
                  st.pop();
                  cnt += u.cnt;
                  tot += (height[i]-u.h)*u.cnt;
             }
             if (sa[i]>len) ans += tot;
             st.push((node){height[i],cnt});
          }
       }

       tot = 0;
       while (!st.empty()) st.pop();
       for (int i=1; i<=n; i++) {
          if (height[i]<K) {
             while (!st.empty()) st.pop();
             tot = 0;
          }
          else {
             int cnt = 0;
             if (sa[i-1]>len) {
                cnt++; tot += height[i]-K+1;
             }
             node u;
             while (!st.empty()) {
                  u = st.top();
                  if (u.h<height[i]) break;
                  st.pop();
                  cnt += u.cnt;
                  tot += (height[i]-u.h)*u.cnt;
             }
             if (sa[i]<len) ans += tot;
             st.push((node){height[i],cnt});
          }
       }

       printf("%I64d\n",ans);

    }
    return 0;
}
