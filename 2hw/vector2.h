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
    x*=a; y*=a;
    return *this;
}

vector2<T> operator/=( T const& a )   //skal.-al osztás
{
    x/=a; y/=a;
    return *this;
}
    
std::ostream& operator<<( std::ostream& o, vector2<T> const& v )
{
    o << v.x << "," << v.y;
    return o;

}   
    

};   

template<typename T>

T skalszorzat( vector2<T> const& v , vector2<T> const& u )  // skalaris szorzat
{
    return { v.x*u.x + v.y*u.y};
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
vector2<T> operator*( vector2<T> const& v,T const& a)  // skal.-al szorzas
{
    return vector2<T>{ a*v.x, a*v.y};
}

template<typename T>
vector2<T> operator*( T const& a, vector2<T> const& v)  // skal.-al szorzas
{
    return vector2<T>{ a*v.x, a*v.y};
}

template<typename T>
T hossz( vector2<T> const& v )  // normalas
{
    return sqrt( v.x*v.x+v.y*v.y );

}


template<typename T>
 std::istream & operator>>(std::istream& in, vector2<T> &v )
{
    in >> v.x;
    in >> v.y;
    return in;

}

template<typename T>
 std::ostream & operator<<(std::ostream& os, const vector2<T> &v )
{
    os << v.x << " " << v.y;
    return os;

}


