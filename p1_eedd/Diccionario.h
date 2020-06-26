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
#include "VectorEstatico.h"
using namespace std;
class Diccionario {
public:
    Diccionario(std::string ruta="");
    Diccionario(const Diccionario& orig);
    ~Diccionario();
    void insertar(std::string termino, long int posicion);
    string leer(int posicion);
    int buscar(std::string termino);
    void mostrarDiccionario();
    VectorEstatico* getPalabras() const;
    void ordenar();
private:
    VectorEstatico* _palabras;
};

#endif /* DICCIONARIO_H */

