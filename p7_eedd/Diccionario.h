/* 
 * @file Diccionario.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 21 de noviembre de 2017, 13:19
 * @note Práctica 7. Tablas Hash
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
#include "THashCerrada.h"

/**
 * @brief Clase que almace la información relativa de un diccionario 
 */
class Diccionario {
public:
    Diccionario();
    Diccionario(std::string& nombre_fichero, int tama = 127591, int pri = 17681);
    Diccionario(const Diccionario& orig);
    virtual ~Diccionario();

    int numPalabras();
    bool tieneSucesores(std::string &palabra);
    Palabra* busca(std::string& cadena);
    void inserta(Palabra& p);

    void entrena(std::string& termino1, std::string& termino2);
    THashCerrada<Palabra>* getPalabras();

    void entrenar(std::string& frase);
    void usaCorpus(std::string& nom_fich_corpus);

private:
    THashCerrada<Palabra> _palabras; //< Palabras del diccionario 

    unsigned long djb2(unsigned char *str) {
        unsigned long hash = 5381;
        int c;
        while (c = *str++) hash = ((hash << 5) + hash) + c;
        return hash;
    }
};

#endif /* DICCIONARIO_H */



