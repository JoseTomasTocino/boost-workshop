#include <iostream>
#include <string>
using namespace std;

#include <boost/functional/hash.hpp>

class alumno{
    string nombre;
public:
    alumno(string n = "Godofredo") : nombre(n){ }

    friend std::size_t hash_value(const alumno & a);
};

std::size_t hash_value(const alumno & a){
    boost::hash<std::string> string_hash;
    return string_hash(a.nombre);
}

int main()
{
    /*
      Ejemplo 1: Hashing de tipos básicos
    */
    boost::hash<std::string> string_hash;
    cout << "Hash de cadena: " 
	 << string_hash("Don't hash me, bro!") << endl;


    /*
      Ejemplo 2: Hashing de tipos creados por el usuario

      Es necesario que creemos una función hash_value que reciba como
      argumento un tipo de datos que queremos hashear. Dentro de ella,
      seremos nosotros los que manualmente elegiremos los criterios
      para generar el hash, teniendo en cuenta los atributos, por ejemplo.

      Es bueno fijarse en los operadores de igualdad a la hora de
      escribir la función de hash, ya que si dos objetos son iguales,
      deben tener el mismo hash.
    */

    boost::hash<alumno> alumno_hash;
    cout << "Hash de tipo personalizado: "
	 << alumno_hash(alumno("Juanito")) << endl;

}
