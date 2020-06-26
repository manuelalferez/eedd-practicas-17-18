/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Diccionario.h"
#include <fstream>
#include <algorithm>

/**
 * @brief Constructor por defecto: carga el fichero en el vector y lo ordena
 * @param ruta Se le pasa el nombre del fichero
 */
Diccionario::Diccionario(std::string ruta) {
    _palabras = new VectorEstatico(80383);

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
                _palabras->insertar(p, total);
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
 * @brief Constructor copia
 * @param orig Diccionario a copiar
 */
Diccionario::Diccionario(const Diccionario& orig) {
    for (int i = 0; i < _palabras->getTama(); i++) {
        Palabra p(orig._palabras->leer(i));
        _palabras->insertar(p, i);
    }
}

/**
 * @brief Método para buscar un término
 * @param termino
 * @return Devuelve la posición
 */
int Diccionario::buscar(std::string termino) {
    Palabra p(termino);
    return _palabras->buscar(p);
}

/**
 * @brief Destructor 
 */
Diccionario::~Diccionario() {
    delete _palabras;
}

/**
 * @brief Método para mostrar el contenido del diccionario
 */
void Diccionario::mostrarDiccionario() {
    for (int i = 0; i < _palabras->getTama(); i++) {
        std::cout << _palabras->leer(i).GetTermino() << std::endl;
    }
}

/**
 * @brief Método para obtener un puntero al vector de palabras
 * @return Devuelve el vector de palabras
 */
VectorEstatico* Diccionario::getPalabras() const {
    return _palabras;
}

/**
 * @brief Método para insertar una palabra al diccionario
 * @param termino Palabra a insertar
 * @param posicion Posicion en la que quiero insertar
 */
void Diccionario::insertar(std::string termino, long int posicion) {
    Palabra p(termino);
    _palabras->insertar(p, posicion);
    ordenar();

}

/**
 * @brief Metodo para ordenar
 */
void Diccionario::ordenar() {
    _palabras->ordenar();
}

/**
 * @brief Metodo para leer una posicion del diccionario
 * @param posicion Posicion a leer
 * @return Devuelve el termino
 */
string Diccionario::leer(int posicion) {
    return _palabras->leer(posicion).GetTermino();
}



