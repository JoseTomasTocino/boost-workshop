#include <iostream>
using namespace std;

#include <boost/scoped_ptr.hpp>

/*
  Vamos a crear una clase que informe de cuándo se crea y cuando se
  destruye, y lleve un contador de elementos creados.

 */

class Elemento
{
    static int counter;
    int n;
public:
    Elemento():n(++counter){
	cout << "* Creando Elemento " << n << endl;
    };

    void lanzar(const char * msg){
	cout << "* Elemento " << n << " says: " << msg << endl;
    };

    virtual ~Elemento(){
	cout << "* So Long, Elemento " << n << endl;
    };
};

int Elemento::counter = 0;

int main(int argc, char *argv[])
{
    
    /*
      Utilizamos corchetes para abrir un nuevo entorno (scope) Vemos
      que al terminar el scope, el scoped pointer se libera
      automáticamente, mientras que en el caso del puntero clásico, si
      no liberamos manulmente se produciría una fuga de memoria.
    */

    cout << "Inicio del scope" << endl;
    {
	boost::scoped_ptr<Elemento> miElemento(new Elemento());
	miElemento -> lanzar("Mensaje desde myFun_1");
    
	Elemento * classicPointer = new Elemento();
	classicPointer -> lanzar ("Mensaje del elemento con puntero clásico");

	delete classicPointer; // Necesario borrarlo manualmente!
    }
    cout << "Fin del scope" << endl;

    /*
      Si tenemos un scoped pointer como atributo de una clase, o como
      variable suelta, es posible asignarle un valor utilizando el
      método reset, que borrará lo que estuviera contenido en el
      puntero previamente.
     */

    boost::scoped_ptr<string> ptrCadena;
    ptrCadena.reset(new string("Hola"));

    /*
      Los operadores habituales se conservan. En el caso del *, se
      devuelve una referencia &. Para acceder al puntero en bruto se
      utiliza el método get(), aunque NO SE RECOMIENDA, ya que hacer
      modificaciones o borrar el objeto apuntado a través de get()
      puede producir errores.
     */

    cout << "Longitud de cadena: " << ptrCadena -> length() << endl;
    cout << *ptrCadena << endl;

    return 0;
}

