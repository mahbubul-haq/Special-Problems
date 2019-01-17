#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define vi vector<int>
#define vvi vector<vi>02
#define vii vector<pii>
#define vvii vector<vii>
#define vll vector<ll>
#define vpll vector<pll>
#define MOD 998244353
#define EPS 1e-12
#define mem(x,y) memset(x,y,sizeof x)
#define INF 1e9
#define dist2D(x1,y1,x2,y2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define sortv(v) sort(v.begin(),v.end())
#define PI acos(-1.0)

class compare{
public:
    bool operator()(pii x,pii y){
        if(x.second==y.second){
            return x.first<y.first;
        }
        return x.second<y.second;
    }
};

ostream& operator<<(ostream &os,const pll &a){
    os<<a.first<<" "<<a.second;
}

/*pll operator+(const pll &a, const ll &b){ return { a.first+b,a.second+b };}
pll operator*(const pll &a,const ll &b){ return {a.first*b,a.second*b};}
pll operator+(const pll &a,const pll &b){ return {a.first+b.first,a.second+b.second};}
pll operator-(const pll &a,const pll &b){ return { a.first-b.first,a.second-b.second};}
pll operator*(const pll &a,const pll &b){ return {a.first*b.first,a.second*b.second};}
pll operator%(const pll &a,const pll &b){ return {a.first%b.first,a.second%b.second};}*/

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

///=======================================template=======================================///

class Point{
public:
    double x,y;
    Point(){ x=y=0.0; }
    Point(double _x,double _y):x(_x),y(_y) { }
    Point(const Point &p):x(p.x),y(p.y){}

    bool operator < (Point &outer) const{
        if(fabs(x-outer.x)>EPS){
            return x<outer.x;
        }
        return y<outer.y;
    }

    bool operator == (const Point &outer) const{
        return (fabs(x-outer.x)<EPS&&fabs(y-outer.y)<EPS);
    }
    Point operator + (const Point &p){ return Point(x+p.x,y+p.y);}
    Point operator - (const Point &p){ return Point(x-p.x,y-p.y);}
    Point operator * (double c){ return Point(x*c,y*c);}
    Point operator / (double c){ return Point(x/c,y/c);}
};

ostream& operator <<(ostream &os,Point outer){
    os<<fixed<<setprecision(4)<<outer.x<<" "<<outer.y;
}

double dot(Point p,Point q){ return p.x*q.x+p.y*q.y;}
double dist2(Point p,Point q){ return dot(p-q,p-q);}

double dist(Point a,Point b){
    return hypot(a.x-b.x,a.y-b.y);
}

Point rotateCCW(Point p,double theta){
    double rad=acos(-1.0)/180.0*theta;
    return Point(p.x*cos(rad)-p.y*sin(rad),p.x*sin(rad)+p.y*cos(rad));
}

///===========================line===========================

class Line{
public:
    double a,b,c;
};

ostream& operator<<(ostream &os,Line l ){
    os<<fixed<<setprecision(2)<<l.a<<"x+"<<l.b<<"y"<<"+("<<l.c<<") = 0";
}

void lineFromGradient(Point p,double grad,Line &l){
    l.a=-grad;
    l.b=1.0;
    l.c=-p.y+grad*p.x;
}

void pointstoLine(Point p1,Point p2,Line &l){
    if(fabs(p1.x-p2.x)<EPS){
        l.a=1.0, l.b=0.0,l.c=-p1.x;
    }
    else{
        l.a=-(p1.y-p2.y)/(p1.x-p2.x);
        l.b=1.0;
        l.c=-(l.a*p1.x)-p1.y;
    }
}

bool areParallel(Line l1,Line l2){
    return (fabs(l1.a-l2.a)<EPS&&fabs(l1.b-l2.b)<EPS);
}

bool areSame(Line l1,Line l2){
    return areParallel(l1,l2)&&(fabs(l1.c-l2.c)<EPS);
}

bool areIntersect(Line l1,Line l2,Point &p){
    if(areParallel(l1,l2)) return false;

    p.x=(l2.b*l1.c-l1.b*l2.c)/(l2.a*l1.b-l1.a*l2.b);
    if(fabs(l1.b)>EPS) p.y=-(l1.a*p.x+l1.c);
    else p.y=-(l2.a*p.x+l2.c);
    return true;
}

void closestPoint(Line l,Point p, Point &ans){
    Line perpendicular;
    if(fabs(l.b)<EPS){
        ans.x=-l.c,ans.y=p.y; return;
    }
    if(fabs(l.a)<EPS){
        ans.x=p.x,ans.y=-l.c; return;
    }

    lineFromGradient(p,1/l.a,perpendicular);
    areIntersect(l,perpendicular,ans);
}

///============vector&circle===================

