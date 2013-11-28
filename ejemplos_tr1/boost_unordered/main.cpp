#include <iostream>
#include <set>
#include <cstdlib>
#include <iomanip>

using namespace std;

#include <boost/unordered_set.hpp>
#include <boost/timer.hpp>
#include <boost/array.hpp>

struct miClase{
    string i;
};

 size_t hash_value(const miClase & M){
    boost::hash<std::string> string_hash;
    return string_hash(M.i);
}	

bool operator==(const miClase& a, const miClase& b){
    return a.i == b.i;
}
#define num 2500000

int main(int argc, char *argv[])
{
    /*
      Ejemplo 1: Creación de un conjunto desordenado con un tipo de
      datos definido por el usuario. Es necesario definir una función
      de hashing y el operador de igualdad.
     */

    boost::unordered_set<miClase> conjunto;
    conjunto.insert(miClase());


    /*
      Ejemplo 2: Comparativa entre un set tradicional y un set no
      ordenado. Se crea una serie de 2.500.000 enteros y se accede a
      ellos en ambos contenedores, cronometrando el tiempo de acceso.
     */
    boost::timer t;

    int nGen;
    set<int> setClasico;
    boost::unordered_set<int> setUnordered;
    int * elementos = new int[num];
    
    for (long i = 0; i < num; ++i)
    {
	nGen = rand();
	setClasico.insert(nGen);
	setUnordered.insert(nGen);
	elementos[i] = nGen;
    }

    int p;
    t.restart();
    for (long i = 0; i < num; ++i)
    {
	p = *(setUnordered.find(elementos[i]));
    }
    cout << setw(30) << "boost::unordered_set: " << t.elapsed() << endl;

    t.restart();
    for (long i = 0; i < num; ++i)
    {
	p = *(setClasico.find(elementos[i]));
    }
    cout << setw(30) << "std::set: " << t.elapsed() << endl;


    delete elementos;
    return 0;
}
