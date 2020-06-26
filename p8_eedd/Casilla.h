/*    
 * @fileCasilla.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 5 de diciembre de 2017, 11:55
 */

#ifndef CASILLA_H
#define CASILLA_H

#include <list>

template <typename T>
class Casilla {
    std::list<T> puntos; //<Lista de puntos de la casilla 
    static int maxElementos; //<Maximo de elementos que hay en todas las casillas

public:

    Casilla() : puntos() {} //<Constructor por defecto 

    ~Casilla() {}           //<Destructor

    void insertar(const T &dato) {    //<Metodo para insetar un dato en la casilla
        puntos.push_back(dato);
        if (puntos.size() > maxElementos) maxElementos = puntos.size();
    }
    
    T *buscar(const T& dato); 
    bool borrar(const T &dato);

    int getNumPuntos() { //<Obtienes el numero de elementos de la casilla
        return puntos.size();
    }
    std::list<T>* getPuntos();
    int getMaxElementos();

};

template <typename T>
int Casilla<T>::maxElementos = 0;

/**
 * Método para buscar un dato en la casilla
 * @param dato
 * @return devuelve el puntero al dato si lo encuentra, sino devuelve null
 */
template <typename T>
T* Casilla<T>::buscar(const T& dato) {
    typename std::list<T>::iterator it;
    it = puntos.begin();
    for (; it != puntos.end(); ++it) {
        if (*it == dato)
            return &(*it);
    }
    return;
}

/**
 * Método para obtener los puntos de una casilla
 * @return lista con los puntos
 */
template <typename T>
std::list<T>* Casilla<T>::getPuntos() {
    return &puntos;
}

/**
 * Devuelve el máximo de elementos de todas las casillas
 * @return 
 */
template <typename T>
int Casilla<T>::getMaxElementos() {
    return Casilla<T>::maxElementos;
}

/**
 * Método que permite borrar un dato de la casilla
 * @param dato
 * @return devuelve true si lo consigue y false si no 
 */
template <typename T>
bool Casilla<T>::borrar(const T& dato) {
    typename std::list<T>::iterator it;
    it = puntos.begin();
    for (; it != puntos.end(); ++it) {
        if (*it == dato) {
            puntos.erase(it);
            if (puntos.size() > maxElementos) maxElementos = puntos.size();
            return true;
        }
    }

    if (puntos.size() > maxElementos) maxElementos = puntos.size();

    return false;

}

#endif /* CASILLA_H */