class Vector{
public:
    double x,y;
    Vector(double _x,double _y):x(_x),y(_y){}
};

Vector toVec(Point a,Point b){
    return Vector(b.x-a.x,b.y-a.y);
}

Vector scale(Vector v, double s){
    return Vector(v.x*s,v.y*s);
}

Point translate(Point p,Vector v){
    return Point(p.x+v.x,p.y+v.y);
}

double dot(Vector a,Vector b){ return (a.x*b.x+a.y*b.y);}
double magnitude_sqr(Vector v){ return v.x*v.x+v.y*v.y; }

double distToLine(Point p,Point a,Point b,Point &c){
    Vector ap=toVec(a,p),ab=toVec(a,b);
    double u=dot(ap,ab)/magnitude_sqr(ab);
    c=translate(a,scale(ab,u));
    return dist(p,c);
}

double distToLineSegment(Point p,Point a,Point b, Point &c){
    Vector ap=toVec(a,p),ab=toVec(a,b);
    double u=dot(ap,ab)/magnitude_sqr(ab);
    if(u<0.0){
        c=Point(a.x,a.y);
        return dist(p,a);
    }
    if(u>1.0){ c=Point(b.x,b.y); return dist(p,b);}
    return distToLine(p,a,b,c);
}

double angle(Point a,Point o,Point b){
    Vector oa=toVec(o,a),ob=toVec(o,b);
    return acos(dot(oa,ob)/sqrt(magnitude_sqr(oa)*magnitude_sqr(ob)));
}

double cross(Vector a,Vector b){
    return a.x*b.y-a.y*b.x;
}

bool ccw(Point p,Point q,Point r){
    return cross(toVec(p,q),toVec(p,r))>0;
}

bool collinear(Point p,Point q,Point r){
    return fabs(cross(toVec(p,q),toVec(p,r)))<EPS;
}

int insideCircle(Point p, Point center,double r){
    double dx=p.x-center.x,dy=p.y-center.y;
    double dis=hypot(dx,dy);
    return fabs(dis-r)<EPS? 1 : dis<r? 0: 2;
}

double chordLength(double r,double ang){
    return 2*r*sin(ang/2);
}

double sectorArea(double r,double ang){
    double pi=acos(-1.0);
    return (ang/(pi*2))*pi*r*r;
}

double segmentArea(double r,double ang){
    double sArea=sectorArea(r,ang);
    double chordL=chordLength(r,ang);
    double triArea=0.5*chordL*sqrt(r*r-chordL*chordL/4);
    return sArea-triArea;
}

