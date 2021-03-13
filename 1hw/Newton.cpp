/*
Írjuk meg a Newton iterátort most általánosan úgy, hogy a függvény és a
deriváltja is az előbb bemutatott módon legyen átadva és a kezdő
paraméter típusa is általános T legyen.
*/

/* 
Newton([](double x ) { return x x 612.0; }, [](double x ) { return 2.0*x ; }, 10.0);
*/

// 1) fgv x_i helyen érték kiszamitasara egy fgv

// 2) f(x) derivaltjara egy fgv

// 3) maga a N-R formula for ciklusban, amig kisebb,egyenlo mind a megadott epsilon 

#include <iostream>
#include <cmath>
#include <iostream>

using namespace std;  //megnézni mashogy

template<typename T, typename F, typename G>  // G nélkül??



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
    cout<< Newton([](double x ) { return x*x-612.0;}, [](double x ) { return 2.0*x ;}, 10.0, 0.0001);
    cout<<"lol";
}
