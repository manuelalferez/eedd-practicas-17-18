/* 
 * @file Libro.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 14 de diciembre de 2017, 14:15
 * @note Práctica Voluntaria
 */

#include "Libro.h"
#include "Editorial.h"

/**
 * @brief Constructor por defecto
 * @post Crea un Libro por defecto
 */
Libro::Libro() :
_isbn(), _titulo(), _autor(), _estado(espera), _notaAcumulada(0),
_numOpiniones(0), _url(), _editorial(0) {
}

/**
 * @brief Constructor parametrizado
 * @param titulo El título del Libro
 * @param autor El autor del Libro
 * @param editorial Puntero a la Editorial asociada al Libro
 * @psot Crea un Libro por parametrización
 */
Libro::Libro(std::string isbn, std::string titulo, std::string autor, Editorial *editorial) :
_isbn(isbn), _titulo(titulo), _autor(autor), _estado(espera),
_notaAcumulada(0), _numOpiniones(0), _url(), _editorial(editorial) {
}

/**
 * @brief Constructor de copia
 * @param orig El Libro que se desea copiar
 * @post Crea un Libro que es una copia de orig
 */
Libro::Libro(const Libro& orig) :
_isbn(orig._isbn), _titulo(orig._titulo), _autor(orig._autor),
_estado(orig._estado), _notaAcumulada(orig._notaAcumulada),
_numOpiniones(orig._numOpiniones), _url(orig._url), _editorial(orig._editorial) {
}

/**
 * @brief Destructor de la clase
 * @post Destruye un objeto
 */
Libro::~Libro() {
}

/**
 * @brief Recibe una opinión para el Libro
 * @param nota Puntuación que se le ha otorgado al Libro
 * @note1 Si la nota es menor que 5 se considera que el Libro no se publica
 * @note2 Si la sumatoria de las 3 notas acumuladas es menor que 21 no se publica
 * @note3 Si la sumatoria es mayor que 21 entonces se publica el Libro
 * @post Recibir una opinión para el Libro y realizar una desisión cuando se cumplen ciertas condiciones
 */
void Libro::opinionRecibida(int nota) {
    if (nota < 5) decisionTomada(false);
    else _notaAcumulada += nota;

    if (_numOpiniones == MAX_OPINIONES)
        if (_notaAcumulada < MIN_PUNTOS) decisionTomada(false);
        else decisionTomada(true);
}

/**
 * @brief Toma una decisión de si publicar el Libro o no
 * @param se_publica Si se_publica=true se publicará el Libro en caso contrario no se publicará
 * @note1 Tanto como si se publica el Libro como si no, se notificará a la Editorial la orden de si Publicar el Libro o no
 * @post Tomar una decisión de si publicar el Libro o no
 */
void Libro::decisionTomada(bool se_publica) {
    if (se_publica) _editorial->siPublicarLibro(this);
    else _editorial->noPublicarLibro(this);
}

/**
 * @brief Asigna una URL al Libro
 * @param url La URL a asignar el Libro
 * @post Asignar una URL al Libro
 */
void Libro::asignarURL(std::string url) {
    _url = url;
}