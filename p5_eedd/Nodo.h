/* 
 * @file Nodo.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 31 de octubre de 2017, 11:56
 * @note Práctica 5. Árboles AVL
 */

#ifndef NODO_H
#define NODO_H

/**
 * @brief Clase que guarda la informacion de un nodo
 */
template <typename T>
class Nodo {
public:
    Nodo<T> *izq,*der; //<Punteros a hijos izquierdo y derecho
    T dato; //<Dato
    char bal; //<Factor de equilibrio
    
    Nodo(T &ele): izq(0), der(0), bal(0), dato(ele) {}
    Nodo(const Nodo& orig): izq(orig.izq), der(orig.der),bal(orig.bal), dato(orig.dato){}
    virtual ~Nodo(){}
};

#endif /* NODO_H */

