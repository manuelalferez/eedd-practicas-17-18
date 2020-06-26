/* 
 * @file Diccionario.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 14 de noviembre de 2017, 15:40
 * @note Practica 6. Contenedores asociativos de STL
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "Palabra.h"
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Sucesor.h"
#include <map>

/**
 * @brief Clase que almace la información relativa de un diccionario 
 */
class Diccionario {
public:
    Diccionario();
    Diccionario(std::string& nombre_fichero);
    Diccionario(const Diccionario& orig);
    virtual ~Diccionario();
    
    int numPalabras();
    bool  tieneSucesores(std::string &palabra);
    std::map<std::string, Palabra> getPalabras() const;
    Palabra* busca(std::string& cadena);
    void inserta(Palabra& p);
    
    void entrena(std::string& termino1,std::string& termino2);
    
private:
    std::map<std::string, Palabra> _palabras; //< Palabras del diccionario 
};

#endif /* DICCIONARIO_H */

