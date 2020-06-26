/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Palabra.cpp
 * Author: Gema
 * 
 * Created on 18 de septiembre de 2017, 20:35
 */

#include "Palabra.h"
/**
 * Constructor por defecto parametrizado
 * @param termino
 */
Palabra::Palabra(std::string termino): _termino(termino) {
}

/**
 * Constructor copia
 * @param orig
 */
Palabra::Palabra(const Palabra& orig): _termino(orig._termino) {
}

/**
 * Destructor
 */
Palabra::~Palabra() {
}

/**
 * Método para obtener el string con el termino
 * @return Devuelve un string, que es el término
 */
std::string Palabra::GetTermino() const {
    return _termino;
}
/**
 * Operador de comparación menor que
 * @param palabra
 * @return Devuelve true si es menor y false si no lo es
 */
bool Palabra::operator<(Palabra& palabra) {
    if(this->_termino<palabra.GetTermino()){
        return true;
    }else{
        return false;
    }
}
/**
 * Operador de igualdad
 * @param palabra
 * @return Devuelve true si es igual y false si no lo es
 */
bool Palabra::operator==(Palabra& palabra) {
if(this->_termino ==palabra.GetTermino()){
        return true;
    }else{
        return false;
    }
}

/**
 * Operador de comparación mayor que
 * @param palabra
 * @return Devuelve true si es mayor y false si no lo es
 */
bool Palabra::operator>(Palabra& palabra) {
if(this->_termino>palabra.GetTermino()){
        return true;
    }else{
        return false;
    }
}
