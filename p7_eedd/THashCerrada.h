/* 
 * @file THashCerrada.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 21 de noviembre de 2017, 13:19
 * @note Práctica 7. Tablas Hash
 */

/**
 * @brief Valores más óptimos después de entrenar la tabla 
 * Tam=127591  //  primo=17681  ->  13 colisiones
 * Tam=158519  //  primo=13477  ->  9 colisiones
 */

#ifndef THASHCERRADA_H
#define THASHCERRADA_H
#define  _MAX_COLISIONES_ 25
#include <vector>
#include <stdio.h>
#include <stdexcept>

/**
 * @brief Estado de la casilla
 * @param Vacia si la casilla jamás contuvo un dato
 * @param Disponible si la casilla esta libre pero contuvo un dato
 * @param Ocupada si la casilla contine un dato
 */
enum Estado {
    VACIA, DISPONIBLE, OCUPADA
};

/**
 * @brief Clase casilla 
 */
template <class T>
class Casilla {
public:
    long _clave;//<Clave del dato
    T _dato;//<El dato
    Estado _estado;//<El estado de la casilla
    
    Casilla(): _clave(-1),_dato(),_estado(VACIA){}
    Casilla(long clave, T& dato, Estado estado = OCUPADA) : _clave(clave), _dato(dato), _estado(estado) {}
    void insertar(long clave, T& dato) { _clave = clave; _dato = dato; _estado = OCUPADA;}
    void borrar() { _estado = 1;}
    virtual ~Casilla() {}
};

/**
 * @brief Clase tabla hash cerrada
 */
template <class T>
class THashCerrada {
public:
    THashCerrada(int tamaTabla=127591,int pri=17681);
    THashCerrada(const THashCerrada& orig);

    virtual ~THashCerrada() {}

    bool insertar(long int clave, T& dato);
    bool borrar(long int clave, T& dato);
    T* buscar(long int clave, T& dato);
    unsigned int tamaTabla();
    unsigned int numElementos();
    unsigned int maxColisiones();
    unsigned int promedioColisiones();
    float factorCarga();
    long int fDispersion(long int clave, int i) { exploracionDoble(clave, i);}

private:
    std::vector<Casilla<T> > _tabla; //<Tabla 
    int _numElementos; //<Número de elementos de la tabla 
    int _totalColisiones;//<Total de colisiones producidas
    int _maxColisiones;//<Máximo de colisiones en cualquier operación de inserción
    int _totalInserciones;//<Total de inserciónes
    int PRIMO_1;//<Un primo
    
    long int exploracionCuadratica(long int clave, int i) { return (clave + i^2) % _tabla.size();}
    long int exploracionDoble(long int clave, int i) { return ((clave % _tabla.size()) + i * (PRIMO_1 - clave % PRIMO_1)) % _tabla.size();}
    Casilla<T>* busca(long int clave, T& dato);
};

#endif /* THASHCERRADA_H */

/**
 * @brief Constructor parametrizado
 * @param tamaTabla Tamaño de la tabla hash 
 * @post Crea una tabla hash con un tamaño igual a tamaTabla 
 */
template <class T>
THashCerrada<T>::THashCerrada(int tamaTabla, int pri) :
_tabla(std::vector<Casilla<T> >(tamaTabla)), _numElementos(0), _totalColisiones(0), _maxColisiones(0), _totalInserciones(0),PRIMO_1(pri) {
}

/**
 * @brief Constuctor de copia
 * @param orig La tabla hash que se quiere copiar
 * @post Crea un tabla hash igual a orig
 */
template <class T>
THashCerrada<T>::THashCerrada(const THashCerrada& orig) :
_tabla(orig._tabla), _numElementos(orig._numElementos), _totalColisiones(orig._totalColisiones), 
        _maxColisiones(orig._maxColisiones), _totalInserciones(orig._totalInserciones), PRIMO_1(orig.PRIMO_1) {
}

/**
 * @brief Inserta un dato junto con su clave en la tabla
 * @param clave La clave asociada al dato
 * @param dato El dato a insertar
 * @return Devuelve true si se inserto el dato en la tabla y false ni no se insertó
 */
