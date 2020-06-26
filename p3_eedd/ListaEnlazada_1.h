/* 
 * @file ListaEnlazada.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 10 de octubre de 2017, 8:36
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include "Nodo.h"
#include "Iterador.h"
#include <stdexcept>
#include <list>
#include <iostream>

/**
 * @brief Clase lista enlazada
 */
template <class T>
class ListaEnlazada {
public:
    ListaEnlazada();
    ListaEnlazada(const ListaEnlazada<T>& orig);

    ListaEnlazada<T>& operator=(const ListaEnlazada<T> &l);

    T& inicio();
    T & final();

    Iterador<T> iterador();

    void insertaInicio(T& dato);
    void insertaFin(T& dato);
    void inserta(Iterador<T> &i, T& dato);

    void borraInicio();
    void borraFinal();
    void borra(Iterador<T> &i);

    virtual ~ListaEnlazada();
private:
    Nodo<T> *_cabecera, *_cola;
};

/**
 * @brief Constructor por defecto 
 * @post Construye una lista enlazada por defecto 
 */
template <class T>
ListaEnlazada<T>::ListaEnlazada() :
_cabecera(0), _cola(0) {
}

/**
 * @brief Constructor de copia 
 * @param orig La lista enlazada que se desea copiar
 * @post Crea una lista enlazada que es una copia de orig
 */
template <class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T>& orig) {

    if (this != &orig) {
        if (orig._cabecera != 0) {
            _cabecera = new Nodo<T>(orig._cabecera->_dato, 0);

            auto i = this->_cabecera;
            auto j = orig._cabecera;

            while (j->_sig != 0) {

                i->_sig = new Nodo<T>(j->_sig->_dato, 0);

                i = i->_sig;
                j = j->_sig;

            }
            if (orig._cabecera == orig._cola)
                _cola = _cabecera;
            else
                _cola = i;
        } else {
            _cabecera = _cola = 0;
        }
    }
}

/**
 * @brief Destructor de la lista enlazada
 * @post Destruir la lista 
 */
template <class T>
ListaEnlazada<T>::~ListaEnlazada() {

    while (_cabecera != _cola != 0) {

        Nodo<T> *borrado = _cabecera;
        _cabecera = _cabecera->_sig;

        delete borrado;

        if (_cabecera == 0)
            _cola = 0;
    }
}

/**
 * @brief Operador de asignación 
 * @param l La lista que se quiere copiar 
 * @post Crear una lista igual a l
 * @return La lista con la información ya modificada que es igual que l
 */

template <class T>
ListaEnlazada<T>& ListaEnlazada<T>::operator=(const ListaEnlazada<T>& l) {
    if (this != &l) {
        while (_cabecera != _cola != 0) {

            Nodo<T> *borrado = _cabecera;
            _cabecera = _cabecera->_sig;

            delete borrado;

            if (_cabecera == 0)
                _cola = 0;
        }
        if (l._cabecera != 0) {
            _cabecera = new Nodo<T>(l._cabecera->_dato, 0);

            auto i = this->_cabecera;
            auto j = l._cabecera;

            while (j->_sig != 0) {

                i->_sig = new Nodo<T>(j->_sig->_dato, 0);

                i = i->_sig;
                j = j->_sig;

            }
            if (l._cabecera == l._cola)
                _cola = _cabecera;
            else
                _cola = new Nodo<T>(*l._cola);
        } else {
            _cabecera = _cola = 0;
        }
    } else
        return *this;
}

/**
 * @brief Devuelve el dato del inicio
 * @post Devolver el dato del inicio de la lista
 * @return El dato del principio de la lista 
 */
template <class T >
T & ListaEnlazada<T>::inicio() {
    return _cabecera->_dato;
}

/**
 * @brief Devuelve el dato del final 
 * @post Devolver el dato del final de la lista
 * @return El dato del final de la lista 
 */
template <class T >
T & ListaEnlazada<T>::final() {
    return _cola->_dato;
}

/**
 * @brief Iterador 
 * @post Iterar sobre la lista enlazada
 */
template <class T >
Iterador<T> ListaEnlazada<T>::iterador() {
    return Iterador<T>(_cabecera);
}

/**
 * @brief Inserta un dato al inicio
 * @post Insertar un dato al inicio de la lista 
 * @param dato Dato que vamos a insertar 
 */
template <class T>
void ListaEnlazada<T>::insertaInicio(T & dato) {
    Nodo<T> *nuevo = new Nodo<T> (dato, _cabecera);

    if (_cola == 0)
        _cola = nuevo;
    _cabecera = nuevo;
}

