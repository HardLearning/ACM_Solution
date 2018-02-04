#include <cstdio>
#include <stack>
using namespace std;

stack<int>s;
int n,x;

int main(){
    while (scanf("%d",&n)==1){
        while (!s.empty()) s.pop();
        for (int i=1; i<=n; i++) {
            scanf("%d",&x);
            if (s.empty() || s.top()==x ) s.push(x);
            else s.pop();
        }
        printf("%d\n",s.top());
    }
    return 0;
}
