/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Diccionario.h"
#include <fstream>
#include <algorithm>

/**
 * Constructor por defecto parametrizado
 * @param ruta Se le pasa el nombre del archivo txt donde están las palabras
 */
Diccionario::Diccionario(std::string& ruta):_palabras(new VDinamico<Palabra>(80383)) {
    
    std::ifstream fe; //creamos la linea de entrada
    std::string linea;
    long int total = 0;
    //asociamos el flujo con un fichero y lo abrimos
    fe.open(ruta);
    if (fe.good()) {
        //mientras no se haya llegado al final del fichero
        while (!fe.eof()) {
            getline(fe, linea); //toma una linea del fichero
            if (linea != "") {
                Palabra p(linea);
                _palabras->aumenta(p);
                total++;
            }
        }
        std::cout << "Total de palabras en el archivo: " << total << std::endl;
        fe.close(); //cerramos el flujo de entrada
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
    ordenar();
}

/**
 * Constructor copia 
 * @param orig
 */
Diccionario::Diccionario(const Diccionario& orig) {
    for (int i = 0; i < _palabras->getTamal(); i++) {
        _palabras->insertar(orig._palabras->operator[](i), i);
    }
}

/**
 * Método para buscar un término
 * @param termino Es el término a buscar en el diccionario
 * @return Devuelve la posición en la que se encuentra el término
 */
int Diccionario::buscar(std::string& termino) {
    Palabra p(termino);
    return _palabras->buscar(p);
}

/**
 * Destructor
 */
Diccionario::~Diccionario() {
    delete _palabras;
}

/**
 * Método para obtener el vector de palabras
 * @return Devuelve el vector de palabras
 */
VDinamico<Palabra>* Diccionario::getPalabras() const {
    return _palabras;
}

/**
 * Método para insertar una palabra en el diccionario
 * @param termino Término a insertar en el diccionario
 * Ordena el vector después de la insercción
 */
void Diccionario::insertar(std::string& termino) {
    Palabra p(termino);
     _palabras->insertar(p);
     ordenar();
}

/**
 * Ordena el diccionario
 */
void Diccionario::ordenar() {
    _palabras->ordenar();

}

/**
 * Método para leer una posición
 * @param posicion Indica que posición se quiere leer
 * @return Devuelve el término a leer
 */
string Diccionario::leer(int posicion) {
    return _palabras->leer(posicion).GetTermino();
}

unsigned Diccionario::tama() {
    return _palabras->tam();
}
