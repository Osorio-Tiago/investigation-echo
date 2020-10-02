//
// Created by deine on 9/21/2020.
//
#include <iostream>
#include <fstream> //usar las funciones de escritura y lectura
#include <string.h> //pasar de string cadena de char
#include <vector>
#include <sstream>
#include "XMLSerialization.h"
using namespace xmls;
using namespace std;

struct Persona : public Serializable{
    xString nombre;
    xInt edad;
    xInt id;

    Persona();
    string toString();

};

//Definición de los métodos
Persona::Persona()
{
    setClassName("Persona");
    Register("Nombre", &nombre);
    Register("Edad", &edad);
    Register("Identificacion", &id);

}

string Persona::toString() {
    {
        ostringstream output;
        output << "Nombre: " << nombre.value() << endl;
        output << "Edad: " << edad.value() << endl;
        output << "Identificacion: " << id.value() << endl;

        return output.str();
    }
}

//-----------------------------------------------------------------------------


class VectorPersonas : public Serializable
{
public:
    Collection<Persona> array;

    VectorPersonas(){
        setClassName("Array de personas");
        for (int i = 0; i < array.size(); i++)
        {
            Register("Persona",array.getItem(i));
        }
    }

    std::string toString() {
        ostringstream out;
        for (int i = 0; i < array.size(); i++)
        {
            out << array.getItem(i)->toString();
        }
        return out.str();
    }

    void insertar(Persona* persona) {
        array.addItem(persona);
    }
};

class ServicioPersonasConPersistencia : public VectorPersonas
{
public:

    ServicioPersonasConPersistencia()
    {
        Register("VectorPersonas", &array);
    }

};



int main() {


    VectorPersonas* arrayPers = new ServicioPersonasConPersistencia();
/*
    auto* persona = new Persona;

    persona->nombre = "Santiago";
    persona->edad = 19;
    persona->id = 604630008;


    arrayPers->insertar(persona);

    auto* persona1 = new Persona;

    persona1->nombre = "Ariadna";
    persona1->edad = 20;
    persona1->id = 123456;

    arrayPers->insertar(persona1);

    auto* persona2 = new Persona;

    persona2->nombre = "Angelo";
    persona2->edad = 18;
    persona2->id = 987654;

    arrayPers->insertar(persona2);

    // -------------------------------- toString del vector  ----------------------

    cout<<"\n\n\ttoString del Array de personas: \n\n" << arrayPers->toString()<<endl;

    // Ahora vamos a crear un archivo txt con estructura en XML:

    ofstream file;
    file.open("ArchivoVectorPersonas.txt"); //txt
    string xml = arrayPers->toXML();
    file << xml;
    file.close();

    cout << "\n\n\tEl archivo XML se debera ver algo asi:\n\n";

    cout << arrayPers->toXML();

*/



    // Ahora voy a leer el archivo txt que esta serializado para cargarlo al vector

    ifstream archivo;
    string texto, xmlData;
    try { archivo.open("ArchivoVectorPersonas.txt", ios::in); }
    catch (std::ifstream::failure a) {
        cerr << '\a' << "no se pudo abrir el archivo";
        exit(1);
    }
    cout << endl;
    while (!archivo.eof()) {
        getline(archivo, texto);
        xmlData += texto;
    }
    archivo.close();


    if(Serializable::fromXML(xmlData, arrayPers)) {
        cout << arrayPers->toString();
    }else {
        cerr << '\a' << "El programa ha fallado con exito.";
    }




    return 0;
};