bool circle2PtsRadius(Point p1,Point p2,double r,Point &c){
    double dis2=(p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
    double det=r*r/dis2-0.25;

    if(det<0.0) return false;
    double h=sqrt(det);
    c.x=(p1.x+p2.x)*0.5+(p1.y-p2.y)*h;
    c.y=(p1.y+p2.y)*0.5+(p2.x-p1.x)*h;
    return true;
}

bool circleCenter(Point p1,Point p2, Point p3,Point &ctr){
    Point m1=(p1+p2)/2;
    Point m2=(p1+p3)/2;
    if(collinear(p1,p2,p3)) return false;

    Line l1,l2;
    if(fabs(p1.y-p2.y)<EPS){
        l1.a=1.0,l1.b=0.0,l1.c=-m1.x;
    }
    else{
        double grad;
        if(fabs(p1.x-p2.x)<EPS){
            grad=0.0;
        }
        else {
            grad=(p1.y-p2.y)/(p1.x-p2.x);
            grad=-1.0/grad;
        }
        lineFromGradient(m1,grad,l1);
    }

    if(fabs(p1.y-p3.y)<EPS){
        l2.a=1.0,l2.b=0.0,l2.c=-m2.x;
    }
    else{
        double grad;
        if(fabs(p1.x-p3.x)<EPS){
            grad=0.0;
        }
        else {
            grad=(p1.y-p3.y)/(p1.x-p3.x);
            grad=-1.0/grad;
        }
        lineFromGradient(m2,grad,l2);
    }

    areIntersect(l1,l2,ctr);

    return true;
}

void reflectionPoint(Line l,Point p,Point &ans){
    Point temp;
    closestPoint(l,p,temp);
    Vector v=toVec(p,temp);
    ans=translate(translate(p,v),v);
}

///==================triangle==================

double area(double ab,double bc,double ca){
    double s=(ab+bc+ca)/2.0;
    double val=s*(s-ab)*(s-bc)*(s-ca);
    if(val>=0.0){
        return sqrt(val);
    }
    else return -INF;
}

double rIncircle(double ab,double bc,double ca){
    return area(ab,bc,ca)/(0.5*(ab+bc+ca));
}

int inCircle(Point p1,Point p2,Point p3,Point &c,double &r){
    r=rIncircle(dist(p1,p2),dist(p2,p3),dist(p3,p1));
    if(fabs(r)<EPS) return 0;

    Line l1,l2;
    double ratio=dist(p1,p2)/dist(p1,p3);

    Point p=translate(p2,scale(toVec(p2,p3),ratio/(1+ratio)));
    pointstoLine(p1,p,l1);

    ratio=dist(p2,p1)/dist(p2,p3);
    p=translate(p1,scale(toVec(p1,p3),ratio/(1+ratio)));
    pointstoLine(p2,p,l2);

    areIntersect(l1,l2,c);
    return 1;
}

double rCircumCircle(double ab,double bc,double ca){
    return ab*bc*ca/(4.0*area(ab,bc,ca));
}

int circumCircle(Point p1,Point p2,Point p3,Point &c,double &r){
    if(collinear(p1,p2,p3)) return 0;

    Line l1,l2;
    Point m1=Point((p1.x+p2.x)/2,(p1.y+p2.y)/2),m2=Point((p1.x+p3.x)/2,(p1.y+p3.y)/2);
    if(fabs(p1.y-p2.y)<EPS){
        l1.a=1.0,l1.b=0.0,l1.c=-m1.x;
    }
    else{
        double grad;
        if(fabs(p1.x-p2.x)<EPS){
            grad=0.0;
        }
        else {
            grad=(p1.y-p2.y)/(p1.x-p2.x);
            grad=-1.0/grad;
        }
        lineFromGradient(m1,grad,l1);
    }

    if(fabs(p1.y-p3.y)<EPS){
        l2.a=1.0,l2.b=0.0,l2.c=-m2.x;
    }
    else{
        double grad;
        if(fabs(p1.x-p3.x)<EPS){
            grad=0.0;
        }
        else {
            grad=(p1.y-p3.y)/(p1.x-p3.x);
            grad=-1.0/grad;
        }
        lineFromGradient(m2,grad,l2);
    }

    areIntersect(l1,l2,c);
    r=dist(c,p1);

    return 1;
}

bool inCircumCircle(Point A,Point B,Point C,Point p){
    Point ctr;
    double r;
    if(circumCircle(A,B,C,ctr,r)==1){
        if(dist(ctr,p)<=r){
            return true;
        }
        else return false;
    }
    else return false;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Point p1=Point(2,2),p2=Point(6,5);
    cout<<dist(p1,p2)<<endl;
    Point p3=Point(10,3);
    p3=rotateCCW(p3,90);
    cout<<p3<<endl;
    p3=rotateCCW(Point(10,3),90-180*atan(3.0/10)/PI);
    cout<<p3<<endl;

    vector<Point> vec;
    vec.pb(Point(2,3));
    vec.pb(Point(3,4));
    vec.pb(Point(2,2));
    vec.pb(Point(-1,2));
    vec.pb(Point(-1,0));

    sortv(vec);
    for(int i=0;i<vec.size();i++){
        cout<<vec[i]<<endl;
    }

    p1=Point(2,2);
    p2=Point(2,3);
    Line l;
    pointstoLine(p1,p2,l);
    cout<<l<<endl;

    p1=Point(3,2);
    Vector v=toVec(Point(2,2),Point(4,3));
    p1=translate(p1,v);
    cout<<p1<<endl;

    v=scale(v,0.5);
    p1=translate(Point(3,2),v);
    cout<<p1<<endl;
    p1=translate(Point(3,2),scale(v,2));
    cout<<p1<<endl;
    p1=rotateCCW(p1,90);
    cout<<p1<<endl;

    p1=rotateCCW(Point(3,2),90);
    v=toVec(Point(2,2),Point(4,3));
    p1=translate(p1,v);
    cout<<p1<<endl;

    v=toVec(Point(2,1),Point(0,0));
    p1=translate(Point(3,2),v);
    p1=rotateCCW(p1,90);
    p1=translate(p1,toVec(Point(0,0),Point(2,1)));
    cout<<p1<<endl;

    pointstoLine(Point(0,6),Point(0,9.11),l);
    closestPoint(l,Point(6,5),p1);
    cout<<p1<<endl;

    reflectionPoint(l,Point(6,5),p1);
    cout<<p1<<endl;

    double ang=angle(Point(2,0),Point(0,0),Point(0,2))*180/PI;
    cout<<ang<<endl;

    p1=Point(2,0),p2=Point(3,0),p3=Point(-3,-1);
    if(!collinear(p1,p2,p3)){
        if(ccw(p1,p2,p3)){
            cout<<"p3 is in left is of P1P2"<<endl;
        }
        else cout<<"right"<<endl;
    }
    else cout<<"colinear"<<endl;

    return 0;
}