/**
 * @brief Inserta un dato al final 
 * @post Insertar un dato al final de la lista 
 * @param dato Dato que vamos a insertar 
 */
template <class T>
void ListaEnlazada<T>::insertaFin(T & dato) {
    Nodo<T> *nuevo = new Nodo<T> (dato, 0);

    if (_cola != 0)
        _cola->_sig = nuevo;
    if (_cabecera == 0)
        _cabecera = nuevo;
    _cola = nuevo;
}

/**
 * @brief Inserta un dato en el medio 
 * @post Insertar un dato en la posicion anterior apuntada por el iterador i
 * @param i El iterador donde vamos a insertar
 * @param dato El dato que vamos a insertar
 */
template <class T>
void ListaEnlazada<T>::inserta(Iterador<T>& i, T & dato) {
    if (i._nodo == _cabecera) { //inicio
        Nodo<T> *nuevo = new Nodo<T> (dato, _cabecera);

        if (_cola == 0)
            _cola = nuevo;
        _cabecera = nuevo;
    } else if (i._nodo == _cola) { //fin
        Nodo<T> *nuevo = new Nodo<T> (dato, 0);

        if (_cola != 0)
            _cola->_sig = nuevo;
        if (_cabecera == 0)
            _cabecera = nuevo;
        _cola = nuevo;
    } else { //otra posicion
        Nodo<T> *anterior = 0;

        if (_cabecera != _cola) {
            anterior = _cabecera;
            while (anterior->_sig != i._nodo)
                anterior = anterior->_sig;
        }

        Nodo<T> *nuevo = new Nodo<T> (dato, i._nodo);

        anterior->_sig = nuevo;
    }
}

/**
 * @brief Borra un nodo inicial
 * @post Borrar un nodo de la posición inicial
 */
template <class T>
void ListaEnlazada<T>::borraInicio() {

    if (_cabecera != 0) {
        Nodo<T> *borrado = _cabecera;
        _cabecera = _cabecera->_sig;

        delete borrado;

        if (_cabecera == 0)
            _cola = 0;
    } else
        throw std::logic_error("[ListaEnlazada<T>::borraInicio()]:La lista esta vacia.");
}

/**
 * @brief Borra un nodo final 
 * @post Borrar un nodo de la posición final 
 */
template <class T>
void ListaEnlazada<T>::borraFinal() {

    if (_cola != 0) {

        Nodo<T> *anterior = 0;

        if (_cabecera != _cola) {
            anterior = _cabecera;
            while (anterior->_sig != _cola)
                anterior = anterior->_sig;
        }

        delete _cola;

        _cola = anterior;

        if (anterior != 0)
            anterior->_sig = 0;
        else
            _cabecera = 0;
    } else
        throw std::logic_error("[ListaEnlazada<T>::borraFinal()]:La lista esta vacia.");
}

/**
 * @brief Borra un nodo apuntado por un iterador
 * @post Borrar un nodo apuntado por un iterador 
 * @param i Iterador que apunta al nodo a eliminar
 */
template <class T>
void ListaEnlazada<T>::borra(Iterador<T>& i) {

    if (i._nodo == _cabecera)//insertar inicio

        if (_cabecera != 0) {
            Nodo<T> *borrado = _cabecera;
            _cabecera = _cabecera->_sig;

            delete borrado;

            if (_cabecera == 0)
                _cola = 0;
        } else
            throw std::logic_error("[ListaEnlazada<T>::borraInicio()]:La lista esta vacia.");
    else if (i._nodo == _cola) // borrar final
        if (_cola != 0) {

            Nodo<T> *anterior = 0;

            if (_cabecera != _cola) {
                anterior = _cabecera;
                while (anterior->_sig != _cola)
                    anterior = anterior->_sig;
            }

            delete _cola;

            _cola = anterior;

            if (anterior != 0)
                anterior->_sig = 0;
            else
                _cabecera = 0;
        } else
            throw std::logic_error("[ListaEnlazada<T>::borraFinal()]:La lista esta vacia.");
    else { //borrar cualquier posicion
        Nodo<T> *anterior = 0;

        if (_cabecera != _cola) {
            anterior = _cabecera;
            while (anterior->_sig != i._nodo)
                anterior = anterior->_sig;
        }

        anterior->_sig = i._nodo->_sig;

        delete i._nodo;
    }
}

#endif /* LISTAENLAZADA_H */

