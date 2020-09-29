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
#endif //INVESTIGATION_DELTA_DEMOSTRACION_H
