#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;

double thickness(double x , double t){
    return 5*t*(0.2969*sqrt(x)-0.1260*x-0.3516*pow(x,2)+0.2843*pow(x,3)-0.1015*pow(x,4));}
    
double camber(double m, double p, double x){
	if (0<=x && x<=p)
	return m/pow(p,2)*(2*p*x-pow(x,2));
	else if(p<=x && x<=1)
	return m/pow((1-p),2)*((1-2*p)+2*p*x-pow(x,2));}    
	
double dyc_dx(double m, double p, double x){
	if (0<=x && x<=p)
	return (2*m/pow(p,2))*(p-x);
	else if(p<=x && x<=1)
	return (2*m/pow((1-p),2))*(p-x);}  

int main(){
    ofstream airfoil("naca2412.dat");
    airfoil<<"NACA2412"<<endl;
    int N = 100;
    double m = 0.02; //max camber
    double p = 0.4; //camber location
	double t = 0.12; //max thickness
    const double pi = 3.14159265;

    // upper surface TE -› LE
    for(int i=N-1; i>=0; i--){
        double theta = i*pi/(N-1);
        double x = 0.5*(1-cos(theta));
        
        double yt =thickness(x,t);
        double yc =camber(m,p,x);
        double dy = dyc_dx(m,p,x);
        double tt =atan(dy); // tan(theta)=
        
        double xu = x - yt*sin(tt);
        double yu = yc + yt*cos(tt);
        
        airfoil<<fixed<<setprecision(6)<<xu<<" "<<yu<<endl;
    }

    // lower surface LE -› TE (without TE)
    for(int i=1; i<N-1; i++){
        double theta = i*pi/(N-1);
        double x = 0.5*(1-cos(theta));
        
        double yt =thickness(x,t);
        double yc =camber(m,p,x);
        double dy = dyc_dx(m,p,x);
        double tt =atan(dy); // tan(theta)=
        
        double xl = x + yt*sin(tt);
        double yl = yc - yt*cos(tt);
        
        airfoil<<fixed<<setprecision(6)<<xl<<" "<<yl<<endl;
    }

    airfoil.close();
}
