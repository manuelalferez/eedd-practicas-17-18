/* 
 * @file Sucesor.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 14 de noviembre de 2017, 15:40
 * @note Practica 6. Contenedores asociativos de STL
 */

#ifndef SUCESOR_H
#define SUCESOR_H
#include <iostream>

/**
 * @brief Clase sucesor 
 */
class Sucesor {
public:
    Sucesor(std::string termino = "",int numOcurrencias=1);
    Sucesor(const Sucesor& orig);
    virtual ~Sucesor();
    Sucesor& operator=(const Sucesor& orig);

    void incrementarOcurrencias();
    std::string getTermino() const;
    int getNumOcurrencias() const;
    
    bool operator<(const Sucesor& orig) const;
private:
    std::string _termino; //<Término del sucesor
    int _numOcurrencias; //<Número de ocurrencias del sucesor
};

#endif /* SUCESOR_H */