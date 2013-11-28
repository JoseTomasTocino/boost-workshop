#include <iostream>
#include <string>
using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>

using namespace boost;

struct Padre;
struct Hijo;

// Habilitamos la clase para que pueda generar shared pointers de sí misma
struct Padre : public enable_shared_from_this<Padre>{
    string nombre;

    Padre (string n = "Darth Vader") : nombre(n){ cout << "Nace padre " << nombre << endl; }

    void hablar(){ cout << "Luke, yo soy tu padre" << endl; }

    ~Padre(){ cout << "Muere padre " << nombre << endl; }

    shared_ptr<Hijo> crearHijo(){
	return make_shared<Hijo>(shared_from_this());
    }
};


struct Hijo{
    shared_ptr<Padre> padre;

    Hijo(shared_ptr<Padre> p) : padre(p) {
	cout << "Nace Luke Skywalker" << endl;
    }
};

int main(int argc, char *argv[])
{
    // Creamos un objeto Padre usando la nueva técnica de make_shared
    shared_ptr<Padre> padre = make_shared<Padre>();

    // Creamos un hijo utilizando el método del padre ("el método" je je)
    shared_ptr<Hijo> h1 = padre -> crearHijo();
    
    // OMG matamos el puntero del padre :(
    padre.reset();
    
    // Pero el padre sigue vivo en el alma de sus hijos.
    h1 -> padre -> hablar(); 
    
    return 0;
}
