#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include <boost/format.hpp>
using boost::format;

int main(int argc, char *argv[])
{

    /*
      Hay tres tipos de formatos que pueden utilizarse:
      - %spec     típico de printf
      - %|spec|   como el de printf pero no es necesario indicar el tipo de datos
      - %N%       cuando no necesitemos formato, solo indicamos el número de argumento
     */

    // Formato simple: %N%
    cout << "* Formato simple: " << endl
	 << format("%1% %2% %3% %2% %1% \n") % "11" % "22" % "333";

    // Formato printf clásico: %spec. Imprescindible poner el type-char (s string, i int...)
    cout << "\n* Formato printf clásico: " << endl
	 << format("%i %s \n") % "11" % "Hola";

    // Formato nuevo: %|spec| En este caso el formato es por defecto, por lo que spec = ""
    cout << "\n* Formato nuevo: " << endl
	 << format("%|| %|| \n") % "11" % "Hola";

    /*
      El formato de spec es:
      [n$][flags][ancho][.precision][type-char]
      n indica el índice del argumento
      type-char es el tipo de datos, opcional en el formato nuevo
     */

    // Argumentos por posición
    // Tanto con el formato clásico como con el nuevo se pueden indicar los argumentos por posición
    cout << "\n* Argumentos por posición: " << endl
	 << format("%|2$| %1$i \n") % "11" % "hola";

    /*
      Flags y ancho
      - alinear izquierda
      = alinear centro
      _ alineación interna ¿?¿?
      + mostrar signo también para positivos
      # mostrar base numérica
      0 rellenar con ceros

      El ancho se indica con un número justo después de las flags
    */

    cout << "\n* Alineación y ancho de campos: " << endl << endl;

    // Campos de ancho 15, por defecto alineación a la derecha
    cout << format("|%|15||%|15||%|15||\n") % "Oficina" % "Software" % "Libre";

    // Idem, alineación centrada
    cout << format("|%|=15||%|=15||%|=15||\n") % "Oficina" % "Software" % "Libre";

    // Idem, alineación izquierda
    cout << format("|%|-15||%|-15||%|-15||\n") % "Oficina" % "Software" % "Libre";


    // Podemos incluir manipuladores de flujo para atributos concretos usando un io::group
    cout << "\n* Grupo con manipuladores (como setfill)" << endl;
    cout << format("|%|=15||%|=15||%|=15||\n") % boost::io::group(setfill('*'), "Oficina") % "Software" % "Libre";
    


    /*
      Con cualquiera de los tres tipos podemos utilizar la nueva
      opción de tabulado, que nos permitirá elegir la separación del
      campo respecto del lado izquierdo, siempre de forma absoluta,
      independientemente del tamaño de las anteriores cadenas.

      Se modela en estos dos elementos que se añaden siempre antes de
      la definición el formato de cada elemento en la cadena de
      formateo (spec): 
         - Con $|nt|, siendo n un número, añade un espaciado a la izquierda hasta rellenar n caracteres.
	 - Con $|nTX|, siendo n un número y X un caracter, lo mismo que lo anterior, pero usando el 
	 caracter X en vez de espacios.
     */

    cout << "\n* Tabulación absoluta" << endl;
    cout << format("%2% %|10t|%|1$| \n") % "Godofredo" % "A1";    
    cout << format("%2% %|10t|%|1$| \n") % "Godofredo" % "A12345";

    cout << "\n* Tabulación usando otro caracter como relleno" << endl;
    cout << format("%2% %|10T+|%|1$| \n") % "Godofredo" % "A1";
    cout << format("%2% %|10T+|%|1$| \n") % "Godofredo" % "A12345";

    
    cout << "\n* Otras opciones típicas, notación científica, etc" << endl;
    cout << format("%|30.5| \n") % 12312344.42345823904;
    cout << format("%|+30.5| \n") % 12312344.42345823904;  // Notación normal, indica los dígitos totales
    cout << format("%|+30.5e| \n") % 12312344.42345823904; // Notación científica, indica los dígitos tras el punto
    cout << format("%|+30.5f| \n") % 123123.42345823904;   // Notación flotante, indica los dígitos decimales
    cout << format("%|+30.5f| \n") % 6.5;

/*
0 	1 	2 	3 	4 	5 	6 	7 	8 	9 	A 	B 	C 	D 	E 	F
6 												┘ 	┐ 	┌ 	└ 	┼
7 				─ 			├ 	┤ 	┴ 	┬ 	│ 					
*/


    /*
      Problema con setw: para calcular los caracteres de relleno, la
      función cuenta los bytes, suponiendo un byte por caracter. Al
      usar tildes con utf-8, un caracter ocupa más de un byte, por lo
      que la función se lía y cuenta caracteres de más, reduciendo el
      espacio.

      Workaround: añadir un espacio más a setw o width por tilde o
      caracter raro
     */

    cout << "┌───────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "│ " << format("%|=70|") % "FACTURA" << "│" << endl;
    cout << "├───────────────────────────────────────────────────────────────────────┤" << endl;
    cout << "│ " << format("%|68|%|5|") % "A nombre de:" %  "│" << endl;
    cout << "│ " << format("%|68|%|5|") % "Fulanito de tal y cual" %  "│" << endl;
    cout << "│ " << format("%|69|%|5|") % "C/ Mengano 11, 3º A" %  "│" << endl;
    cout << "│ " << format("%|69|%|5|") % "11011  Cádiz" %  "│" << endl;
    cout << "│ " << format("%|68|%|5|") % "SPAIN" % "│" << endl;
    cout << "├──────────────────────────────────────────────────────────┬────────────┤" << endl;
    cout << "│ " << format("%|56| %|| %|+9.2f| %|4|") % "Gofres con Chocolate" % "│" % 3.50 % "│" << endl;
    cout << "│ " << format("%|56| %|| %|+9.2f| %|4|") % "Papas alinhadas con otros condimentos" % "│" % 23.50 % "│" << endl;
    cout << "├──────────────────────────────────────────────────────────┼────────────┤" << endl;
    cout << "│ " << format("%|56| %|| %|+9.2f| %|4|") % "Total" % "│" % 27.0065413 % "│" << endl;
    cout << "└──────────────────────────────────────────────────────────┴────────────┘" << endl << endl;

    return 0;
}
