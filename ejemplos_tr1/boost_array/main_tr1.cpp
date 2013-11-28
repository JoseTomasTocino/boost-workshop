//#include <boost/array.hpp>

#include <iostream>
#include <string>
#include <stdexcept>
#include <tr1/array>
using namespace std;

int main(int argc, char *argv[])
{
    /*
      Ejemplo 1: Inicialización básica de un boost::array
    */
  tr1::array<string, 3> primos = { {"Shurmano", "Shurprimo", "Shurperro"} };
    cout << primos[0] << endl
	 << primos[1] << endl
	 << primos[2] << endl;

    /*
      Ejemplo 2: Métodos típicos de los contenedores
     */

    // Tamaño
    cout << "Tamaño: " << primos.size() << endl;

    // Bound checking (comprobación de límites)
    try{
	cout << primos.at(4) << endl;
    }catch(std::out_of_range& s){
      cout << "Fuera de rango" << endl;
    }

    // Iteradores
    cout << *primos.begin() << endl
	 << *(primos.end()-1) << endl;

    // Operadores
    tr1::array<int, 4> yo = { {0, 1, 2, 3} };
    tr1::array<int, 4> another = { {0, 1, 2, 5} };
    cout << ((yo == another)?"Iguales":"Diferentes") << endl;

    return 0;
}
