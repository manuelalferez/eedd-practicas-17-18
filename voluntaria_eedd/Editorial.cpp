/* 
 * @file Editorial.cpp
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 14 de diciembre de 2017, 14:15
 * @note Práctica Voluntaria
 */

#include "Editorial.h"

/**
 * @brief Constructor por defecto 
 * @post Crear una Editorial por defecto
 */
Editorial::Editorial() :
_libros(), _colaboradores(), _librosPublicados(), _librosNoPublicados(), _librosEnRevision() {
}

/**
 * @brief Constructor de copia
 * @param orig La Editorial que se quiere copiar
 * @post Crea una Editorial que es una copia de orig
 */
Editorial::Editorial(const Editorial& orig) :
_libros(orig._libros), _colaboradores(orig._colaboradores),
_librosPublicados(orig._librosPublicados), _librosNoPublicados(orig._librosNoPublicados),
_librosEnRevision(orig._librosEnRevision) {
}

/**
 * @brief Destructor de la clase
 * @post Destruye un objeto
 */
Editorial::~Editorial() {
}

/**
 * @brief Insertar un Libro en el sistema
 * @param isbn El ISBN del Libro
 * @param titulo El título del Libro
 * @param autor El autor del Libro 
 * @return 
 */
void Editorial::nuevoLibro(std::string isbn, std::string titulo, std::string autor) {
    Libro l(isbn, titulo, autor, this); //Creación del Libro
    _libros.push(l); //Insercción en la cola
    _libros.back().asignarURL(generaURL());
}

/**
 * @brief Devuelve el siguiente Libro de la cola
 * @return El siguiente Libro de la cola
 * @post Devolver el siguiente Libro de la cola 
 */
Libro Editorial::getSiguienteLibro() {
    Libro l = _libros.front();
    _libros.pop();
    return l;
}

/**
 * @brief Decide si aceptar la revisión de un Libro o no
 * @param l El Libro que se quiere aceptar su revisión
 * @note1 Aceptará la revisión si se encuentra a tres Lectores para que lo lean
 * @return Devuelve true si acepta la revisión del Libro y false si no la acepta
 */
bool Editorial::aceptarRevision(Libro& l) {
    int numLectores = 0;
    auto i = _colaboradores.begin();
    do {
        if (i.base()->aceptaLibro()) numLectores++;
        i++;
    } while (i != _colaboradores.end() && numLectores != 3);

    if (numLectores == 3) { //Se comprueba que si hay 3 Lectores disponibles
        l._estado = en_revision;
        _librosEnRevision.push_back(l); //Se encola en la lista de Libros en revisión
        adjudicarLibro3Lectores(l); //<Se adjudica a 3 Lectores
    } else {
        _libros.push(l); //Se encola en la cola de Libros en espera
        return false;
    }
}

/**
 * @brief Almacena un Libro en el histórico de Libros no publicados
 * @param l El Libro a insertar 
 * @post Almacena un Libro en el histórico de Libros no publicados
 */
void Editorial::noPublicarLibro(Libro* l) {
    l->_estado = no_publicable;
    _librosNoPublicados[l->_isbn] = (*l);
}

/**
 * @brief Almacena un Libro, que ha sido publicado, en la base de Libros online
 * @param l El Libro a insertar 
 * @post Almacenar un Libro, que ha sido publicado, en la base de Libros online 
 */
void Editorial::siPublicarLibro(Libro* l) {
    l->_estado = publicado;
    _librosPublicados[l->_isbn] = (*l);
}

/**
 * @brief Adjudica un Libro a tres Lectores
 * @param l El libro a adjudicar
 * @post Adjudicar un Libro a tres Lectores
 */
void Editorial::adjudicarLibro3Lectores(Libro& l) {
    int numLectores = 0;
    auto i = _colaboradores.begin();
    do {
        if (i.base()->aceptaLibro()) {
            numLectores++;
            i.base()->adjudicarLibro(l);
        }
        i++;
    } while (i != _colaboradores.end() && numLectores != 3);
}

