#include <iostream>
#include <cmath>
using namespace std;


// Derivált - Richardson-extrapoláció:

double Fun(double x)    //  hiperbola
{
    const int  F = 900, a = 200, H = 35;
    const double  q = 1.8;

    return  F/q * ( cosh((q/F)*x) - cosh((q*a)/(2*F))  ) + H;
}

template <typename T>
T dFun2(T x, double h)  // másodrendű közelítés
{
    return Fun(x + h)-Fun(x - h) )/2*h;
}

template <typename T> 
T dFun4(T x, double h) // negyedrendű közelítés
{
    return ( 4*dFun2(x,h)-dFun2(x,h) )/2*h;
}

template <typename T>  
T dFun(T x, double h)  // hatodrendű közelítés
{
    return ( 16*dFun4(x, h)-dFun4(x, 2*h) )/15; //h kint
}

double f(double x)
{
    double df = dFun(x,1);
    return sqrt(1+(df*df));
}


// Integrál - Középpontos szabály:

double mid(double f(double x),double a, double b, int n)  //feloszt kint??
{
    double dx, M, m;
    dx = fabs(b-a)/n;
    
    for (int i=0; i<n; i++)
    {
        M += f( (a+(i*dx))/2) * dx;
    }

    return M;

}


// Integrál - trapéz-szabály:

double trpz(double f(double x), double a, double b, double n)
{
    double dx, sum, result;
    dx = fabs(b-a)/n;
    for( int i=1; i<n; i++ )
    {
        sum +=f(a+i*dx);
    }
    
    result = ( dx/2 )*( f(a)+f(b)+2*sum );

    return result;
}


// Integrál - 1/3 Simpson-szabály:

double simpson(double f(double x), double a, double b, int n)
{
    
    double k, dx, result;
   
    dx = fabs(a - b)/n;    
    result = f(a) + f(b);

    for(int i=1; i<= n-1; i++ )
    {
        k = a + i*dx;

    if(i%2==0)
    {
        result += 2 * (f(k));
    }
    else
    {
        result += 4 * (f(k));
    }

 }

    result *= n/3;

    return result;
}



int main()
{
   

    
    return 0;
}
