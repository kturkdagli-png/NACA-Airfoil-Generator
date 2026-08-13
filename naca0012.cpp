#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;

double thickness(double x , double t){
    return 5*t*(0.2969*sqrt(x)-0.1260*x-0.3516*pow(x,2)+0.2843*pow(x,3)-0.1015*pow(x,4));
}

int main(){
    ofstream airfoil("naca0012.dat");
    airfoil<<"NACA0012"<<endl;

    int N = 100;
    double t = 0.12;
    const double pi = 3.14159265;

    // upper surface TE -› LE
    for(int i=N-1; i>=0; i--){
        double theta = i*pi/(N-1);
        double x = 0.5*(1-cos(theta));
        double y = thickness(x,t);
        airfoil<<fixed<<setprecision(6)<<x<<" "<<y<<endl;
    }

    // lower surface LE -› TE (without TE)
    for(int i=1; i<N-1; i++){
        double theta = i*pi/(N-1);
        double x = 0.5*(1-cos(theta));
        double y = thickness(x,t);
        airfoil<<fixed<<setprecision(6)<<x<<" "<<-y<<endl;
    }

    airfoil.close();
}
