#include <iostream>
#include <cmath>
using namespace std;

// Derivált - Richardson-extrapoláció

double Fun(double x)    //  hiperbola
{
    const int  F = 900, a = 200, h = 35;
    const double  q = 1.8;

    return  F/q * ( cosh((q/F)*x) - cosh((q*a)/(2*F))  ) + h;

}

template <typename T>
T dFun(double x)
{

//no


}


// Középpontos szabály:




int main()
{
    
    return 0;
}
