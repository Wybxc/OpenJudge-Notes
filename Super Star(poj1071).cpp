
#include "iostream"
#include "cmath"
using namespace std;
const double eps = 1e-8;
const double board = 100 ;
const int dx[6]={1,0,-1,0,0,0};
const int dy[6]={0,1,0,-1,0,0};
const int dz[6]={0,0,0,0,1,-1};
double x[32],y[32],z[32];int n;
double curx,cury,curz,bestdis;
double sq(double x){return x*x;}
double dis(double x,double y,double z,double x1,double y1,double z1){
    return sqrt(sq(x-x1)+sq(y-y1)+sq(z-z1));
}
double maxround(double x0,double y0,double z0){
    double temp=0;
    for (int i = 0; i < n; i++) 
        temp=max(temp,dis(x0,y0,z0,x[i],y[i],z[i]));
    return temp;
}
void search(){
    double tempx,tempy,tempz;
    for(double t=100;t>eps;t*=0.9){
        for(int i = 0; i <6;i++){
            tempx=curx+dx[i]*t;
            tempy=cury+dy[i] *t;
            tempz = curz + dz[i] *t;
            
            double temp=maxround(tempx,tempy,tempz);
            if(temp<bestdis){
                curx=tempx ;
                cury = tempy;
                curz= tempz;
                bestdis=temp;
                break;
            }
        }
    }
    printf("%.5lf\n",bestdis);
    return;
}

int main(){
    while(cin>>n&&n!=0){
        curx=cury=curz=0;bestdis=0x3f3f3f3f;
        for (int i = 0; i < n; i++) 
            cin>>x[i]>>y[i]>>z[i];
        search();
    }
    return 0;
}
/*4
10.00000 10.00000 10.00000
10.00000 50.00000 50.00000
50.00000 10.00000 50.00000
50.00000 50.00000 10.00000
4
10.00000 10.00000 10.00000
20.00000 10.00000 10.00000
20.00000 20.00000 10.00000
10.00000 20.00000 10.00000
0*/