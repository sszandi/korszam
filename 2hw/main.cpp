#include "vector2.h"
#include <iostream>

//using namespace std;

int main()
{
    vector2<double> v1{},v2{};

    std::cout << "Enter the first vector:\n";
    std::cin >> v1;
    std::cout << "Enter the second vector:\n";
    std::cin >> v2;
    double a;
    std::cout << "Enter a scalar:\n";
    std::cin >> a;
    
    std::cout << "\nv1 = (" << v1.x << "," << v1.y << ")\n";
    std::cout << "v2 = (" << v2.x << "," << v2.y << ")\n";
    std::cout << "a = " << a << "\n\n";

    vector2<double> u1{}, u2{};   //save initial values for later...
    u1=v1;
    u2=v2;
    double a1;
    a1=a;
  
    v1+=v2;   
    std::cout << "v1+=v2 = (" << v1.x <<"," << v1.y <<")\n";

    v1-=v2; 
    std::cout << "v1-=v2 = (" << v1.x <<"," << v1.y <<")\n\n";

    v1*=a;
    v2*=a;
    std::cout << "a*v1 = (" << v1.x << "," << v1.y << ")\n";
    std::cout << "a*v2 = (" << v2.x << "," << v2.y << ")\n\n";

    v1/=a;
    v2/=a;
    std::cout <<"v1/a = (" << v1.x << "," << v1.y << ")\n";
    std::cout << "v2/a = (" << v2.x << "," << v2.y << ")\n\n";
    
    double s;
    s=skalszorzat(v1,v2);
    std::cout << "v1*v2=" << s << "\n\n";

    vector2<double> w1{},w2{},w3{},w4{};
    w1=v1+v2;
    w2=v1-v2;
    w3=v1*a;
    w4=a*v1;
    std::cout << "w1 = v1 + v2 = (" << w1.x << "," << w1.y << ")\n";
    std::cout << "w2 = v1 - v2 = (" << w2.x << "," << w2.y << ")\n";
    std::cout << "w3 = a * v1 = (" << w3.x << "," << w3.y << ")\n";
    std::cout << "w3 = v1 * a = (" << w4.x << "," << w4.y << ")\n\n";

    double r1,r2;
    r1=hossz(v1);
    r2=hossz(v2);
    std::cout << "Length of vector v1 is: " << r1 << " \n";
    std::cout << "Length of vector v2 is: " << r2 << " \n\n";
    
    return 0;
}