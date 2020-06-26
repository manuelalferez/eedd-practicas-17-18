/* 
 * @file Palabra.cpp
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 14 de octubre de 2017, 12:20
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#include "Palabra.h"
#include <vector>
/**
 * @brief Constructor por defecto parametrizado
 * @param termino El termino
 * @post Crear una palabra por defecto o parametrización
 */
Palabra::Palabra(std::string termino, int numSucesores) :
_siguientes(),
_termino(termino) {
}

/**
 * @brief Constructor de copia 
 * @param orig La palabra que se quiere copiar
 * @post Crear una palabra que es una copia de orig
 */
Palabra::Palabra(const Palabra& orig) :
_siguientes(orig._siguientes),
_termino(orig._termino) {
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
void Palabra::SetTermino(std::string _termino) {
    this->_termino = _termino;
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
        auto i = _siguientes.iterador();
        bool esta = false;

        while (!i.fin()&& !esta) {
            if (i.dato().getTermino() == cadena) {
                i.dato().incrementarOcurrencias();
                esta = true;
            }
            i.siguiente();
        }
        if (!esta) {
            Sucesor nuevo(cadena);
            _siguientes.insertaInicio(nuevo);
        }
    }
}

/**
 * @brief Devuelve la lista de sucesores 
 * @return Mi lista de sucesores llamada siguientes
 * @post Devolver la lista de sucesores de la palabra 
 */
ListaEnlazada<Sucesor>& Palabra::sucesores() {
    return _siguientes;
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
 * @brief Método para mostrar los sucesores ordenados
 * @return Devuelve 1 si tiene sucesores y -1 si no tiene
 */
int Palabra::mostrarSucesoresOrdenados() {
    std::vector<std::string> vectorSucesores;
    std::vector<int> vectorOcurrencias;
    if (!_siguientes.vacia() ) {
            auto i = _siguientes.iterador();
            int cont = 0;
            std::cout << "~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Sucesores:" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~" << std::endl;
            while (!i.fin()) {
                vectorSucesores.push_back(i.dato().getTermino());
                vectorOcurrencias.push_back(i.dato().getNumOcurrencias());
                i.siguiente();
                cont++;
            }
            for(int i = 0; i<vectorOcurrencias.size(); ++i){
                for(int j = i+1; j< vectorOcurrencias.size();++j){
                        if(vectorOcurrencias[i] < vectorOcurrencias[j]){
                            auto aux = vectorOcurrencias[j];
                            auto aux1= vectorSucesores[j];
                            vectorOcurrencias[j] = vectorOcurrencias[i];
                            vectorOcurrencias[i] = aux;
                            vectorSucesores[j] = vectorSucesores[i];
                            vectorSucesores[i]= aux1;
                            
                        }
                }
            }
            ListaEnlazada<Sucesor> ordenada;
            for ( int i = 0;i<vectorSucesores.size();++i){
                auto sucesor= Sucesor(vectorSucesores[i]);
                if(i<10){
                    std::cout << i << ". Sucesor: " << vectorSucesores[i] << "|| Ocasiones: " << vectorOcurrencias[i] << std::endl;
                }
                ordenada.insertaFin(sucesor);  
            }
            _siguientes = ordenada;
            return 1;
    } else {
        std::cout << "No tiene sucesores." << std::endl;
        return -1;
    }
}

