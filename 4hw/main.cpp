#include <iostream>
#include <fstream>
#include <math.h>


template<typename U> 
U dfun(U y)
{   
    return 1 + pow(y,2);
}


template<typename U> 
U NewtonMethod(U (*df)(U y), U y0, double t0, double h, double T)  // T total time
{
    U y = y0;
    double b = (T - t0)/h;  // *

    for(int i=1; i<=b; i++)
    {
        y = y + h*df(y);
    }

return y;

}

template<typename U> 
U RK4Method(U (*df)(U y), U y0, double t0, double h, double T)
{
    double k1, k2, k3, k4, b;
    
    U y = y0;
    b = (T - t0)/h;   // *

    for(int i=1; i<=b; i++)    
    {
        k1 = df(y);
        k2 = df(y+h*k1/2);
        k3 = df(y+h*k2/2);
        k4 = df(y+h*k3);
        y = y + (k1 + k4 + 2 * (k2 + k3)) * (h /6);

    }   
    
return y;

}

template<typename U> 
U analitikusan(U T)
{
    return tan(T);
}



int main()
{   
    double y0, t0, T, h, h2, q1, q2 ,q3;
    y0 = 0;
    t0 = 0;
    T = 1;
    h = 0.001;
    h2 = 0.005;
    
    std::ofstream file;
    file.open("Results4.txt");
    q1 = NewtonMethod(dfun, y0, t0, h, T);
    q2 = RK4Method(dfun, y0, t0,  h,  T);
    q3 = analitikusan(T);

        
    file<< "Newton \t \t" << "Runge-Kutta \t" << "Analitikus \n";
    file<< q1 << " \t " << q2 << " \t" << q3;   
    
    // std::cout << q1 << ", \t " << q2 << ", \t" << q3;   
    
    return 0;
}
