#include <iostream>
using std::cout;
using std::endl;

//Class for a pair of values of type T:
template<class T>
class Pair
{
public:
    Pair( );
    Pair(const T& firstValue, const T& secondValue);
    void setFirst(const T& newValue);
    void setSecond(const T& newValue);
    T getFirst( ) const;
    T getSecond( ) const;
private:
    T first;
    T second;
};

template<class T>
Pair<T>::Pair(const T& firstValue, const T& secondValue)
{
    first = firstValue;
    second = secondValue;
}

template<class T>
void Pair<T>::setFirst(const T& newValue)
{
    first = newValue;
}

template<class T>
void Pair<T>::setSecond(const T& newValue)
{
    second = newValue;
}


template<class T>
T Pair<T>::getFirst( ) const
{
    return first;
}

template<class T>
T Pair<T>::getSecond( ) const
{
    return second;
}


int main( )
{
    Pair<char> p('A', 'B');
    cout << "First is " << p.getFirst( ) << " Second is " << p.getSecond() << endl;
    p.setFirst('Z');
    cout << "First changed to " << p.getFirst( ) << endl;
    cout << "First is " << p.getFirst( ) << " Second is " << p.getSecond() << endl;

    return 0;
}
