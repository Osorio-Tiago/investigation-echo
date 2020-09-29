//
// Created by ariad on 28/9/2020.
//

#ifndef INVESTIGATION_DELTA_DEMOSTRACION_H
#define INVESTIGATION_DELTA_DEMOSTRACION_H

#include <iostream>
#include <sstream>
#include "xmlserialization.h"
#include <fstream>

using namespace xmls;


class Persona : public Serializable {
public:

    xString nombre;
    xInt edad;
    xInt id;

    Persona();
    Persona(string nombre, int edad, int id);
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

Persona::Persona(string nombre, int edad, int id) {
    this->nombre = nombre;
    this->edad = edad;
    this->id = id;
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
#endif //INVESTIGATION_DELTA_DEMOSTRACION_H
