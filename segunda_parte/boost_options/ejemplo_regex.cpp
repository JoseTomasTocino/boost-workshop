#include <iostream>
#include <fstream>
using namespace std;

#include <boost/regex.hpp>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>


#define foreach BOOST_FOREACH

namespace po = boost::program_options;

int main(int argc, char * argv[])
{

    po::options_description desc("Modo de empleo: ejecutable EXPR FICHERO1 FICHERO2...");
    desc.add_options()
	("expr", po::value<string>())
	("fich", po::value<vector<string> >() -> multitoken())
	("con-nombre,h", "Imprime el nombre del fichero junto a cada ocurrencia.")
	("con-linea,n", "Imprime la línea de la ocurrencia.")
	;

    po::positional_options_description argumentosPosicionales;
    argumentosPosicionales.add("expr", 1);
    argumentosPosicionales.add("fich", -1);

    po::variables_map mapaVariables;
    po::store(po::command_line_parser(argc, argv)
	      .options(desc)
	      .positional(argumentosPosicionales)
	      .run(),
	      mapaVariables);
    po::notify(mapaVariables);

    if(!mapaVariables . count("expr") || !mapaVariables . count("fich")){
	cout << desc << endl;
	return 1;
    }

    bool imprimirNombre = (bool) mapaVariables.count("con-nombre");
    bool imprimirLinea = (bool) mapaVariables.count("con-linea");

    string expr = mapaVariables["expr"].as<string>();
    vector<string> archivos = mapaVariables["fich"].as<vector<string> >();
    string lineaActual;

    fstream archivo;
    int numLinea;
    boost::regex patron(expr);
    boost::smatch resultado;

    foreach(string & s, archivos){
	numLinea = 1;

	archivo.open(s.c_str(), fstream::in);
	// Suponemos que existe
	while(getline(archivo, lineaActual)){
	    if(boost::regex_search(lineaActual, resultado, patron)){
		cout << ((imprimirNombre)? s + ":" : "")
		     << ((imprimirLinea)? boost::lexical_cast<string>(numLinea) + ":" : "")
		     << ((imprimirLinea | imprimirNombre)?" ":"")
		     << lineaActual 
		     << endl;
	    }
	    numLinea ++;
	}

	archivo.close();
    }
    return 0;
}
