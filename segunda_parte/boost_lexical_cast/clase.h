#ifndef _CLASE_H_
#define _CLASE_H_

#include <iostream>
using namespace std;

class myClass
{
public:
    myClass() : a("hola") { };
    void print(){
	cout << "myClass::print [a=\"" << a << "\"]" << endl;
    }
    string a;


    friend ostream& operator << (ostream &os, const myClass & M);
    friend istream& operator >> (istream &is, myClass & M);
};

inline ostream& operator << (ostream &os, const myClass & M){
//    os << "[[ Operator<< : " << M.a << " ]]";
    return os << M.a;
}

inline istream& operator >> (istream &is, myClass & M){
    is >> M.a;
    return is;
}


#endif /* _CLASE_H_ */
