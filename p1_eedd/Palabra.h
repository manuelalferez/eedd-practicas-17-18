/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Palabra.h
 * Author: Gema
 *
 * Created on 18 de septiembre de 2017, 20:35
 */

#ifndef PALABRA_H
#define PALABRA_H
#include <iostream>

using namespace std;
class Palabra {
public:
    Palabra(std::string termino=""); 
    Palabra(const Palabra& orig);
    virtual ~Palabra();
    std::string GetTermino() const;
    
    //Sobrecarga de operadores
    bool operator==(Palabra& palabra);
    bool operator<(Palabra& palabra);
    bool operator>(Palabra& palabra);
private:
    std::string _termino;
};

#endif /* PALABRA_H */

