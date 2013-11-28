#include <iostream>
using namespace std;

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

#include <boost/random/variate_generator.hpp>

#include <fstream>
#include <map>
#include <ctime>

int main(int argc, char *argv[])
{
    cout << "* Inicio de la ejecución." << endl;

    /*
      En boost::random tenemos dos conceptos principales. Por un lado
      están los generadores aleatorios, de los que hay una gran
      variedad, según rendimiento, aleatoriedad efectiva y otros
      parámetros.
     */

    boost::mt19937 generador;
    
    /*
      Opcionalmente, podemos cambiar la semilla.
    */
    generador.seed(std::time(0));

    /*
      Se pueden usar directamente, aunque no es lo habitual.
      Devuelve un entero en el rango [0 , 2^32)
     */
    cout << "Min: " << generador.min() << endl
	 << "Max: " << generador.max() << endl
	 << "Generar aleatorio: " << generador() << endl;

    /*
      Por otro lado tenemos las distribuciones. Boost provee las más
      típicas distribuciones estadísticas: uniforme entera y real,
      gausiana(normal), bernoulli, etc
     */
    boost::uniform_real<> distribucionNormal(0,5);

    /* 
       Finalmente unimos el generador a la distribución para obtener
       un objeto función que nos devolverá los números aleatorios.
     */

    boost::variate_generator<boost::mt19937&, boost::uniform_real<> > 
	obj(generador, distribucionNormal);

    fstream fichero;
    fichero.open("números", fstream::out);

    cout << "Generando 1000 reales aleatorios..." << endl;
    for(long i = 0; i < 1e3; ++i){
	fichero << obj() << endl;
    }
    cout << "Salida generada en el fichero «números»" << endl;
    fichero.close();

    cout << "* Fin de la ejecución." << endl;
    return 0;
}
