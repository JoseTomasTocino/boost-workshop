#include <iostream>
#include <string>
using namespace std;

#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <boost/tuple/tuple.hpp>

int main(int argc, char *argv[])
{
    /*
      El tipo de datos que se usa para definir la expresión regular es
      boost::regex, que recibe una cadena con la expresión regular y
      opcionalmente una serie de banderas en cortocircuito.

      Existe un tipo base basic_regex y dos especializaciones: regex y
      wregex, que usan caracteres normales y anchos, respectivamente.
      
      La sintaxis que podemos usar para definir las expresiones
      regulares es por defecto la usada en Perl, aunque podemos
      cambiarlo.

      Expresión: Una palabra y dos o más espacios+palabra, seguido de
      posibles espacios
    */

    boost::regex patron("\\w+(\\s+\\w+){2,}\\s*");

    /* 
       El otro tipo de datos importante es match_results, que guardará
       información sobre las ocurrencias encontradas al parsear la
       cadena con el patrón indicado.

       Es una clase paramétrica de la que hay cuatro typedefs
       incluídos en la biblioteca:
       - cmatch, para cadenas de C
       - wcmatch, para cadenas de C con caracteres anchos
       - smatch, para std::string
       - wsmatch, para std::wstring
     */
    boost::smatch resultado;

    string cadena;
    cout << "-- Prueba boost::regex_match" << endl;
    cout << "* Introduzca su nombre y apellidos: ";
    getline(cin, cadena);

    /*
      La primera de las funciones es regex_match, que comprueba si
      _toda_ la cadena concuerda con la expresión regular.

      Tiene sobrecargas varias, pero en todas ellas, siempre hay que
      pasarle en primer lugar la cadena (de forma directa, con
      punteros o con iteradores), un objeto match_results (que recibe
      por referencia), y la expresión regular.
      
     */
        
    while(!boost::regex_match(cadena, resultado, patron)){
	cout << "ERROR: Nombre y dos apellidos. ¿O es que eres americano? " << flush;
	getline(cin,cadena);
    }
    

    /*
      La siguiente función es regex_search, que simplemente busca
      alguna ocurrencia de la expresión regular en la cadena, sin
      necesidad de que toda ésta concuerde.
     */
    cout << endl << "-- Prueba boost::regex_search" << endl;
    cout << "* Escribe un nick, debe tener algún dígito y alguna letra: " << flush;
    patron = boost::regex("(\\d+.*?[[:alpha:]]+|[[:alpha:]]+.*?\\d+)");


    getline(cin, cadena);
    while(!boost::regex_search(cadena, resultado, patron)){
	cout << "MAL HECHOOO, inténtalo de nuevo: " << flush;
	getline(cin, cadena);
    }

    /*
      Por último tenemos regex_replace, que nos servirá para
      reemplazar cada ocurrencia de la expresión regular, utilizando
      un formateador con el que definiremos el destino.

      La sintaxis que se sigue a la hora de definir el reemplazo viene bien 
      explicada en http://www.boost.org/doc/libs/1_43_0/libs/regex/doc/html/boost_regex/format.html

      Hay multitud de opciones, lo más básico es saber hacer
      referencia a las cadenas encontradas. En la expresión regular,
      cada par de paréntesis forma un grupo. Podremos referirnos a
      ellos utilizando $N, siendo N > 0 una referencia al grupo
      N-ésimo.
      
     */
    cadena = "Vim es un gran editor. Vi se utiliza en entornos Unix desde hace muchos años, y es muy popular. A pesar de todo, vIm tiene una curva de aprendizaje muy dura.";

    /*
      Al definir la expresión regular podemos pasarle una bandera para
      que ignore la diferencia entre mayúsculas y minúsculas. 

      Ojo: Si le pasamos alguna flag, las flags por defecto
      (boost::regex::perl) se quitan, por lo que hay que indicarlas
      explicitamente.
     */
    cout << endl << "-- Prueba boost::regex_replace" << endl;
    patron = boost::regex("vim?", boost::regex::icase | boost::regex::perl);
    cout << "Cadena original: " << cadena << endl << endl
	 << "Cadena con reemplazo: " << boost::regex_replace(cadena, patron, "emacs") << endl;

    /* 
       El ejemplo previo es bastante genérico y no tiene en cuenta las
       mayúsculas después de punto. 

       Vamos a hacer otro ejemplo que bien serviría en el ministerio de
       igualdad.    
    */

    cout << endl << "-- Otro ejemplo de replace" << endl;
    patron.assign("(miembr)(o)(s?)", boost::regex::icase | boost::regex::perl);
    cadena = "Miembros del partido aseguran que el iPhone 4 incrementará su productividad, aunque el resto de miembros no piensan lo mismo. ";
    cout << boost::regex_replace(cadena,patron, "$1a$3") << endl;

    /*
      Además de las tres funciones, boost::regex nos ofrece dos tipos
      de iteradores que nos servirán para los casos en los que haya
      más de una ocurrencia de la expresión regular.

      El primero de esos iteradores es regex_iterator, que como en
      casos anteriores se trata de una clase paramétrica con
      diferentes typedef para cada tipo de caracter.

      Al dereferenciar el iterador obtenemos un objeto match_results
      con el que trabajar.
     */

    cout << endl << "-- Prueba boost::regex_iterator" << endl;
    patron.assign("([aeiou])|([bdfghjklmnpqrstvwxyz])");
    cadena = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum";

    boost::sregex_iterator inicial (cadena.begin(), cadena.end(), patron), final;
    int vocales, consonantes;
    vocales = consonantes = 0;

//    boost::tie(vocales, consonantes) = boost::make_tuple(0,0);
    while(inicial != final){
	boost::smatch m = *inicial;
	if(m[1].matched){
	    ++ vocales;

	}
	else if(m[2].matched){
	    ++ consonantes;
	}

	inicial++;
    }

    cout << boost::format("%|-16| : %||\n") % "Vocales" % vocales;
    cout << boost::format("%|-16| : %||\n") % "Consonantes" % consonantes;


    /*
      Por último, el otro tipo de iteradores es regex_token_iterator,
      que nos permitirá dividir una cadena en tokens utilizando el
      patrón regular como divisor.

      ¡Importante el -1!
     */

    cout << endl << "-- Prueba boost::regex_token_iterator" << endl;
    patron.assign("[\\s,]+");
    cadena = "boost, token iterator , c++ ";
    boost::sregex_token_iterator inicial_tok(cadena.begin(), cadena.end(), patron, -1), final_tok;

    cout << boost::format("Cadena: \"%s\"\n") % cadena;
    while(inicial_tok != final_tok){
	cout << *inicial_tok++ << endl;
    }
 }
