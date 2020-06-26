/* 
 * @file Diccionario.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 31 de octubre de 2017, 11:56
 * @note Práctica 5. Árboles AVL
 */

#include "Diccionario.h"

/**
 * @brief Constructor parametrizado
 * @param nombre_fichero Nombre del archivo con el que crear el diccionario 
 * @post Crea un diccionario por parametrización
 */
Diccionario::Diccionario(std::string& nombre_fichero) : _palabras(AVL<Palabra>()) {
    std::ifstream fe;
    std::string linea;

    fe.open(nombre_fichero);
    if (fe.good()) {
        while (!fe.eof()) {
            getline(fe, linea);
            if (linea != "") {
                Palabra p(linea);
                _palabras.inserta(p);
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
    return _palabras.numElementos();
}

/**
 * @brief Entrena el diccionario 
 * @param frase Frase para entrenar el diccionario 
 * @post Entrenar el diccionario a partir de la frase 
 */
void Diccionario::entrena(std::string& frase) {
    std::string anterior, posterior, palabra;
    std::stringstream ss;

    Palabra* esta= nullptr;

    ss << frase;
    ss>>anterior;

    while (!ss.eof()) {
        ss>>palabra;

        if (palabra != "") {
            posterior = palabra;
            esta = this->busca(anterior);

            if (esta != nullptr)
                esta->nuevoSucesor(posterior);
            else {
                Palabra nueva(anterior);
                nueva.nuevoSucesor(posterior);
                this->insertar(nueva);
            }
            palabra = ""; //Piso palabra asigándole la cadena vacía 
            anterior = posterior;
        }
    }

    if (esta == nullptr) {
        Palabra nueva(anterior);
        this->insertar(nueva);
    }
}

/**
 * @brief Extrae las frases de un fichero y entrena el diccionario 
 * @param nom_fich_corpus El nombre del fichero
 * @post Entrenar un diccionario con un fichero 
 */
void Diccionario::usaCorpus(std::string& nom_fich_corpus) {
    std::ifstream fe;
    std::string linea;

    fe.open(nom_fich_corpus);
    if (fe.good()) {
        while (!fe.eof()) {
            getline(fe, linea);
            if (linea != "") {
                entrena(linea);
            }
        }
        fe.close();
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

/**
 * @brief Informa si una palabra tiene sucesores
 * @param palabra La palabra que quiero ver si esta en el diccionario y ver si tiene sucesores
 * @return Devuelve un true si la palabra tiene sucesores y false si no tiene
 */
bool Diccionario::tieneSucesores(std::string& palabra) {
    Palabra* esta=nullptr;
    esta= this->busca(palabra);
    if (esta)
        return esta->tieneSucesores();
    else 
        throw std::invalid_argument("[Diccionario::tieneSucesores]: La palabra no esta en el diccionario.");
}

/**
 * @brief Devuelve mi AVL de palabras
 * @return El AVL de palabras de mi diccionario 
 */
AVL<Palabra> Diccionario::getPalabras() const  {
    return _palabras;
}

/**
 * @brief Busca si una cadena esta en el diccionario 
 * @param cadena La cadena a buscar en el diccionario
 * @return Devuelve un puntero a la palabra del diccionario si estaba, o NULL si no estaba
 * @post Devolver un puntero a una cadena si estaba en el diccionario o NULL si no estaba
 */
Palabra* Diccionario::busca(std::string& cadena) {
    Palabra p(cadena);
    return _palabras.busca(p);
}

/**
 * @brief Inserta una palabra en el diccionario 
 * @param p La palabra a insertar
 * @return Devuelve true si se inserto y false en otro caso
 * @post Insertar una palabrra en el diccionario y saber si se insertó correctamente
 */
bool Diccionario::insertar(Palabra& p) {
    Palabra q;
    if(_palabras.busca(p,q) == false) return _palabras.inserta(p);
    else return false;
}
