/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VDinamico.h
 * Author: Gema
 *
 * Created on 25 de septiembre de 2017, 21:39
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H
#include <climits>
#include <algorithm>
#include <math.h>
#include <iostream>

template <typename T>
class VDinamico {
public:
    VDinamico(int tamaf=1); //Constructor por defecto
    VDinamico(const VDinamico<T>& orig); //constructor copia
    VDinamico(const VDinamico<T>& origen, unsigned inicio,
            unsigned num); //constructor copia desde una posicion a otra
    VDinamico(unsigned tam); //inicializar el tamaño del vector a la potencia de 2 superior


    void operator=(const VDinamico<T>& orig); //operador de asignacion
    T operator[](int pos); //operador []

    void aumenta(T dato); //Insertar dato al final
    void insertar(const T& dato, unsigned pos = UINT_MAX); //Insertar dato en cualquier posicion
    T borrar(unsigned pos = UINT_MAX); //borrar cualquier posicion
    T disminuye(); // borrar dato al final
    unsigned tam(); //mostrar el tamaño 
    void ordenar(); // ordena el vector
    int buscar(T dato); //busca un dato

    T leer(int pos) {
        return _v[pos];
    }

    virtual ~VDinamico() {
        delete [] _v;
    }

    int getTamaf();
    int getTamal();
private:
    int _tamaf;
    int _tamal;
    T *_v;
};

/**
 * Constructor por defecto
 */
template <typename T>
VDinamico<T>::VDinamico(int tamaf) : _tamaf(tamaf), _tamal(0), _v(new T[_tamaf]){
}

/**
 * Constructor copia
 * @param orig
 */
template <typename T>
VDinamico<T>::VDinamico(const VDinamico& orig) : _tamaf(orig._tamaf),
_tamal(orig._tamal),_v(new T(_tamaf)) {
    for (int i = 0; i < _tamal; ++i) {
        _v[i] = orig._v[i];
    }
}

/**
 * Constructor copia en un rango 
 * @param origen
 * @param inicio
 * @param num
 */
template <typename T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned inicio, unsigned num) {
    if (inicio > 0 && inicio + num < _tamaf) {
        T _v = new T[_tamaf = origen._tamaf];
        _tamal = origen._tamal;

        for (int i = inicio; i < inicio + num; ++i) {
            _v[i] = origen._v[i];
        }
    } else {
        throw std::out_of_range("Fuera de rango");
    }
}

/**
 * Constructor en el que se le pasa un tamaño y se inicializa a la potencia de dos mas cercana
 * @param tam
 */
template <typename T>
VDinamico<T>::VDinamico(unsigned tam) : _tamal(0){
    for (int i = 0; _tamaf < tam; i++) {
        _tamaf = pow(2, i);
    }
    _v = new T[_tamaf];
}

/**
 * Operador []
 * @param pos
 * @return devuelve el dato de la posicion indicada
 */
template <typename T>
T VDinamico<T>::operator[](int pos) {
    return _v[pos];
}

/**
 * Operador de asignacion
 * @param orig
 */
template <typename T>
void VDinamico<T>::operator=(const VDinamico<T>& orig) {
    delete [] _v;
    _tamaf = orig._tamaf;
    _tamal = orig._tamal;
    _v = new T[orig._tamaf];
    for (int i = 0; i < _tamal; i++) {
        _v[i] = orig._v[i];
    }
}

/**
 * Método para introducir un dato. Aumenta el tamaño del vector al doble si no hay espacio para introducir un dato
 * @param dato  Dato a introducir en el vector, lo introduce al final
 */
template <typename T>
void VDinamico<T>::aumenta(T dato) {
    if (_tamal == _tamaf) {
        T *vaux = new T[_tamaf = _tamaf * 2];
        for (int i = 0; i < _tamal; i++) {
            vaux[i] = _v[i];
        }
        delete [] _v;
        _v = vaux;
    }
    _v[_tamal++] = dato;
}

/**
 * Método para insertar un dato en una posicion
 * @param dato Dato a insertar
 * @param pos  Posicion en la que se quiere insertar, si no se indica 
 * se inserta en la última posicion
 */
template <typename T>
void VDinamico<T>::insertar(const T& dato, unsigned pos) {
    if (pos == UINT_MAX) {
        aumenta(dato);
    } else if (pos != UINT_MAX && pos <= _tamal) {
        if (_tamal == _tamaf) {
            T* vaux = new T[_tamaf = _tamaf * 2];
            for (int i = 0; i < _tamal; i++) {
                vaux[i] = _v[i];
            }
            delete [] _v;
            _v = vaux;
        }

        for (unsigned i = _tamal - 1; i >= pos; i--) {
            _v[i + 1] = _v[i];
        }
        _v[pos] = dato;

    } else {
        throw std::out_of_range("Posicion fuera de rango en la inserccion");
    }
}

/**
 * Método para disminuir el tamaño del vector y eliminar el ultimo elemento 
 * @return Devuelve el dato que se ha borrado
 */
template <typename T>
T VDinamico<T>::disminuye() {
    if (_tamaf * 3 < _tamaf) {
        _tamaf = _tamaf / 2;
        T *vaux = new T[_tamaf];
        for (unsigned i = 0; i < _tamal; i++) {
            vaux[i] = _v[i];
        }
        delete [] _v;
        _v = vaux;
    }
    return _v[--_tamal];
}

/**
 * Método para ordenar el vector
 */
template <typename T>
void VDinamico<T>::ordenar() {
    std::sort(_v, _v + _tamal);
}

/**
 * Método para obtener el tamaño fisico del vector
 * @return Devuelve el tamaño fisico del vector
 */
template <typename T>
int VDinamico<T>::getTamaf() {
    return _tamaf;
}

/**
 * Método para obtener el tamaño lógico del vector
 * @return Devuelve el tamaño lógico del vector
 */
template <typename T>
int VDinamico<T>::getTamal() {
    return _tamal;
}

/**
 * Método para buscar en el vector
 * @param dato Dato a buscar
 * @return Devuelve la posicion en la que está el dato, si no está devuelve -1
 */
template <typename T>
int VDinamico<T>::buscar(T dato) {
    int inf = 0;
    int sup = _tamal - 1;
    int curIn = 0;
    while (inf <= sup) {
        curIn = (inf + sup) / 2;
        if (_v[curIn] == dato) {
            return curIn;
        } else if (_v[curIn] < dato) inf = curIn + 1;
        else sup = curIn - 1;
    }
    return -1;
}
template<typename T>
unsigned VDinamico<T>::tam(){
    return _tamal;
}
#endif /* VDINAMICO_H */

