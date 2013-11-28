#include <iostream>
#include <string>
using namespace std;

#include <boost/program_options.hpp>

// Alias para el namespace para acortarlo
namespace po = boost::program_options;

void notificado(int a){
    cout << "He sido notificado del valor " << a << endl;
}

int main(int argc, char *argv[])
{
    /*
      options_description es un contenedor para objetos
      option_description (ojo, sin s). Es la manera básica de definir
      la sintaxis y semántica de los argumentos que podemos recibir.

      Su constructor puede recibir el título que aparecerá en el
      bloque de ayuda.
    */
    po::options_description desc("Sintaxis");

    /*
      Para añadir opciones usamos el método add_options, que devuelve
      un objeto cuyo operador () usaremos para ir añadiendo cada opción.

      Las opciones tienen tres partes: 

      - Primero, definiremos el nombre del parámetro. Un parámetro
      puede tener un nombre largo, o un nombre corto y uno largo. El
      nombre corto es de una letra y se indica a partir de la coma.
         
      - Luego, debemos pasar la cadena con la descripción del
      argumento, que aparecerá en la ayuda. Este argumento siempre
      va en último lugar.

      - Por último, podemos aportar información semántica sobre el3
      valor recogido. Esto se hace pasando un tipo value_semantic,
      que es una clase paramétrica, normalmente la especialización
      po::value. Éste tipo de datos puede recibir una referencia
      donde albergar el contenido del valor leído, además del tipo
      de valor a leer y de opciones que se indican como métodos.
    */

    // En boost::1.42 se añadió -> required()
    desc.add_options()
	// Definición básica, sin aceptar valor
	("ayuda,h", "muestra el mensaje de ayuda")

	// Acepta un entero
	("velocidad,v", po::value<int>(), "Recibe un entero")

	// Acepta una cadena
	("archivo,a", po::value<string>(), "Recibe una cadena")

	// Acepta una serie de argumentos
	("numeritos,n", po::value<vector<string> >() -> multitoken(), "Varios argumentos")

	// Con valor por defecto
	("densidad,d",  po::value<int>() -> default_value(20), "Con valor por defecto")

	// zero_tokens indica que opcionalmente puede tener argumento
	("opcional,o", po::value<string>() -> zero_tokens(), "Opción con argumento opcional")

	// Llamar automáticamente a una función al leer este parámetro
	("llamador,l", po::value<int>() -> notifier(notificado), "Se ejecuta la opción al señalar la opción")

	;
	
    /*
      Lo siguiente es crear un objeto en el que almacenar las opciones
      leídas y los valores introducidos. Ese objeto es un variables_map.
     */
    po::variables_map mapaVariables;

    /*
      Para rellenar el variables_map, primero hay que parsear la línea
      de comandos. Se puede hacer de dos formas, en este ejemplo lo
      haremos de la forma sencilla, usando la función libre
      parse_command_line, que recibe argc, argv y la descripción de las opciones
     */
    po::store(po::parse_command_line(argc, argv, desc), mapaVariables);

    /*
      Por último, es necesario llamar a notify para que se ejecuten
      las notificaciones a las funciones
     */
    po::notify(mapaVariables);
    
    /*
      A partir de aquí podemos parsear las funciones casi como si de
      un mapa estándar se tratara, usando como claves los nombres
      largos de las opciones. Los elementos del mapa en realidad son
      del tipo boost::any, así que es necesario castearlos usando
      as<T>()
     */

    if(mapaVariables . count("ayuda")){
	cout << desc << endl;
	return 1;
    }

    if(mapaVariables . count("numeritos")){
	const vector<string> & num = mapaVariables["numeritos"].as< vector<string> >();
	for (size_t i = 0; i < num.size(); ++i)
	{
	    cout << num[i] << endl;
	}
    }
    return 0;
}
