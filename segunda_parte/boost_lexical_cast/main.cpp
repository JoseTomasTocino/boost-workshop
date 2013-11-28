#include <iostream>
#include <string>

using namespace std;

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

using boost::format;

#include "clase.h"


int main(int argc, char *argv[])
{
    /*
      Ejemplo 1: Conversiones entre tipos normales
     */
    string cadena = "5.321";
    float num = boost::lexical_cast<float>(cadena);
    cout << "-- De cadena a flotante" << endl;
    cout << format("\"%1%\"  %|2$.6f|  %|2$.6e|  ") % cadena %  num << endl << endl;

    num = 3.14159265;
    cout << "-- De flotante a cadena" << endl
	 << format("%|.6f| \"%||\"") % num % boost::lexical_cast<string>(num) << endl << endl;

    /*
      Ejemplo 2: Conversiones entre tipos propios
    */


    cout << "** Pruebas con tipos propios" << endl
	 << "\tNuestro tipo tiene definidos los operadores de flujo." << endl
	 << "\tPuede convertirse de y hacia cualquier tipo que se pueda convertir de y hacia string." << endl;

    cadena = "Lorem Ipsum";

    cout << endl << "-- De cadena a myClass" << endl;
    try{
	myClass M = boost::lexical_cast<myClass>(cadena);
	M.print();
    }catch(boost::bad_lexical_cast&){
	cerr << "ZOMG ERROR" << endl;
    }
    
    cout << endl << "-- De flotante a myClass" << endl;
    try{
	myClass M = boost::lexical_cast<myClass>(num);
	M.print();
    }catch(boost::bad_lexical_cast&){
	cerr << "ZOMG ERROR" << endl;
    } //*/

    cout << endl << "-- Sentido inverso, de myClass a cadena" << endl;
    try{
	myClass A;
	string M = boost::lexical_cast<string>(A);
	cout << M << endl;
    }catch(boost::bad_lexical_cast&){
	cerr << "ZOMG ERROR" << endl;
    }

    return 0;
}
