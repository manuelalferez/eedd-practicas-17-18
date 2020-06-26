/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Diccionario.h
 * Author: Gema
 *
 * Created on 19 de septiembre de 2017, 16:58
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <iostream>
#include "Palabra.h"
#include "VDinamico.h"
using namespace std;
class Diccionario {
public:
    Diccionario(std::string& ruta);
    Diccionario(const Diccionario& orig);
    ~Diccionario();
    string leer(int posicion);
    VDinamico<Palabra>* getPalabras() const;
    void ordenar();
    
    int buscar(std::string& termino);
    void insertar(std::string& termino);
    
    unsigned tama();
private:
    VDinamico<Palabra>* _palabras;
};

#endif /* DICCIONARIO_H */

