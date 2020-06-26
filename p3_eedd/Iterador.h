/* 
 * @file Iterador.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 10 de octubre de 2017, 8:36
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#ifndef ITERADOR_H
#define ITERADOR_H
#include "Nodo.h"

template <class T>
class ListaEnlazada; ///Para resolver el problema que surje al utilizar una clase amiga

/**
 * @brief Clase iterador 
 */
template <class T>
class Iterador {
public:

    Iterador(Nodo<T> *nodo);
    Iterador(const Iterador<T>& orig);
    Iterador<T>& operator=(const Iterador<T> &i);
    bool fin();
    void siguiente();
    T& dato();

    virtual ~Iterador(){}
private: 
    Nodo<T> *_nodo; //< Puntero a un nodo
    friend class ListaEnlazada<T>;
};

/**
 * @brief Contructor parametrizado
 * @param nodo Puntero a un nodo
 * @post Crea un iterador que apunta a nodo
 */
template <class T>
Iterador<T>::Iterador(Nodo<T>* nodo) :
_nodo(nodo) {
}

/**
 * @brief Constructor de copia 
 * @param orig Iterador el cual se quiere copiar
 * @post Crea un iterador a partir de orig 
 */
template <class T>
Iterador<T>::Iterador(const Iterador& orig) :
_nodo(orig._nodo) {
}

/**
 * @brief Operador de asignación
 * @param i El operador con el que se quiere asignar 
 * @post Apuntar el iterador al mismo nodo que i
 * @return El iterador con el nodo ya asignado al mismo que i 
 */
template <class T>
Iterador<T>& Iterador<T>::operator=(const Iterador<T>& i) {
    if (this != i)
        _nodo = i._nodo;
    return *this;
}

/**
 * @brief Método fin()
 * @post Saber si el iterador ha llegado al final 
 * @return Devuelve true si se llego al final y false en otro caso 
 */
template <class T>
bool Iterador<T>::fin() {
    return _nodo == 0;
}

/**
 * @brief Método siguiente()
 * @post El iterador apunta al siguiente dato
 */
template <class T>
void Iterador<T>::siguiente() {
    _nodo = _nodo->_sig;
}

/**
 * @brief Método que devuelve un dato
 * @post Devolver un dato que está apuntado por el iterador
 * @return El dato apuntado
 */
template <class T>
T& Iterador<T>::dato() {
    return _nodo->_dato;
}
#endif /*ITERADOR_H */

