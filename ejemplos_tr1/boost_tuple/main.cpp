#include <iostream>
#include <string>
using namespace std;

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

boost::tuple<int, string> miFuncion(){
    return boost::make_tuple(5, "Cadena");
}

template <typename T>
int tupleLength(T t){
    return boost::tuples::length<T>::value;
}

int main(int argc, char *argv[])
{
    /*
      Ejemplo 1: Construcción de una tupla básica
    */
    boost::tuple<int, string, string> miTupla(1, "Cisco", "Caca"), otraTupla;

    // También podemos utilizar make_tuple
    otraTupla = boost::make_tuple(2, "Linksys", "Guachi");
    
    // Acceso a los elementos por separado
    cout << miTupla.get<0>() << endl
	 << miTupla.get<1>() << endl
	 << miTupla.get<2>() << endl;
    cout << tupleLength(miTupla) << endl;

    // get nos devuelve una referencia, por lo que sirve tanto para leer como para escribir
    miTupla.get<2>() = "Good";
    
    /*
      Ejemplo 2: Podemos usar las opciones de flujo avanzado
      contenidas en el fichero de cabecera tuple_io.hpp, que nos
      permitirán definir e imprimir tuplas utilizando los operadores
      de inserción y extracción respectivamente.

      En este ejemplo, debemos escribir la tupla abriendo y cerrando
      con comillas, y separando los campos con comas.

      Nota: Según la referencia, la inserción con cadenas no suele
      funcionar, porque es difícil distinguir entre delimitadores y
      valores propios.
     */

    boost::tuple<int, int, int, int> telefono;

    cout << "Escribe la tupla en el formato *956-26-36-36*" << endl;
    cin >> boost::tuples::set_open('*') 
	>> boost::tuples::set_close('*')
	>> boost::tuples::set_delimiter('-');
    cin >> telefono;

    cout << boost::tuples::set_open('[') 
	 << boost::tuples::set_close(']')
	 << boost::tuples::set_delimiter('-')
	 << telefono << endl;
     

    /*
      Ejemplo 3: Los tiers son unas tuplas especiales en las que todos
      los elementos son referencias. Resultan muy útiles para asignar
      varias variables de una vez, especialmente usando el valor de
      retorno de una función.

      Se crean usando la función boost::tie
     */

    int valor;
    string cadena;

    boost::tie(valor, cadena) = miFuncion();
    cout << valor << " , " << cadena << endl;

    /*
      Si la función devuelve una 2-upla pero solo nos interesa uno de
      los valores, podemos utilizar ignore.
    */

    int otroValor;
    boost::tie(otroValor, boost::tuples::ignore) = miFuncion();
    cout << otroValor << endl;

 return 0; 
}
