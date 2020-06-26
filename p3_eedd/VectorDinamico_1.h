/* 
 * @file VectorDinamico.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 14 de octubre de 2017, 12:20
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#ifndef VECTORDINAMICO_H
#define VECTORDINAMICO_H
#include <math.h>
#include <stdexcept>
#include <climits>
#include <algorithm>
#include <iostream>

template <class T>
class VectorDinamico {
public:
    VectorDinamico(int tama = 1);
    VectorDinamico(unsigned tam);
    VectorDinamico(const VectorDinamico<T>& orig);
    VectorDinamico(const VectorDinamico<T>& origen, unsigned inicio, unsigned num);

    virtual ~VectorDinamico() {
        delete[] _v;
    }

    T& operator=(const VectorDinamico<T> &orig);
    T& operator[](unsigned pos);
    T lee(unsigned pos);
    void aumenta(T& dato);
    T disminuye();
    void ordenar();
    int busca(T dato);
    int busquedaBin(T dato);
    void insertar(T& dato, unsigned pos = UINT_MAX);

    int tam();

private:
    int _taml, _tamf;
    T *_v;

};

template <class T>
VectorDinamico<T>::VectorDinamico(int tama) :
_tamf(tama), _taml(0), _v(new T[_tamf]) {
}

template <class T>
VectorDinamico<T>::VectorDinamico(unsigned tam) :
_taml(0) {
    for (int i = 0; _tamf < tam; i++)
        _tamf = pow(2, i);
    _v = new T[_tamf];
}

template <class T >
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T> & orig) :
_tamf(orig._tamf),
_taml(orig._taml),
_v(new T(_tamf)) {
    for (int i = 0; i < _taml; i++)
        _v[i] = orig._v[i];
}

template <class T>
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T>& origen, unsigned inicio, unsigned num) {
    _v = new T[_tamf = num];
    _taml = 0;
    for (int i = inicio; i < inicio + num; i++) {
        _v[i] = origen._v[i];
        _taml++;
    }
}

template <class T>
T& VectorDinamico<T>::operator=(const VectorDinamico<T>& orig) {
    if (this->_v!=orig._v) {
        delete[] _v;
        _v = new T[ _tamf = orig._tamf];
        _taml = orig._taml;
        for (int i = 0; i < _taml; i++) {
            _v[i] = orig._v[i];
        }
    }
    return *_v;
}

template <class T>
T& VectorDinamico<T>::operator[](unsigned pos) {
    if (pos > _tamf || pos < 0)
        throw std::out_of_range("[VectorDinamico<T>::operator []]: Posicion fuera de rango.");
    return _v[pos];
}

template <class T>
void VectorDinamico<T>::insertar(T& dato, unsigned pos) {

    //Insercion por el medio
    if (_taml <= _tamf && pos != UINT_MAX) {

        //Vector lleno
        if (_taml == _tamf) {
            T *vaux;
            vaux = new T[_tamf = _tamf * 2];
            for (int i = 0; i < _taml; i++)
                vaux[i] = _v[i];
            delete[] _v;
            _v = vaux;
        }

        //Dejamos hueco y metemos dato
        for (unsigned i = _taml - 1; i >= pos; i--)
            _v[i + 1] = _v[i];
        _v[pos] = dato;

        //Insercion por el final
    } else if (pos == UINT_MAX) {
        if (_taml == _tamf) {
            T *vaux;
            vaux = new T[_tamf = _tamf * 2];

            for (int i = 0; i < _taml; i++)
                vaux[i] = _v[i];
            delete[] _v;
            _v = vaux;
        }
        _v[_taml++] = dato;

        //Posicion fuera de rango
    } else if (pos >= _tamf || pos < 0)
        throw std::out_of_range("[VectorDinamico<T>::insertar]: Fuera de rango.");

}

template <class T>
int VectorDinamico<T>::tam() {
    return _taml;
}

template <class T>
T VectorDinamico<T>::lee(unsigned pos) {
    return _v[pos];
}

template <class T>
void VectorDinamico<T>::aumenta(T& dato) {
    if (_taml == _tamf) {
        T *vaux;
        vaux = new T[_tamf = _tamf * 2];

        for (int i = 0; i < _taml; i++)
            vaux[i] = _v[i];
        delete[] _v;
        _v = vaux;
    }
    _v[_taml++] = dato;
}

template <class T>
T VectorDinamico<T>::disminuye() {
    if (_taml * 3 < _tamf) {
        _tamf = _tamf / 2;
        T *vaux = new T[_tamf];

        for (unsigned i = 0; i < _taml; i++)
            vaux[i] = _v[i];
        delete[] _v;
        _v = vaux;
    }
    return _v[--_taml];
}

template <class T>
void VectorDinamico<T>::ordenar() {

    std::sort(_v, _v + _taml);
}

template <class T>
int VectorDinamico<T>::busca(T dato) {
    for (int i = 0; i < _taml; i++)
        if (_v[i] == dato)
            return i;

    return -1;
}

template <class T>
int VectorDinamico<T>::busquedaBin(T dato) {
    int inf = 0;
    int sup = _taml - 1;
    int mid;

    while (inf <= sup) {
        mid = (inf + sup) / 2;
        if (_v[mid] == dato)
            return mid;
        else if (_v[mid] < dato)
            inf = mid + 1;
        else sup = mid - 1;
    }
    return -1;
}

#endif /* VECTORDINAMICO_H */

