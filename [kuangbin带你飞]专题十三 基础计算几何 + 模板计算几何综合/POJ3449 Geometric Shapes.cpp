#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y;
   Point (double x=0, double y=0):x(x),y(y){}
   bool operator ==(const Point& rhs) const {
      return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;
   }
};

typedef Point Vector;

Vector operator +(Vector A,Vector B) {return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A,Vector B) {return Vector(A.x-B.x,A.y-B.y); }
Vector operator *(Vector A,double p) {return Vector(A.x*p,A.y*p); }

double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y;}

int n;
struct node{
   int idx,sz;
   Point p[30];
}poly[30];

struct Node{
   bool v;
   vector<int>num;
}mark[30];

bool OnSegment(Point p, Point a1, Point a2){
   return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}

bool SegmentIntersection(Point a1, Point a2, Point b1, Point b2){
   double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1);
   double c3 = Cross(b2-b1,a1-b1), c4 = Cross(b2-b1,a2-b1);
   if (dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0 ) return 1;

   if (OnSegment(a1,b1,b2) || OnSegment(a2,b1,b2) || OnSegment(b1,a1,a2) || OnSegment(b2,a1,a2)) return 1;
   return a1==b1 || a1==b2 || a2==b1 || a2==b2;
}

int main(){
    n = 0;
    char str[50];
    double x,y;
    while (scanf("%s",str)==1){
        if (str[0]=='.') break;
        if (str[0]=='-') {
            //printf("%d\n",n);
            for (int i=0; i<26; i++) mark[i].v = 0, mark[i].num.clear();

            for (int a=0; a<n; a++) {
               for (int b=a+1; b<n; b++) {
                  bool flag = 0;
                  for (int i=0; i<poly[a].sz; i++) {
                    for (int j=0; j<poly[b].sz; j++)
                       if ( SegmentIntersection(poly[a].p[i],poly[a].p[(i+1)%poly[a].sz],poly[b].p[j],poly[b].p[(j+1)%poly[b].sz]) ){
                           flag = 1;
                           break;
                       }
                    if (flag) break;
                  }
                  if (flag) mark[poly[a].idx].num.push_back(poly[b].idx),mark[poly[b].idx].num.push_back(poly[a].idx);
               }

               mark[poly[a].idx].v = 1;
            }

            for (int i=0; i<26; i++) if (mark[i].v) {
                printf("%c ",i+'A');
                int sz = mark[i].num.size();
                if (sz==0) printf("has no intersections\n");
                else if (sz==1) printf("intersects with %c\n",mark[i].num[0]+'A');
                else {
                    sort(mark[i].num.begin(),mark[i].num.end());
                    if (sz==2) printf("intersects with %c and %c\n",mark[i].num[0]+'A',mark[i].num[1]+'A');
                    else {
                       printf("intersects with");
                       for (int k=0; k<sz-1; k++) printf(" %c,",mark[i].num[k]+'A');
                       printf(" and %c\n",mark[i].num[sz-1]+'A');
                    }
                }
            }
            printf("\n");

            n = 0;
            continue;
        }

        poly[n].idx = str[0]-'A';
        scanf("%s",str);
        if (strcmp(str,"square")==0){
            poly[n].sz = 4;
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[0] = (Point){x,y};
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[2] = (Point){x,y};

            x = (poly[n].p[0].x+poly[n].p[2].x+poly[n].p[2].y-poly[n].p[0].y)/2;
            y = (poly[n].p[0].y+poly[n].p[2].y+poly[n].p[0].x-poly[n].p[2].x)/2;
            poly[n].p[1] = (Point){x,y};

            x = (poly[n].p[0].x+poly[n].p[2].x-poly[n].p[2].y+poly[n].p[0].y)/2;
            y = (poly[n].p[0].y+poly[n].p[2].y-poly[n].p[0].x+poly[n].p[2].x)/2;
            poly[n].p[3] = (Point){x,y};

            n++;
            continue;
        }

        if (strcmp(str,"rectangle")==0){
            poly[n].sz = 4;
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[0] = (Point){x,y};
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[1] = (Point){x,y};
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[2] = (Point){x,y};
            x = poly[n].p[2].x+poly[n].p[0].x-poly[n].p[1].x;
            y = poly[n].p[2].y+poly[n].p[0].y-poly[n].p[1].y;
            poly[n].p[3] = (Point){x,y};

            n++;
            continue;
        }

        if (strcmp(str,"line")==0) {
            poly[n].sz = 2;
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[0] = (Point){x,y};
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[1] = (Point){x,y};
            n++;
            continue;
        }

        if (strcmp(str,"triangle")==0) {
            poly[n].sz = 3;
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[0] = (Point){x,y};
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[1] = (Point){x,y};
            scanf(" (%lf,%lf)",&x,&y); poly[n].p[2] = (Point){x,y};
            n++;
            continue;
        }

        if (strcmp(str,"polygon")==0) {
            scanf("%d",&poly[n].sz);
            for (int i=0; i<poly[n].sz; i++) scanf(" (%lf,%lf)",&x,&y), poly[n].p[i] = (Point){x,y};
            n++;
            continue;
        }

    }
    return 0;
}
