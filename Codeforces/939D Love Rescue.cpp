#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxm = 100000+5;
const int maxn = 30;
int fa[maxn];
int n;
char s1[maxm],s2[maxm];

struct Edge{
    int x,y;
};
vector<Edge>ans;

int Find(int x) {
   if (fa[x]==x) return x;
   return fa[x] = Find(fa[x]);
}

int main(){
    while (scanf("%d",&n)==1){
        scanf("%s",s1);
        scanf("%s",s2);

        ans.clear();
        for (int i=0; i<26; i++) fa[i] = i;
        for (int i=0; i<n; i++) {
            int a = s1[i]-'a';
            int b = s2[i]-'a';
            if (Find(a)!=Find(b)) {
                fa[Find(a)] = Find(b);
                ans.push_back((Edge){a,b});
            }
        }


        printf("%d\n",ans.size());
        for (int i=0; i<ans.size(); i++) printf("%c %c\n",ans[i].x+'a',ans[i].y+'a');
    }
    return 0;
}