template <class T>
bool THashCerrada<T>::insertar(long int clave, T& dato) {
    _totalInserciones++; //Cuenta de total de insercciones  (haya habido exito o no)
    int intentos = 0;
    long int valor;
    while (intentos < _MAX_COLISIONES_) {
        valor = fDispersion(clave, intentos);
        if (_tabla[valor]._dato != dato) {
            if (_tabla[valor]._estado == DISPONIBLE || _tabla[valor]._estado == VACIA) { //La casilla esta disponible o vacia para insertar el dato
                _tabla[valor].insertar(clave, dato);
                _numElementos++;
                return true;
            }
        } else return false; //Si en la casilla esta el dato que se va insertar no se inserta de nuevo
        intentos++;
        if(intentos>_maxColisiones){//Si los intentos son mayores que el máximo de colisiones se cambia
            _maxColisiones=intentos;
        }
        _totalColisiones++; //Cuenta del maximo de colisiones producidas
    }
    return false;
}

/**
 * @brief Borra un dato de la tabla 
 * @param clave La clave asociada al dato
 * @param dato El dato a eliminar
 * @return Devuelve true si se eliminó correctamente y false en otro caso
 */
template <class T>
bool THashCerrada<T>::borrar(long int clave, T& dato) {
    auto esta = busca(clave, dato);
    if (esta) {
        esta->borrar();
        _numElementos--;
        return true;
    }
    return false;
}

/**
 * @brief Busca un dato y devuelve la casilla donde se encuentra dicho dato
 * @param clave La clave asociada al dato
 * @param dato El dato a buscar
 * @return Un puntero a la casilla si se encontró el dato y NULL si no se encontró
 */
template<class T>
Casilla<T>* THashCerrada<T>::busca(long int clave, T& dato) {
    int intentos = 0;
    long int valor;
    while (intentos < _MAX_COLISIONES_) {
        valor = fDispersion(clave, intentos);
        if (_tabla[valor]._estado == OCUPADA) { //La casilla esta ocupada
            if (_tabla[valor]._dato == dato) return &_tabla[valor]; //Si el dato de la casilla es igual al dato que se nos pasa
        } else if (_tabla[valor]._estado == VACIA) return nullptr; //Si la casilla esta vacia, fin de busqueda y se devuelve puntero a NULL

        intentos++;
    }
    return nullptr;
}

/**
 * @brief Busca un dato y devuelve un puntero al dato
 * @param clave La clave asociada al dato
 * @param dato El dato a buscar
 * @return Un puntero al dato si se encontró y NULL si no se encontró
 */
template <class T>
T* THashCerrada<T>::buscar(long int clave, T& dato) {
    int intentos = 0;
    long int valor;
    while (intentos < _MAX_COLISIONES_) {
        valor = fDispersion(clave, intentos);
        if (_tabla[valor]._estado==OCUPADA) { //La casilla esta ocupada
            if (_tabla[valor]._dato == dato) return &_tabla[valor]._dato; //Si el dato de la casilla es igual al dato que se nos pasa
        } else if (_tabla[valor]._estado==VACIA) return nullptr; //Si la casilla esta vacia, fin de busqueda y se devuelve puntero a NULL

        intentos++;
    }
    return nullptr;
}

/**
 * @brief Devuelve el número de elementos insertados en la tabla 
 * @return Número de elementos de la tabla
 */
template <class T>
unsigned int THashCerrada<T>::numElementos() {
    return _numElementos;
}

/**
 * @brief Devuelve el número máximo de colisiones que se han producido por operación de inserción
 * @return Número de colisiones que se han producido por operación de inserción
 */
template <class T>
unsigned int THashCerrada<T>::maxColisiones() {
    return _maxColisiones;
}

/**
 * @brief Devuelve el promedio de colisiones por operación de inserción
 * @return Promedio de colisiones producidas en operaciones de inserción
 */
template <class T>
unsigned int THashCerrada<T>::promedioColisiones() {
    return _totalColisiones/_totalInserciones;
}

/**
 * @brief Devuelve el factor de carga de la tabla
 * @return El factor de carga de la tabla 
 */
template <class T>
float THashCerrada<T>::factorCarga() {
    return (float)_numElementos/_tabla.size();
}

/**
 * @brief Método que devuelve el tamaño de la tabla
 * @return El tamaño de la tabla 
 */
template <class T>
unsigned int THashCerrada<T>::tamaTabla() {
    return _tabla.size();
}