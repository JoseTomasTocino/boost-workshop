#include <iostream>
using namespace std;

#include <boost/bind.hpp>
#include <boost/function.hpp>

int myFun(int a, int b, int c){
    cout << "MyFun: " << endl
	 << "\ta: " << a << endl
	 << "\tb: " << b << endl
	 << "\tc: " << c << endl;
 
    return a + b * c;
}

class miClase{
public:

    void hacerSuma(int a){
	cout << "Hago una suma: " << a << endl;
    }

    void hacerResta(int a){
	cout << "Hago una resta: " << a << endl;
    }

    void hacerAlgo(int a){
	cout << "Hago algo con " << a << endl;
    }
};

int main(int argc, char *argv[])
{
    /*
      Ejemplo 1: creamos un objeto función que abstrae dos de los
      argumentos de la función myFun.
    */
    boost::function<int(int)> f = boost::bind(myFun, 2, 3, _1);
    cout << "Retorno de la función: " << f(1) << endl;


    /*
      Ejemplo 2: Bindeamos a un método de una clase, de un objeto
      concreto.
    */

    miClase c;
    boost::function<void(int)> miMetodo = boost::bind(&miClase::hacerAlgo, c, _1);
    miMetodo(2);
    

    /*
      Ejemplo 3: Bindeamos a un método de una clase, pero sin pasarle
      ningún objeto de esa clase en el momento de la creación, sino al
      realizar la llamada.
    */
    
    boost::function<void(miClase, int)> operacion;

    if(1 == 0){
	operacion = boost::bind(&miClase::hacerSuma, _1, _2);
    }else{
	operacion = boost::bind(&miClase::hacerResta, _1, _2);
    }

    operacion(c, 2);

    return 0;
}
