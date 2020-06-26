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
 * @brief Constructor parametrizado
 * @param termino 
 */
Palabra::Palabra(std::string termino): _termino(termino) {
}
/**
 * @brief Constructor copia
 * @param orig
 */
Palabra::Palabra(const Palabra& orig): _termino(orig._termino) {
}
/**
 * @brief Destructor
 */
Palabra::~Palabra() {
}

/**
 * @brief Palabra para obtener el término
 * @return devuelve el termino
 */
std::string Palabra::GetTermino() const {
    return _termino;
}
/**
 * @brief Operador de comparación menor que 
 * @param palabra palabra a comparar 
 * @return devuelve true si es menor y false si es mayor
 */
bool Palabra::operator<(Palabra& palabra) {
    if(this->_termino<palabra.GetTermino()){
        return true;
    }else{
        return false;
    }
}

/**
 * @brief Operador de igualdad
 * @param palabra
 * @return devuelve true si es igual y false si es distinto
 */
bool Palabra::operator==(Palabra& palabra) {
if(this->_termino ==palabra.GetTermino()){
        return true;
    }else{
        return false;
    }
}
/**
 * @brief Operador de comparación mayor que
 * @param palabra
 * @return devuelve true si es mayor y false si es menor
 */
bool Palabra::operator>(Palabra& palabra) {
if(this->_termino>palabra.GetTermino()){
        return true;
    }else{
        return false;
    }
}
