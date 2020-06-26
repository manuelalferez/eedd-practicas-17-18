/* 
 * @file Diccionario.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 14 de octubre de 2017, 12:20
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "VectorDinamico.h"
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
    int  mostrarSucesores(std::string &palabra);
    VectorDinamico<Palabra>* getPalabras() const;
    Palabra* buscar(std::string& cadena);
    bool insertar(Palabra& p);
    
private:
    VectorDinamico<Palabra> *_palabras; //< Palabras del diccionario 
};

#endif /* DICCIONARIO_H */