/**
 * @brief Genera una URL a partir del último Libro insertado
 * @return Una URL a partir del último Libro insertado
 * @post Generar una URL 
 */
std::string Editorial::generaURL() {
    return ("https://www.amazon.es/" + _libros.back()._titulo + "-" + _libros.back()._autor);
}

/**
 * @brief Añade un nuevo colaborador a la Editorial 
 * @param alias El alias del lector
 * @post Añadir un nuevo colaborador a la Editorial 
 */
void Editorial::nuevoLector(std::string alias, int maxLibros) {
    LectorColaborador lector(alias, maxLibros);
    _colaboradores.push_back(lector);
}

/**
 * @brief Devuelve el número de Libros que están en espera de ser revisados
 * @return El número de Libros que están en espera de ser revisados
 * @post Devolver el número de Libros que están en espera de ser revisados
 */
int Editorial::numLibrosEnEspera() {
    return _libros.size();
}

/**
 * @brief Devuelve el número de Libros que están en revisión
 * @return El número de Libros que están en revisión
 * @post Devolver el número de Libros que se encuentran en revisión
 */
int Editorial::numLibrosEnRevision() {
    return _librosEnRevision.size();
}

/**
 * @brief Muestra la carga de los Lectores
 * @post Informar sobre el alias del Lector y la carga de Libros asignados. 
 */
void Editorial::muestraCargaLectores() {
    for (int i = 0; i < _colaboradores.size(); i++)
        std::cout << "   " << _colaboradores[i]._alias << "| Carga: " << (_colaboradores[i]._adjudicados.size() / _colaboradores[i]._maxLibros)*100 << "%." << std::endl;
}

/**
 * @brief Elige un Lector aleatoriamente y emite una evaluación aleatoria
 * @note Si el Lector generado no está leyendo ningún Libros, entonces generará otro Lector aleatorio 
 * @post Eligir un Lector aleatoriamente y que emita una evaluación aleatoria entre 0 y 10
 */
void Editorial::valorarAleatoriamente() {
    int lectorAleatorio;
    bool evaluacion = false;
    for (int i = 0; i < _colaboradores.size() && evaluacion == false; i++) {
        lectorAleatorio = rand() % _colaboradores.size();
        if (!_colaboradores[lectorAleatorio]._adjudicados.empty()) { //Comprueba que el Lector tiene Libros asignados
            int notaAleatoria = rand() % 11;
            _colaboradores[lectorAleatorio].emitirEvaluacion(notaAleatoria);
            evaluacion=true;
        }
    }
}

/**
 * @brief Muestra un listado con los Libros publicados por el sistema
 * @post Mostrar un listado con los Libros publicados por el sistema
 */
void Editorial::muestraLibrosPublicados() {
    if (!_librosPublicados.empty()) {
        auto it = _librosPublicados.begin();
        std::cout << "    ISBN;TITULO;AUTOR;ESTADO" << std::endl;

        while (it != _librosPublicados.end()) {
            std::cout << "   " << it->second._isbn << ";" << it->second._titulo << ";" << it->second._autor << ";" << it->second._estado << std::endl;
            it++;
        }
    } else {
        std::cout << "   Ningún Libro en la base de datos de Libros publicados." << std::endl;
    }
}

/**
 * @brief Muestra un listado con los Libros no publicados
 * @post Mostrar un listado con los Libros no publicados por el sistema
 */
void Editorial::muestraLibrosNoPublicados() {
    auto it = _librosNoPublicados.begin();
    if (it != _librosNoPublicados.end()) {
        std::cout << "    ISBN;TITULO;AUTOR;ESTADO(0: espera, 1: en_revision, 2: no_publicado, 3: publicado)" << std::endl;

        while (it != _librosNoPublicados.end()) {
            std::cout << "   " << it->second._isbn << ";" << it->second._titulo << ";" << it->second._autor << ";" << it->second._estado << std::endl;
            it++;
        }
    } else {
        std::cout << "   Ningún Libro en la base de datos de Libros no publicados." << std::endl;
    }
}