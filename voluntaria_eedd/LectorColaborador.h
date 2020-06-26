/* 
 * @file LectorColaborador.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 14 de diciembre de 2017, 14:15
 * @note Práctica Voluntaria
 */

#ifndef LECTORCOLABORADOR_H
#define LECTORCOLABORADOR_H

#include "Libro.h"

#include <stdexcept>
#include <queue>
#include <cmath>

/**
 * @brief Clase que almacena la información de un lector (colaborador)
 */
class LectorColaborador {
public:
    std::string _alias; //<Alias del lector
    int _maxLibros; //<Máximo de libros que el lector va a leer
    std::queue<Libro*> _adjudicados; //<Libros que el lector tiene adjudicados

    LectorColaborador(std::string alias, int maxLibros);
    LectorColaborador(const LectorColaborador& orig);
    virtual ~LectorColaborador();

    Libro* getSiguienteLibro();
    void emitirEvaluacion(int nota);
    void adjudicarLibro(Libro& l);
    
    bool aceptaLibro();
};

#endif /* LECTORCOLABORADOR_H */