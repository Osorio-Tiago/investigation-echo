//
// Created by deine on 9/21/2020.
//
#include <iostream>
#include <fstream> //usar las funciones de escritura y lectura
#include <string.h> //pasar de string cadena de char
#include <vector>
#include <sstream>
#include "xmlserialization.h"
using namespace xmls;
using namespace std;

struct Persona : public Serializable{
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

/*
void save(Persona persona) {
    ofstream archivo;
    //se crea una variable ofstream para poder usar los metodos necesarios para escribir en un archivo como .open, .write , .close ,...

    try { archivo.open("ArchivoBinario.dat", ios::app | ios::binary); }
        //se abre o se crea el archivo "ArchivoBinario.dat" y se decide en que modo se abrira ese archivo y por ultimo se le recuerda a C++ que es un archivo binario

    catch (std::ifstream::failure a) { cout << "no se pudo abrir el archivo"; }
    //si el archivo no se pudo abrir o algo mas paso el metodo fail() retorna un 1 si algo malo paso y con el exit(1) nos salimos del metodo

    archivo.write((char *) &persona, sizeof(Persona));
    //esta el metodo que se usa para escribir en el archivo binario
    //se le pasan  dos paramentros, primero la direccion del objeto,struct,variable que se va "almacenar" y segundo el tamanno de este objeto,struct o variable

    archivo.close();
    //por ultimo se cierra el archivo
}

void load(Persona &persona) {
    ifstream archivo;
    //se crea una variable ifstream para poder usar los metodos necesarios para leer el archivo como .open, .read , .close ,...

    try { archivo.open("ArchivoBinario.dat", ios::in | ios::binary); }
        //carga el archivo, se decide en que modo se va a abrir ese archivo( en este caso en modo lectura) y se le recuerda a C++ que es un archivo binario

    catch (std::ifstream::failure a) {
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    //si el archivo no se pudo abrir o algo mas paso el metodo fail() retorna un 1 si algo malo paso y con el exit(1) nos salimos del metodo

    archivo.read((char *) &persona, sizeof(Persona));
    //lo que esta en el archivo se va a cargar en la persona

    archivo.close();
    //se cerro el archivo
}

void ejemploSeekgYTellg(Persona &persona) {
    ifstream archivo;

    try { archivo.open("ArchivoBinario.dat", ios::in | ios::binary); }
        //carga el archivo, se decide en que modo se va a abrir ese archivo( en este caso en modo lectura) y se le recuerda a C++ que es un archivo binario

    catch (std::ifstream::failure a) {
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    //si el archivo no se pudo abrir o algo mas paso el metodo fail() retorna un 1 si algo malo paso y con el exit(1) nos salimos del metodo

    //por ejemplo queremos mostrar la tercera persona que fuen ingresado en el archivo
    archivo.seekg(2 * sizeof(Persona));
    //ya que C++ utiliza lo que son direccion fisicas lo cual quiere decir que se recorre el archivo byte a byte
    //por ese motivo hay multiplicarle el sizeof(Persona) para ubicarnos en la tercera persona
    //lo multiplicamos por 2 ya que la primera persona es el registro 0, la segunda el 1, la tercera el 2,...

    archivo.read((char *) &persona, sizeof(Persona));
    cout << "La lectura del archivo quedo en el byte: " << archivo.tellg();


    archivo.close();
    //se cerro el archivo
}



void leer() {
    ifstream archivo;
    string texto;
    try { archivo.open("ArchivoTexto.txt", ios::in); }
    catch (std::ifstream::failure a) {
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    cout << endl;
    while (!archivo.eof()) {
        getline(archivo, texto);
        cout << texto << endl;
    }
    archivo.close();
}
*/


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

    cout<<arrayPers->toString()<<endl;

    // Ahora vamos a crear un archivo txt con estructura en XML:

    ofstream file;
    file.open("ArchivoVectorPersonas.txt"); //txt
    //.good();
    string xml = arrayPers->toXML();
    file << xml;
    file.close();

    cout << "\n\n\tEl archivo XML se debera ver algo asi:\n\n";

   // cout << arrayPers->toXML();
*/




    // Ahora voy a leer el archivo txt que esta serializado para cargarlo al vector

    ifstream archivo;
    string texto, xmlData;
    try { archivo.open("ArchivoVectorPersonas.txt", ios::in); }
    catch (std::ifstream::failure a) {
        cout << "no se pudo abrir el archivo";
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
    }else
    {
        cerr << '\a' << "El programa ha fallado con exito.";
    }
    return 0;
};
