#include <iostream>
#include <ostream>
#include "vector2.h"

using namespace std;

int main()
{
    vector2<int> v1{2,8}, v2{2,4};

    /*
    cout << "Enter the first vector:\n";
    cin >> v1;
    cout << "Enter the second vector:\n";
    cin >> v2;
    */

    vector2<int> u1;
    v1+=v2;
    u1=v1;

    cout << "v1+=v2 = \n" << u1;




}
