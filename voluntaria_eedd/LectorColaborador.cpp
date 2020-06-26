/* 
 * @file LectorColaborador.cpp
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 14 de diciembre de 2017, 14:15
 * @note Práctica Voluntaria
 */

#include <stdexcept>

#include "LectorColaborador.h"

/**
 * @brief Constructor parametrizado
 * @param alias El alias del lector
 * @post Crea un LectorColaborador por parametrización
 */
LectorColaborador::LectorColaborador(std::string alias, int maxLibros) :
_alias(alias), _maxLibros(maxLibros), _adjudicados() {
}

/**
 * @brief Constructor de copia 
 * @param orig El LectorColaborador que se desea copiar
 * @post Crea un LectorColaborador que es una copia de orig
 */
LectorColaborador::LectorColaborador(const LectorColaborador& orig) :
_alias(orig._alias), _maxLibros(orig._maxLibros), _adjudicados(orig._adjudicados) {
}

/**
 * @brief Destructor de la clase
 * @post Destruye un objeto
 */
LectorColaborador::~LectorColaborador() {
    while (!_adjudicados.empty()) _adjudicados.pop();
}

/**
 * @brief Devuelve el primer libro de la cola de libros adjudicados
 * @return Devolver el primer libro de la cola de adjudicados al lector, eliminándolo de la misma
 */
Libro* LectorColaborador::getSiguienteLibro() {
    if (!_adjudicados.empty()) {
        Libro *l = _adjudicados.front(); //Asigno a l el primer libro adjudicado de la lista
        _adjudicados.pop(); //Saco el primer libro de la lista de adjudicados
        return &(*l); //Devuelvo el primer libro adjudicado de la lista
    } else throw std::logic_error("[LectorColaborador::getSiguienteLibro()]: El lector no esta leyendo ningún libro.");
}

/**
 * @brief Emite una evaluación sobre un Libro
 * @param nota Nota hacia el Libro
 * @post Emitir una evaluación sobre un Libro
 */
void LectorColaborador::emitirEvaluacion(int nota) {
    Libro *l = _adjudicados.front();
    _adjudicados.pop();
    l->opinionRecibida(nota);
}

/**
 * @brief Adjudica un libro al LectorColaborador 
 * @param l El nuevo libro que se va a adjudicar al LectorColaborador
 * @throw Si el LectorColaborador se encuentra leyendo su máximo de libros permitidos lanza un excepción
 * @post Adjudicar un libro al LectorColaborador 
 */
void LectorColaborador::adjudicarLibro(Libro& l) {
    _adjudicados.push(&l);
}

/**
 * @brief Informa si el LectorColaborador acepta leer más Libros
 * @return Devuelve true si acepta leer más y false si no
 * @post Informar si el LectorColaborador acepta leer más Libros
 */
bool LectorColaborador::aceptaLibro() {
    return _adjudicados.size() < _maxLibros;
}