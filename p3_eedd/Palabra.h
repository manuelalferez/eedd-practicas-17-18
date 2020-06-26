/* 
 * @file Palabra.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 14 de octubre de 2017, 12:20
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#ifndef PALABRA_H
#define PALABRA_H
#include "Sucesor.h"
#include "ListaEnlazada.h"
#include <iostream>

/**
 * @brief Clase palabra 
 */
class Palabra {
public:
    Palabra(std::string termino = "", int numSucesores=0);
    Palabra(const Palabra& orig);
    virtual ~Palabra();

    void SetTermino(std::string _termino);
    std::string GetTermino() const;
    bool operator==(Palabra &palabra);
    bool operator<(Palabra &palabra);
    Palabra& operator=(const Palabra& orig);
    bool operator<=(Palabra &p);
    void nuevoSucesor(std::string& cadena);
    ListaEnlazada<Sucesor>& sucesores();
    int mostrarSucesoresOrdenados();

private:
    std::string _termino; //< Término de la palabra
    ListaEnlazada<Sucesor> _siguientes; //< Sucesores de la palabra
};

#endif /* PALABRA_H */

