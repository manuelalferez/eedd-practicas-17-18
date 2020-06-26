/* 
 * @file Diccionario.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 24 de octubre de 2017, 16:11
 * @note Práctica 4. STL de contenedores lineales
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
#include <vector>

/**
 * @brief Clase que almace la información relativa de un diccionario 
 */
class Diccionario {
public:
    Diccionario(std::string& nombre_fichero);
    Diccionario(const Diccionario& orig);
    virtual ~Diccionario();
    
    int numPalabras();
    void entrena(std::string& frase);
    void usaCorpus(std::string& nom_fich_corpus);
    int  tieneSucesores(std::string &palabra);
    std::vector<Palabra>* getPalabras() const;
    Palabra* busca(std::string& cadena);
    bool insertar(Palabra& p);
    
private:
    std::vector<Palabra> *_palabras; //< Palabras del diccionario 
};

#endif /* DICCIONARIO_H */

