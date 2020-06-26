/* 
 * @file Sucesor.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 14 de octubre de 2017, 12:20
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#ifndef SUCESOR_H
#define SUCESOR_H
#include <string>

/**
 * @brief Clase sucesor 
 */
class Sucesor {
public:
    Sucesor(std::string termino = "",int _numOcurrencias=1);
    Sucesor(const Sucesor& orig);
    virtual ~Sucesor();
    Sucesor& operator=(const Sucesor& orig);

    void incrementarOcurrencias();
    std::string getTermino() const;
    int getNumOcurrencias() const;

private:
    std::string _termino; //<Término del sucesor
    int _numOcurrencias; //<Número de ocurrencias del sucesor
};

#endif /* SUCESOR_H */

