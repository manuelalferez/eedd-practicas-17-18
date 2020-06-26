/* 
 * @file Palabra.cpp
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 24 de octubre de 2017, 16:11
 * @note Práctica 4. STL de contenedores lineales
 */
#include "Palabra.h"
#include <vector>
#include <queue>

/**
 * @brief Constructor por defecto parametrizado
 * @param termino El termino
 * @post Crear una palabra por defecto o parametrización
 */
Palabra::Palabra(std::string termino) :
_siguientes(),
_termino(termino),
_ordenada() {
}

/**
 * @brief Constructor de copia 
 * @param orig La palabra que se quiere copiar
 * @post Crear una palabra que es una copia de orig
 */
Palabra::Palabra(const Palabra& orig) :
_siguientes(orig._siguientes),
_termino(orig._termino),
_ordenada(orig._ordenada) {
}

/**
 * @brief Destructor de la clase 
 * @post Destruir un objeto 
 */
Palabra::~Palabra() {
}

/**
 * @brief Modifica el termino de palabra 
 * @param _termino El nuevo termino de palabra 
 * @post Modificar el termino de palabra
 */
void Palabra::SetTermino(std::string termino) {
    this->_termino = termino;
}

/**
 * @brief Devuelve el termino de palabra 
 * @return El termino de palabra 
 */
std::string Palabra::GetTermino() const {
    return _termino;
}

/**
 * @brief Operador ==
 * @param palabra Palabra con la que se quiere comparar
 * @return Si la palabra que se le pasa es igual a this
 */

bool Palabra::operator==(Palabra& palabra) {
    if (this->_termino == palabra._termino)
        return true;
    return false;
}

/**
 * @brief Operador menor 
 * @param palabra Palabra con la que se quiere comparar
 * @return Si la palabra que se le pasa es menor a this
 */
bool Palabra::operator<(Palabra& palabra) {
    if (this->_termino < palabra._termino)
        return true;
    return false;
}

/**
 * @brief Añade un nuevo sucesor a palabra
 * @param cadena El nuevo sucesor a añadir
 * @post Añadir un nuevo sucesor a palabra si no se encuentra o incrementarlo en caso contrario 
 */
void Palabra::nuevoSucesor(std::string& cadena) {
    if (cadena != _termino) {
        auto i = _siguientes.begin();
        bool esta = false;

        while (i != _siguientes.end() && !esta) {
            if ((*i).getTermino() == cadena) {
                (*i).incrementarOcurrencias();
                esta = true;
            }
            i++;
        }
        if (!esta) {
            Sucesor nuevo(cadena);
            _siguientes.push_back(nuevo);
        }
    }
}

/**
 * @brief Devuelve mis sucesores ordenados
 * @return Sucesores ordenados
 * @post Devolver los sucesores ordenados
 */
std::priority_queue<Sucesor> Palabra::sucesores() {
    return _ordenada;
}

/**
 * @brief Operador de asignación
 * @param orig La palabra que se quiere copiar
 * @return La palabra con la información ya copiada
 */
Palabra& Palabra::operator=(const Palabra& orig) {
    if (this->GetTermino() != orig.GetTermino()) {
        _termino = orig._termino;
        _siguientes = orig._siguientes;
    }
    return *this;
}

/**
 * @brief Operador menor igual 
 * @param p Palabra con la que se quiere realizar la comprobación
 * @return True si mi palabra es menor igual que la palabra que se me pasa, false en otro caso
 */
bool Palabra::operator<=(Palabra& p) {
    if (this->GetTermino() < p.GetTermino() || this->GetTermino() == p.GetTermino()) {
        return true;
    }
    return false;
}

/**
 * @brief Método para ordenar los sucesores de la palabra
 * @return Devuelve 1 si tiene sucesores y -1 si no tiene
 */
int Palabra::SucesoresOrdenados() {
    _ordenada = std::priority_queue<Sucesor>();
    if (!_siguientes.empty()) {
        auto it = _siguientes.begin();
        while (it != _siguientes.end()) {
            _ordenada.push((*it));
            it++;
        }
        return 1;
    } else {
        std::cout << "No tiene sucesores." << std::endl;
        return -1;
    }
}

