/* 
 * @file Diccionario.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 21 de noviembre de 2017, 13:19
 * @note Práctica 7. Tablas Hash
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
Diccionario::Diccionario(std::string& nombre_fichero, int tama, int pri) : _palabras(tama, pri) {
    std::ifstream fe;
    std::string linea;

    fe.open(nombre_fichero);
    if (fe.good()) {
        while (!fe.eof()) {
            getline(fe, linea);
            if (linea != "") {
                Palabra p(linea);
                auto clave = djb2((unsigned char*) linea.c_str());
                _palabras.insertar(clave, p);
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
 * @brief Busca si una cadena esta en el diccionario 
 * @param cadena La cadena a buscar en el diccionario
 * @return Devuelve un puntero a la palabra del diccionario si estaba, o NULL si no estaba
 * @post Devolver un puntero a una palabra si estaba en el diccionario o NULL si no estaba
 */
Palabra* Diccionario::busca(std::string& cadena) {
    Palabra p(cadena);
    auto clave = djb2((unsigned char*) cadena.c_str());
    auto esta = _palabras.buscar(clave, p);
    if (esta) return esta;
    else return nullptr;
}

/**
 * @brief Inserta una palabra en el diccionario 
 * @param p La palabra a insertar
 * @post Insertar una palabrra en el diccionario, (si estaba no se inserta)
 */
void Diccionario::inserta(Palabra& p) {
    auto clave = djb2((unsigned char*) p.GetTermino().c_str());
    _palabras.insertar(clave, p);
}

/**
 * @brief Entrenar el diccionario
 * @param termino1 Primer termino
 * @param termino2 El segundo termino (el que le sigue a termino1)
 * @post Si ambos terminos estan en el diccionario se inserta termino2 como sucesor de la palabra con el termino1, sino no se hace nada
 */
void Diccionario::entrena(std::string& termino1, std::string& termino2) {
    auto clave = djb2((unsigned char*) termino1.c_str());
    Palabra p(termino1);
    auto esta1 = _palabras.buscar(clave, p);
    if (esta1) { //termino1 esta en el diccionario
        clave = djb2((unsigned char*) termino2.c_str());
        Palabra q(termino2);
        auto esta2 = _palabras.buscar(clave, q);
        if (esta2) esta1->nuevoSucesor(termino2); //termino2 esta en el diccionario 
    }
}

THashCerrada<Palabra>* Diccionario::getPalabras() {
    return &_palabras;
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
                entrenar(linea);
            }
        }
        fe.close();
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

/**
 * @brief Entrena el diccionario 
 * @param frase Frase para entrenar el diccionario 
 * @post Entrenar el diccionario a partir de la frase 
 */
void Diccionario::entrenar(std::string& frase) {
    std::string anterior, posterior, palabra;
    std::stringstream ss;

    Palabra* esta = nullptr;

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
                this->inserta(nueva);
            }
            palabra = ""; //Piso palabra asigándole la cadena vacía 
            anterior = posterior;
        }
    }

    if (esta == nullptr) {
        Palabra nueva(anterior);
        this->inserta(nueva);
    }
}