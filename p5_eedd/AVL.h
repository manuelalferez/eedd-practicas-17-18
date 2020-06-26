/* 
 * @file AVL.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 31 de octubre de 2017, 11:56
 * @note Practica 5. Arboles AVL
 */

#ifndef AVL_H
#define AVL_H

#include "Nodo.h"
#include <iostream>
#include <queue>
#include <stdexcept>

/**
 * @brief Clase que representa la estructura de un arbol AVL
 */
template <typename T>
class AVL {
public:

    AVL() : raiz(0) {}
    AVL(const AVL<T>& orig);
    virtual ~AVL() { destruirArbol(raiz);}
    AVL<T>& operator=(AVL<T>& orig);

    bool inserta(T &dato) { return inserta(raiz, dato);}
    bool busca(T& dato, T& result);
    T* busca(T& dato);
    void recorreInorden() { inorden(raiz, 0);}
    unsigned int numElementos();
    unsigned int altura() { return altura(raiz);}
    void destruir() { destruirArbol(raiz);}

private:
    Nodo<T> *raiz;

    //Funciones privadas
    void rotDer(Nodo<T>* &nodo);
    void rotIzq(Nodo<T>* &nodo);
    int inserta(Nodo<T>* &c, T& dato);
    void inorden(Nodo<T>* p, int nivel);
    Nodo<T>* busca(T&ele, Nodo<T> *p);
    unsigned int altura(Nodo<T>* &nodo);
    void copiaArbol(Nodo<T>* nodo);
    void destruirArbol(Nodo<T>* nodo);
};

/**
 * @brief Constructor de copia
 * @param orig El AVL que vamos a copiar
 * @post Crea un AVL que es una copia de orig
 */
template <typename T>
AVL<T>::AVL(const AVL<T>& orig) :
raiz(0) {
    if (orig.raiz) copiaArbol(orig.raiz);
}

/**
 * @brief Operador de asignacion
 * @param orig El AVL que vamos a copiar
 * @return El AVL que es una copia de orig
 */
template <typename T>
AVL<T>& AVL<T>::operator=(AVL<T>& orig) {
    if (this != &orig) {
        destruir();
        copiaArbol(orig.raiz);
    }
}

/**
 * @brief Inserta un dato a partir de un nodo
 * @param c El nodo a partir del cual se insertará
 * @param dato El dato que vamos a insertar
 * @return 
 */
template <typename T>
int AVL<T>::inserta(Nodo<T>*& c, T& dato) {
    Nodo<T> *p = c;
    int deltaH = 0;

    if (!p) {

        p = new Nodo<T>(dato); //La recursion llega a una hoja
        c = p;
        deltaH = 1;

    } else if (dato > p->dato) {

        if (inserta(p->der, dato)) {
            p->bal--;

            if (p->bal == -1) deltaH = 1;

            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDer(p->der); //Rotacion doble: caso 3

                rotIzq(c); //Rotacion simple: caso 4
            }
        }
    } else if (dato < p->dato) {

        if (inserta(p->izq, dato)) {
            p->bal++;

            if (p->bal == 1) deltaH = 1;

            else if (p->bal == 2) {
                if (p->izq->bal == -1) rotIzq(p->izq); //Rotacion doble: caso 2

                rotDer(c); //Rotacion simple: caso 1
            }
        }
    }
    return deltaH;
}

/**
 * @brief Rotación hacia la derecha
 * @param nodo Nodo que esta desequilibrado y vamos a rotar
 */
template <typename T>
void AVL<T>::rotDer(Nodo<T>*& nodo) {
    Nodo<T> *q = nodo;
    Nodo<T> *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0)
        q->bal -= l->bal;
    l->bal--;
    if (q->bal < 0)
        l->bal -= -q->bal;
}

/**
 * @brief Notación hacia la izquierda 
 * @param nodo Nodo que esta desequilibrado y vamos a rotar
 */
template <typename T>
void AVL<T>::rotIzq(Nodo<T>*& nodo) {
    Nodo<T> *q = nodo;
    Nodo<T> *r;
    nodo = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0)
        q->bal += -r->bal;
    r->bal++;
    if (q->bal > 0)
        r->bal += q->bal;
}

