/* 
 * @file Sucesor.cpp
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 14 de octubre de 2017, 12:20
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#include "Sucesor.h"

/**
 * @brief Constructor por defecto paremetrizado 
 * @param termino El termino del sucesor 
 * @post Crear un sucesor por defecto-paramtriza
 */
Sucesor::Sucesor(std::string termino,int numOcurrencias) :
_termino(termino),
_numOcurrencias(numOcurrencias) {
}

/**
 * @brief Constructor de copia 
 * @param orig El sucesor que se quiere copiar 
 * @post Crear un sucesor que es una copia de orig
 */
Sucesor::Sucesor(const Sucesor& orig) :
_termino(orig._termino),
_numOcurrencias(orig._numOcurrencias) {
}

/**
 * @brief Destructor de la clase
 * @post Destruir un objeto
 */
Sucesor::~Sucesor() {
}

/**
 * @brief Incrementa el número de ocurrencias del sucesor
 * @post Incrementar el número de ocurrencias del sucesor
 */
void Sucesor::incrementarOcurrencias() {
    _numOcurrencias++;
}

/**
 * @brief Devuelve el término del sucesor
 * @return El término del sucesor 
 */
std::string Sucesor::getTermino() const {
    return _termino;
}

/**
 * @brief Devuelve el número de ocurrencias del sucesor
 * @return El número de ocurrencias del sucesor 
 * @post Devolver el número de ocurrencias del sucesor
 */
int Sucesor::getNumOcurrencias() const {
    return _numOcurrencias;
}

/**
 * @brief Operador de asignación
 * @param orig El sucesor que se quiere copiar
 * @return El sucesor con la información copiada de orig
 * @post Hacer un asignación con toda la información del sucesor orig
 */
Sucesor& Sucesor::operator=(const Sucesor& orig) {
    _termino = orig._termino;
    _numOcurrencias = orig._numOcurrencias;

    return *this;
}
