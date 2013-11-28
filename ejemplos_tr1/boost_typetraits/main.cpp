#include <iostream>
using namespace std;

#include <boost/type_traits.hpp>

template <typename T>
void miAlgoritmo(T elemento, const boost::true_type&){
    cout << "Pues sí es un float" << endl;
}

template <typename T>
void miAlgoritmo(T elemento, const boost::false_type&){
    cout << "Vaya, parece que no es un float" << endl;
}

int main(int argc, char *argv[])
{
    float p = 5;
    miAlgoritmo(p, boost::is_floating_point<float>());
    return 0;
}
