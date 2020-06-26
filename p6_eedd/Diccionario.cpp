/* 
 * @file Diccionario.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 14 de noviembre de 2017, 15:40
 * @note Practica 6. Contenedores asociativos de STL
 */

#include "Diccionario.h"

/**
 * @brief Constructor por defecto
 * @post Crea un diccionario por defecto
 */
Diccionario::Diccionario() :
_palabras() {
}

/**
 * @brief Constructor parametrizado
 * @param nombre_fichero Nombre del archivo con el que crear el diccionario 
 * @post Crea un diccionario por parametrización
 */
Diccionario::Diccionario(std::string& nombre_fichero) : _palabras() {
    std::ifstream fe;
    std::string linea;

    fe.open(nombre_fichero);
    if (fe.good()) {
        while (!fe.eof()) {
            getline(fe, linea);
            if (linea != "") {
                Palabra p(linea);
                _palabras.insert(std::pair<std::string, Palabra>(linea, p));
            }
        }
        fe.close();
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

/**
 * @brief Constructor de copia 
 * @param orig El diccionario que se quiere copiar 
 * @post Crear un diccionario que es una copia de orig 
 */
Diccionario::Diccionario(const Diccionario& orig) : _palabras(orig._palabras) {

}

/**
 * @brief Destructor de la clase 
 * @post Destruye un objeto diccionario 
 */
Diccionario::~Diccionario() {
}

/**
 * @brief Numero de palabras en el diccionario 
 * @return El número de palabras existentes en el diccionario 
 */
int Diccionario::numPalabras() {
    return _palabras.size();
}

/**
 * @brief Informa si una palabra tiene sucesores
 * @param palabra La palabra que quiero ver si esta en el diccionario y ver si tiene sucesores
 * @return Devuelve un true si la palabra tiene sucesores y false si no tiene
 */
bool Diccionario::tieneSucesores(std::string& palabra) {
    Palabra* esta = nullptr;
    esta = this->busca(palabra);
    if (esta)
        return esta->tieneSucesores();
    else
        throw std::invalid_argument("[Diccionario::tieneSucesores]: La palabra no esta en el diccionario.");
}

/**
 * @brief Devuelve mi MAP de palabras
 * @return El MAP de palabras de mi diccionario 
 */
std::map<std::string, Palabra> Diccionario::getPalabras() const {
    return _palabras;
}

/**
 * @brief Busca si una cadena esta en el diccionario 
 * @param cadena La cadena a buscar en el diccionario
 * @return Devuelve un puntero a la palabra del diccionario si estaba, o NULL si no estaba
 * @post Devolver un puntero a una palabra si estaba en el diccionario o NULL si no estaba
 */
Palabra* Diccionario::busca(std::string& cadena) {
    auto i = _palabras.find(cadena);
    if (i != _palabras.end()) return &(i->second);
    else return nullptr;
}

/**
 * @brief Inserta una palabra en el diccionario 
 * @param p La palabra a insertar
 * @post Insertar una palabrra en el diccionario, (si estaba no se inserta)
 */
void Diccionario::inserta(Palabra& p) {
    _palabras.insert(std::pair<std::string, Palabra>(p.GetTermino(), p));
}

/**
 * @brief Entrenar el diccionario
 * @param termino1 Primer termino
 * @param termino2 El segundo termino (el que le sigue a termino1)
 * @post Si ambos terminos estan en el diccionario se inserta termino2 como sucesor de la palabra con el termino1, sino no se hace nada
 */
void Diccionario::entrena(std::string& termino1, std::string& termino2) {
    auto i = _palabras.find(termino1);
    if (i != _palabras.end()) {//termino1 esta en el diccionario
        auto j = _palabras.find(termino2);
        if (j != _palabras.end()) {//termino2 esta en el diccionario
            i->second.nuevoSucesor(termino2);
        }
    }
}
