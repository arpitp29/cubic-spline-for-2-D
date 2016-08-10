/*
NAME-ARPIT PADWEKAR
ROLL NUMBER - 130123009
DEPT- M&C
*/
#include<iostream>
#include<fstream>
using namespace std;


class cubicspline{
	public:
	double *x, *y;
    int n;
	double *a,*b,*c,*d;
	void set(double *x_n,double *y_n,int n_n);
	double f(double x_point);
};
/*
this class is for creating cubicsplines 
x is the x-coordinate and y is the y-coordinate of the point 
x should be strictly increasing 
S[j](x)=a[j]+b[j](a-a[j])+c[j](a-a[j])^2 +d[j](a-a[j])^3 
*/

void cubicspline::set(double *x_n,double *y_n,int n_n){
	n=n_n;
	//setting x,y,a,b,c,d as double array of size n
	x=new double[n];
	y=new double[n];
	a=new double[n];
	b=new double[n];
	c=new double[n];
	d=new double[n];
	
	/*
	initializing arrays x ,y and a
	*/
	for(int i=0;i<n;i++){
		x[i]=x_n[i];
		y[i]=y_n[i];
	    a[i]=y[i];
	}
	
	/*
	this is to solve the tridigonal linear system 
	h->the step size of (x[i+1]-x[i]) for every i=0....n-1
	*/
	double h[n];
	for(int i=0;i<=n-2;i++){
		h[i]=x[i+1]-x[i];
	}
	double al[n];
	for(int i=1;i<=n-2;i++){
		al[i]=(3/h[i])*(a[i+1]-a[i]) -(3/h[i-1])*(a[i]-a[i-1]);
	}
	
	double l[n],u[n],z[n];
	l[0]=1;u[0]=z[0]=0;
	l[n-1]=1;z[n-1]=0;c[n-1]=0;
	
	for(int i=1;i<=n-2;i++){
		l[i]=2*(x[i+1]-x[i-1])-h[i-1]*u[i-1];
		u[i]=h[i]/l[i];
		z[i]=(al[i]-h[i-1]*z[i-1])/l[i];
		}
	
	/*
	calculating c,b,d for the equations
	*/
	for(int j=n-2;j>=0;j--){
		c[j]=z[j]-u[j]*c[j+1];
		b[j]=((a[j+1]-a[j])/h[j])-(h[j]/3)*(c[j+1]+2*c[j]);
		d[j]=(c[j+1]-c[j])/(3*h[j]);
	}
	
}  
  
/*
this returns the value of the y at given point x_p
*/
double cubicspline::f(double x_p){
	int i=x_p;
	double h_p=x_p-x[i];
	return a[i]+b[i]*h_p +c[i]*h_p*h_p+d[i]*h_p*h_p*h_p;
}


int main(){
	cubicspline s,s1;
/*
20 points are taken using the software (windig) and are used for cubic interploation
*/
double x[20]={-3.239909361,4.284095737,2.367653307,2.583345135,3.202945758,1.109332956,1.459991503,0.771845348,0.515507718,-0.41736298,0.06373035,-0.28990228,-0.656564226,-1.133975358,-1.545531794,-1.475145164,-2.268942076,-2.324175046,-0.391587594,-3.840532502};
double t[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
double y[20]={-2.13312562,0.234386064,-1.990794505,-4.538167398,-3.326582637,2.417221357,-1.612519473,-1.147854412,-2.151961479,-0.248123495,-1.103951282,-2.456026059,-1.671293018,-2.723693528,-1.750177029,-4.380541,-2.241325591,-3.617901147,-3.605721569,-4.717886985};
	s.set(t,x,20);
	s1.set(t,y,20);
	
   ofstream fp;
   fp.open("assignment1b.txt");
   double ti=0;
   
//now calculating the x and y coordinates at time =0.01*t where t=0...1900
   for(int i=0;i<1901;i++){
   int t=ti;
   fp<<" "<<s.f(ti)<<"     "<<s1.f(ti)<<endl;
   ti=ti+0.01;	
}
//now from these generated 2000 points we can replot the spiral using GNUPLOT 
	
	return 0;
}
