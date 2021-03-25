#include <iostream>
#include <cmath>

template<typename T>

class vector2 
{
    public:
    T x,y;    

vector2<T> operator+=( vector2<T> const& v )    // +=
{
    x+=v.x; y+=v.y;
    return *this;
}

vector2<T> operator-=( vector2<T> const& v )    // -=
{
    x-=v.x; y-=v.y;
    return *this;
}

vector2<T> operator*=( T const& a)    //skal.-al szorzas
{
    x=a*x; y=a*y;
    return *this;
}

vector2<T> operator/=( T const& a )   //skal.-al osztás
{
    x=x/a; y=y/a;
    return *this;
}
    
std::ostream& operator<<( std::ostream& o, vector2<T> const& v )
{
    o << v.x << "," << v.y;
    return o;

}   
    

};   

template<typename T>

T skalszorzt( vector2<T> const& v , vector2<T> const& u )  // skalarszorzat
{
    return { v.x*u.x, v.y*u.y};
}

template<typename T>
vector2<T> operator+( vector2<T> const& v , vector2<T> const& u )  // 2 vektor összeadása
{
    return vector2<T>{ v.x+u.x, v.y+u.y};
}

template<typename T>
vector2<T> operator-( vector2<T> const& v , vector2<T> const& u )  // 2 vektor kivonása
{
    return vector2<T>{ v.x-u.x, v.y-u.y};
}

template<typename T>
vector2<T> operator*( T const& a)  // skal.-al szorzas
{
    return vector2{ a*x, a*y};
}

template<typename T>
double hossz( vector2<T> const& v )  // normalas
{
    return sqrt( v.x*v.x+v.y*v.y );

}
