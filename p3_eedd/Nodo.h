/* 
 * @file Nodo.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 10 de octubre de 2017, 8:36
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#ifndef NODO_H
#define NODO_H

/**
 * @brief Clase nodo
 */
template <class T>
class Nodo {
public:

    T _dato; //< Dato que contiene el nodo
    Nodo<T> *_sig; //< Puntero al siguiente nodo en la secuencia 
    
    Nodo(T &dato, Nodo *sig = 0) :_dato(dato), _sig(sig) {}
    virtual ~Nodo() {}
};

#endif /* NODO_H */

