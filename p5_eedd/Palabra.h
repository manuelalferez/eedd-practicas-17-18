/* 
 * @file Palabra.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 31 de octubre de 2017, 11:56
 * @note Práctica 5. Árboles AVL
 */

#ifndef PALABRA_H
#define PALABRA_H
#include "Sucesor.h"
#include <list>
#include <iostream>
#include <queue>

/**
 * @brief Clase palabra 
 */
class Palabra {
public:
    Palabra(std::string termino = "");
    Palabra(const Palabra& orig);
    virtual ~Palabra();

    void SetTermino(std::string termino);
    std::string GetTermino() const;
    
   bool operator==(Palabra &palabra);
    bool operator<(Palabra &palabra);
    bool operator>(Palabra &palabra);
    Palabra& operator=(const Palabra& orig);
    bool operator<=(Palabra &p);

    void nuevoSucesor(std::string& cadena);
    std::priority_queue<Sucesor> sucesores();
    bool tieneSucesores();

private:
    std::priority_queue<Sucesor> _ordenada; //<Sucesores de la palabra ordenados
    std::string _termino; //< Término de la palabra
    std::list<Sucesor> _siguientes; //< Sucesores de la palabra
};

#endif /* PALABRA_H */


