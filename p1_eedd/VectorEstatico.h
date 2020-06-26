/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VectorEstatico.h
 * Author: Gema
 *
 * Created on 18 de septiembre de 2017, 20:37
 */

#ifndef VECTORESTATICO_H
#define VECTORESTATICO_H
#include <iostream>
#include "Palabra.h"

using namespace std;
class VectorEstatico {
public:
    VectorEstatico(int tama=80383);
    VectorEstatico(const VectorEstatico& orig);
    virtual ~VectorEstatico();
    
    int buscar(Palabra& dato);
    void insertar(Palabra& palabra, long int pos);
    Palabra leer(int pos);
    int getTama() const;
    
    void ordenar();
private:
    int _tama;
    Palabra *_v;
    
};

#endif /* VECTORESTATICO_H */

