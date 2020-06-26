/*  
 * @file MallaRegular.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 5 de diciembre de 2017, 11:48
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H


#include <vector>
#include <iostream>
#include "Casilla.h"
#include <math.h>

template <typename T>
class MallaRegular {
    double xMin, yMin, xMax, yMax;
    double tamaCasillaX, tamaCasillaY;
    std::vector<std::vector<Casilla<T>>> mr;

    int _numCodPostales;

    Casilla<T> *obtenerCasilla(double x, double y);

public:
    MallaRegular(int axMin, int aYMin, int aXMax, int aYMax, double aNDiv);

    ~MallaRegular() {
    }
    void insertar(double x, double y, const T& dato);
    T *buscar(double x, double y, const T &dato);
    bool borrar(double x, double y, const T& dato);


    std::vector<T*> buscarRango(double rxmin, double rymin, double rxmax, double rymax);
    unsigned numElementos();
    unsigned maxElementosCelda();
    double promedioElementosPorCelda();

};
/**
 * Constructor de la malla regular
 * @param axMin
 * @param aYMin
 * @param aXMax
 * @param aYMax
 * @param aNDiv
 */
template <typename T>
MallaRegular<T>::MallaRegular(int axMin, int aYMin, int aXMax, int aYMax, double aNDiv) :
xMin(axMin), yMin(aYMin), xMax(aXMax), yMax(aYMax) {
    tamaCasillaX = (xMax - xMin) / aNDiv;
    tamaCasillaY = (yMax - yMin) / aNDiv;
    mr.insert(mr.begin(), aNDiv, std::vector<Casilla < T >> (aNDiv));

    _numCodPostales = 0;
}

/**
 * Devuelve una casilla a partir de los parametros dados
 * @param x
 * @param y
 * @return Puntero a una casilla
 */
template <typename T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(double x, double y) {
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;
    return &mr[j][i];
}

/**
 * Inserta un dato en una casilla de la malla
 * @param x
 * @param y
 * @param dato 
 */
template <typename T>
void MallaRegular<T>::insertar(double x, double y, const T& dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    c->insertar(dato);
    _numCodPostales++;
}

/**
 * Borra un punto de la malla dado por x e y
 * @param x
 * @param y
 * @param dato
 * @return devuelve true si ha sido borrado, false si no 
 */
template <typename T>
bool MallaRegular<T>::borrar(double x, double y, const T& dato) {
    _numCodPostales--;
    Casilla<T> *c = obtenerCasilla(x, y);
    return c->borrar(dato);
}

/**
 * Busca un punto en toda la malla
 * @param x
 * @param y
 * @param dato
 * @return devuelve un puntero al punto si lo encuentra, sino nulo
 */
template <typename T>
T* MallaRegular<T>::buscar(double x, double y, const T& dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    return c->buscar(dato);
}

/**
 * Permite obtener todos los puntos que hay dentro de un rango 
 * @param rxmin
 * @param rymin
 * @param rxmax
 * @param rymax
 * @return Devuelve los puntos de dicho rango
 */
template <typename T>
std::vector<T*> MallaRegular<T>::buscarRango(double rxmin, double rymin, double rxmax, double rymax) {
    std::vector<T*> vCasillas;  
    double x = xMin;
    double y = yMin;
    int jmin = 0;
    int imin = 0;
    int imax = 0;
    int jmax = 0;

    while (x < ceil(rxmin)) {
        imin++;
        x += (tamaCasillaX);
    }
    imax = imin;
    while (x < ceil(rxmax)) {
        imax++;
        x += (tamaCasillaX);
    }

    while (y < ceil(rymin)) {
        jmin++;
        y += (tamaCasillaY);

    }
    jmax = jmin;

    while (y < ceil(rymax)) {
        jmax++;
        y += (tamaCasillaY);
    }

    for (int i = imin; i < imax; ++i) {
        for (int j = jmin; j < jmax; ++j) {
            auto listaPuntos = mr[j][i].getPuntos();
            auto itLista = listaPuntos->begin();
            while (itLista != listaPuntos->end()) {
                vCasillas.push_back(&(*itLista));
                itLista++;
            }
        }
    }

    return vCasillas;
}

/**
 * Método para obtener el número de elementos
 * @return numero de elementos de la malla
 */
template <typename T>
unsigned MallaRegular<T>::numElementos() {
    return _numCodPostales;
}

/**
 * Método para obtener el máximo de elementos 
 * @return devuelve el máximo de elementos que puede haber en una celda
 */
template <typename T>
unsigned MallaRegular<T>::maxElementosCelda() {
    return mr[0][0].getMaxElementos();
}

/**
 * Método para saber el promedio de elementos por celda
 * @return devuelve el promedio de elementos por celda
 */
template <typename T>
double MallaRegular<T>::promedioElementosPorCelda() {
    return _numCodPostales / (mr.size()* (*mr.begin()).size());
}
#endif /* MALLAREGULAR_H */

