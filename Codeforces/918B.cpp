#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string,string>mp;
int n,m;
string s1,s2;

int main(){
    mp.clear();
    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        cin >> s1 >> s2;
        mp[s2] = s1;
    }

    int sz;
    string tmp;
    for (int i=1; i<=m; i++) {
        cin >> s1 >> s2;
        sz = s2.size();
        tmp = s2.substr(0,sz-1);
        cout << s1 << " " << s2 << " #" << mp[tmp] << endl;
    }
    return 0;
}
