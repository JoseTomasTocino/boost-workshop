#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm> 
using namespace std;

#include <boost/bind.hpp> 
#include <boost/ref.hpp>
#include <boost/utility.hpp>

void add(int i, int j, std::ostream &os) 
{ 
  os << i + j << std::endl; 
} 

int main() 
{ 
    /* 
       Ejemplo 1: boost::bind siempre hace una copia de los
       argumentos; en los casos en los que no se pueda hacer copia,
       podemos usar boost::ref.
    */
    std::vector<int> v; 
    v.push_back(1); 
    v.push_back(3); 
    v.push_back(2); 
    
    std::for_each(v.begin(), v.end(), boost::bind(add, 10, _1, boost::ref(std::cout))); 
} 
