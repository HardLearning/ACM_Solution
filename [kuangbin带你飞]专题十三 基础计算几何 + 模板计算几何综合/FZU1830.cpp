#include <cstdio>
#include <cmath>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

double N,L;

int main(){
    while (scanf("%lf%lf",&N,&L)==2){
        if (dcmp(L)==0) { printf("Oh, my god!\n"); continue; }
        double a = 1.0;
        double b = N-L;
        double c = 2*N*N-N*L-N*N*N/2/L; c = -c;
        double delta = b*b-4*a*c;
        if (dcmp(delta)<0) printf("Oh, my god!\n");
        else {
            delta = sqrt(delta);
            double x1 = (-b+delta)/2/a;
            double x2 = (-b-delta)/2/a;
            if (dcmp(x1)>=0 && dcmp(N-x1)>0 && dcmp(x1-L+2*N)>0) { printf("%.2f\n",x1); continue;}
            if (dcmp(x2)>=0 && dcmp(N-x2)>0 && dcmp(x2-L+2*N)>0) { printf("%.2f\n",x2); continue;}
            printf("Oh, my god!\n");
        }
    }
    return 0;
}
