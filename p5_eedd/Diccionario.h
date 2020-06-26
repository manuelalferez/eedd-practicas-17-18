/* 
 * @file Diccionario.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 31 de octubre de 2017, 11:56
 * @note Práctica 5. Árboles AVL
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "Palabra.h"
#include "AVL.h"
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Sucesor.h"


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
    bool  tieneSucesores(std::string &palabra);
    AVL<Palabra> getPalabras() const;
    Palabra* busca(std::string& cadena);
    bool insertar(Palabra& p);
    
private:
    AVL<Palabra> _palabras; //< Palabras del diccionario 
};

#endif /* DICCIONARIO_H */