/**
 * @brief Muestra los datos del AVL por inorden (1ºizq,2ºpadre,3ºder)
 * @param p El padre a partir del cual mostrar sus hijos
 * @param nivel El nivel en el que se encuentran los distintos nodos
 */
template <typename T>
void AVL<T>::inorden(Nodo<T>* p, int nivel) {
    if (p) {
        inorden(p->izq, nivel + 1);
        //Sustituir por procesamiento ----
        std::cout << "Procesando nodo " << p->dato;
        std::cout << " en el nivel " << nivel << std::endl;
        //-----------
        inorden(p->der, nivel + 1);
    }
}

/**
 * @brief Busca un elemento a partir de un nodo
 * @param ele El elemento que deseamos buscar
 * @param p El nodo a partir del cual empezar a buscar
 * @return Un puntero al nodo donde se encuentra el elemento que buscábamos 
 */
template <typename T>
Nodo<T>* AVL<T>::busca(T& ele, Nodo<T>* p) {
    if (!p)
        return 0;
    else if (ele < p->dato)
        return busca(ele, p->izq);
    else if (ele > p->dato)
        return busca(ele, p->der);
    else return p;
}

/**
 * @brief Busca un dato
 * @param dato El dato que deseamos buscar
 * @param result El contenido del nodo del elemento que buscábamos
 * @return True si el elemento se encontró y false en caso contrario
 */
template <typename T>
bool AVL<T>::busca(T& dato, T& result) {
    Nodo<T> *p = busca(dato, raiz);
    if (p) {
        result = p->dato;
        return true;
    }
    return false;
}

/**
 * @brief Calcula el numero de elemetos de un AVL
 * @return El número de elementos del AVL
 */
template <typename T>
unsigned int AVL<T>::numElementos() {
    int num = 0;
    if (raiz) {
        Nodo<T> *p = raiz;
        std::queue<Nodo<T>*> cola;
        cola.push(p);

        while (!cola.empty()) {
            p = cola.front();
            cola.pop();
            num++;
            if (p->izq) cola.push(p->izq);
            if (p->der) cola.push(p->der);
        }
        return num;
    } else
        return num; //No hay elementos
}

/**
 * @brief Calcula la altura de un nodo
 * @param nodo El nodo que queremos hayar su altura
 * @return La altura del nodo
 */
template <typename T>
unsigned int AVL<T>::altura(Nodo<T>* &nodo) {
    if (nodo) {
        int _altura = 0;
        int _altura_hijo;
        Nodo<T>* p = nodo;
        if (p->izq) {
            _altura_hijo = altura(p->izq);
            if (_altura < _altura_hijo) _altura = _altura_hijo;
        }
        if (p->der) {
            _altura_hijo = altura(p->der);
            if (_altura < _altura_hijo) _altura = _altura_hijo;
        }
        if (p->dato == raiz->dato) return _altura;
        else return ++_altura;
    }
}

/**
 * @brief Crea un AVL que es una copia a partir del nodo que se le pasa
 * @param nodo El nodo a partir del cual deseamos empezar a copiar
 */
template <typename T>
void AVL<T>::copiaArbol(Nodo<T>* nodo) {
    if (nodo) {
        this->inserta(nodo->dato);
        if (nodo->izq)
            copiaArbol(nodo->izq);
        if (nodo->der)
            copiaArbol(nodo->der);
    }
}

/**
 * @brief Destruye a partir de un nodo
 * @param nodo El nodo a partir de cual deseamos destruir
 */
template <typename T>
void AVL<T>::destruirArbol(Nodo<T>* nodo) {
    if (nodo) {
        Nodo<T> *p = nodo;
        if (p->izq) {
            destruirArbol(p->izq);
            p->izq = 0;
        }
        if (p->der) {
            destruirArbol(p->der);
            p->der = 0;
        }
        if (p->dato == raiz->dato) {
            delete raiz;
            raiz = 0;
        } else {
            delete p;
            p = 0;
        }
    }
}

/**
 * @brief Busca un dato y devuelve un puntero al dato
 * @param dato El dato a buscar
 * @return Un puntero al dato si se ha encontrado o un puntero a NULL si no se encontró
 */
template <typename T>
T* AVL<T>::busca(T& dato) {
    Nodo<T> *p = busca(dato, raiz);
    if (p!=nullptr) return &p->dato;
    else return 0;
}

#endif /* AVL_H */

