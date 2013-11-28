#include <iostream>
#include <string>

using namespace std;

int tabulados;

#include <boost/shared_ptr.hpp>

/*
  Tenemos dos clases. La clase Mirador tiene un shared pointer a
  Observado. 
*/

string tab(){
    return string(tabulados, '\t');
}

struct Observado{
    Observado(){ cout << tab() << "+ Creando Observado" << endl; }
    ~Observado(){ cout << tab() << "- Borrando Observado" << endl; }
};

struct Mirador{
    boost::shared_ptr<Observado> fan;

    Mirador(){ cout << tab() << "+ Creando Mirador" << endl; }
    ~Mirador(){ cout << tab() << "- Borrando Mirador" << endl; }
};

/*
  La función popular rellena el atributo del Mirador con un shared
pointer a Observado.

*/

void popular(Mirador & m1, Mirador & m2){
    boost::shared_ptr<Observado> O(new Observado);
    m1.fan = O;
    m2.fan = O;
}

int main(int argc, char *argv[])
{
    tabulados = 0;
    cout << "-- Inicio" << endl;
    {
	tabulados ++;
	cout << tab() << "-- Inicio del primer scope" << endl;
	Mirador M1;
	{
	    tabulados ++;
	    cout << tab() << "-- Inicio del segundo scope" << endl;
	    Mirador M2;
	    popular(M1, M2);
	    cout << tab() << "-- Fin del segundo scope" << endl;
	}
	tabulados --;
	cout << tab() << "-- Final del primer scope" << endl;
    }
    tabulados--;
    cout << "-- Fin" << endl;
    
    return 0;
}
