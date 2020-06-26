/* 
 * @file Diccionario.cpp
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 14 de octubre de 2017, 12:20
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#include "Diccionario.h"

/**
 * @brief Constructor parametrizado
 * @param nombre_fichero Nombre del archivo con el que crear el diccionario 
 * @post Crea un diccionario por parametrización
 */
Diccionario::Diccionario(std::string& nombre_fichero) : _palabras(new VectorDinamico<Palabra>(80383)) {
    std::ifstream fe;
    std::string linea;
    int total = 0;

    fe.open(nombre_fichero);
    if (fe.good()) {
        while (!fe.eof()) {
            getline(fe, linea);
            if (linea != "") {
                Palabra p(linea);
                _palabras->insertar(p); //insertar palabra haciendo hueco sin necesidad de ordenar luego
                total++;
            }
        }
        std::cout << "Total de palabras en el archivo: " << total << std::endl;
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
Diccionario::Diccionario(const Diccionario& orig) {
    _palabras = new VectorDinamico<Palabra>(orig._palabras->tam());
    for (int i = 0; i < _palabras->tam(); i++)
        _palabras[i] = orig._palabras[i];
}

/**
 * @brief Destructor de la clase 
 * @post Destruye un objeto diccionario 
 */
Diccionario::~Diccionario() {
    delete _palabras;
}

/**
 * @brief Numero de palabras en el diccionario 
 * @return El número de palabras existentes en el diccionario 
 */
int Diccionario::numPalabras() {
    return _palabras->tam();
}

/**
 * @brief Entrena el diccionario 
 * @param frase Frase para entrenar el diccionario 
 * @post Entrenar el diccionario a partir de la frase 
 */
void Diccionario::entrena(std::string& frase) {
    std::string anterior, posterior, palabra;
    std::stringstream ss;

    Palabra* esta = 0;
    bool esnumero;

    ss << frase;
    ss>>anterior;

    while (!ss.eof()) {
        ss>>palabra;

        if (palabra != "") {

            posterior = palabra;
            esta = this->buscar(anterior);

            if (esta != 0)
                esta->nuevoSucesor(posterior);
            else {
                Palabra nueva(anterior);
                nueva.nuevoSucesor(posterior);

                //Comprobamos que la palabra nueva es un número

                this->insertar(nueva);

            }
            palabra = ""; //Piso palabra asigándole la cadena vacía 
            anterior = posterior;
        }
    }
    //Comprobamos que posterior es un numero


    Palabra nueva(anterior);
    esta = this->buscar(anterior);

    if (esta == 0)
        this->insertar(nueva);

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
       // bool tieneNumeros = false;
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
    std::cout << " El diccionario se ha entrenado correctamente" << std::endl;
}

/**
 * @brief Muestra los sucesores de una palabra de mi diccionario 
 * @param palabra La palabrra que quiero mostrar los sucesores
 * @note Si la palabra no esta en el diccionario se nos avisa mediante un mensaje
 * @return Devuelve un 1 si la palabra tiene sucesores o -1 en otro caso
 */
int Diccionario::mostrarSucesores(std::string& palabra) {
    Palabra palabra_buscar(palabra);
    auto p = buscar(palabra);
    if (p != nullptr) {
        return p->mostrarSucesoresOrdenados();
    } else {
        std::cout << "La palabra no esta en el diccionario" << std::endl;
        return -1;
    }
}

/**
 * @brief Devuelve mi vector de palabras
 * @return El vector de palabras de mi diccionario 
 */
VectorDinamico<Palabra>* Diccionario::getPalabras() const {
    return _palabras;
}

/**
 * @brief Busca si una cadena esta en el diccionario 
 * @param cadena La cadena a buscar en el diccionario
 * @return Devuelve un puntero a la palabra del diccionario si estaba, o NULL si no estaba
 * @post Devolver un puntero a una cadena si estaba en el diccionario o NULL si no estaba
 */
Palabra* Diccionario::buscar(std::string& cadena) {
    Palabra p(cadena);
    auto pos = _palabras->busquedaBin(p);
    if (pos != -1) { //esta
        return &(*_palabras)[pos];
    } else {
        return nullptr;
    }
}

/**
 * @brief Inserta una palabra en el diccionario de manera ordenada
 * @param p La palabra a insertar
 * @return Devuelve la posición donde se insertó la palabra o -1 si no se puedo insertar
 * @post Insertar una palabrra en el diccionario y saber en que posición se insertó
 */
bool Diccionario::insertar(Palabra& p) {
    int i = 0;
    auto tam = _palabras->tam();

    for (i = 0; i < _palabras->tam(); ++i) {
        if (p.GetTermino() <= (*_palabras)[i].GetTermino()) {
            if (p.GetTermino() < (*_palabras)[i].GetTermino()){
                _palabras->insertar(p, i);
            return true;
        }
        }
    }
    return false;
}
