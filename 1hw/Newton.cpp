#include <iostream>
#include <cmath>
#include <iostream>
using namespace std;  

template<typename T, typename F, typename G>  

T Newton(F fgv, G d_fgv, T x_i, double err) // err -> ACCURACY
{
    double x_0 = x_i - fgv(x_i)/d_fgv(x_i);
    
    while(abs(x_0-x_i)>=err)
    {
        x_i=x_0;
        x_0 = x_i - fgv(x_i)/d_fgv(x_i);
    }
    
    return x_0;
}

//template<typename TT>

int main()
{
    cout << "Root of given function: " << Newton([](double x ) { return x*x-612.0;}, [](double x ) { return 2.0*x ;}, 10.0, 0.0001);
}
