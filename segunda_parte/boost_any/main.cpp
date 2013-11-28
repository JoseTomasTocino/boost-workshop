#include <iostream>
#include <string>

using namespace std;

#include <boost/any.hpp>
#include <boost/unordered_map.hpp>

void fun(boost::unordered_map<string, boost::any> & mapa){
    if(mapa.count("número")){
	cout << "Se recibió el número: "
	     << boost::any_cast<int>(mapa["número"]) << endl;
    }

    if(mapa.count("cadena")){
	cout << "Se recibió la cadena: " 
	     << boost::any_cast<string>(mapa["cadena"]) << endl;
    }
}

int main(int argc, char *argv[])
{
    /* 
       Ejemplo básico de almacenamiento y acceso
    */
    boost::any cualquiera = 5;
    cualquiera = string("Hola");

    cout << boost::any_cast<string>(cualquiera) << endl;

    /*
      Acceso erróneo sin levantar excepciones
     */
    boost::any num = 5;
    string * a;
    if (!(a = boost::any_cast<string>(&num))){
	cout << "No es una cadena" << endl;
    }

    /*
      Aplicación: parámetros variables para una función
     */
    boost::unordered_map<string, boost::any> argumentos;
    argumentos["número"] = 5;
    argumentos["cadena"] = string("Pepito grillo");
    fun(argumentos);

    return 0;
}
