/*
NAME-ARPIT PADWEKAR
ROLL NUMBER - 130123009
DEPT- M&C(13')
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
	cubicspline s,s1;//creating 2 objects of cubicspline
/*
21 points are taken using the software (windig) and are used for cubic interploation
*/
	double x[21]={	0,-0.864151417,-0.869801312,0.315546627,1.066417653,0.903135692,-0.009133997,-1.196930224,-1.879249192,-2.156847359,-1.789039204,-1.081484039,0.002165793,1.428199253,2.280768386,2.762139427,2.734643272,2.1994099,0.950029819,-0.810665746,-2.746131391443548};
	double y[21]={0,-0.09482406,0.90520731,1.098622053,0.1944505477, -0.904642330,-1.43290749,-1.192975297,-0.42251796,0.7123575755,1.610314196,2.37305000,2.56702972,2.15910731, 1.254370821,0.051696537,-1.081484039,-2.345177186, -3.204902853,-3.5617878,-2.984368624250603};
	double t[21]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	s.set(t,x,21);
	s1.set(t,y,21);
	  
  	ofstream fp;
   	fp.open("assignment1a.txt");
   	double ti=0;
   
   //now calculating the x and y coordinates at time =0.01*t where t=1...2000
   for(int i=0;i<2001;i++){
   int t=ti;
   fp<<" "<<s.f(ti)<<"     "<<s1.f(ti)<<endl;
   ti=ti+0.01;	
}

	//now from these generated 2000 points we can replot the spiral using GNUPLOT 
	return 0;
}
