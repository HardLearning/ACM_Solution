#include <iostream>
#include <cmath>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

double A,B,x,y;

inline void Swap(double& a, double& b) {double c=a; a=b; b=c;}
int main(){
    while (cin>>A>>B>>x>>y && A!=0 && B!=0 && x!=0 && y!=0){
        if (A<B) Swap(A,B);
        if (x<y) Swap(x,y);

        if (dcmp(A-x)>0 && dcmp(B-y)>0) {
            cout << "Escape is possible." << endl;
            continue;
        }

        if (dcmp(A*A+B*B-x*x-y*y)<0) {
            cout << "Box cannot be dropped." << endl;
            continue;
        }

        double p = (B-sqrt(x*x+y*y-A*A))/2;
        double q = (A-sqrt(x*x+y*y-B*B))/2;

        if (p*p+q*q-y*y>0) cout << "Escape is possible." << endl;
        else cout << "Box cannot be dropped." << endl;
    }
    return 0;
}

