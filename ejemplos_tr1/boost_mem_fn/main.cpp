#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <functional>

using namespace std;

struct Clase
{
    string S;
    Clase(string s = "Hola") : S(s) {}

    void imprimir(){ 
	cout << "Texto contenido: " << S << endl;
    }
};

int main(int argc, char *argv[])
{
    /* 
       Ejemplo 1: Ejecución del método de una clase en varios
    elementos.
    */

    vector<Clase> elementos; 
    elementos.push_back(Clase("Mercurio"));
    elementos.push_back(Clase("Venus")); 
    elementos.push_back(Clase("La Tierra"));

    /*
      mem_fn debe apuntar a un método de la clase sobre la que se
      itera, no puede ser una función cualquiera.
    */
    cout << "* Ejecución directa" << endl;
    std::for_each(elementos.begin(), elementos.end(),
		  boost::mem_fn(&Clase::imprimir));


    /* 
       Ejemplo 2: Podemos asociar la función objeto a un
       boost::function que podremos ejecutar más tarde.
    */

    boost::function<void(Clase&)> punteroAlMetodo = boost::mem_fn(&Clase::imprimir);

    /*       
       Notar que al ser una función miembro, el primer argumento es un
       objeto de la clase cuyo método hay que ejecutar.
    */
    cout << "\n* Ejecución tras alojamiento" << endl;
    Clase objeto;
    punteroAlMetodo(objeto); 

    return 0;
}
