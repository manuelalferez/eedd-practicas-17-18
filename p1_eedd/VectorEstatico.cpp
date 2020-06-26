/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "VectorEstatico.h"
#include <algorithm>
/**
 * @brief Constructor por defecto parametrizado
 * @param tama
 */
VectorEstatico::VectorEstatico(int tama) {
    _tama = tama;
    _v = new Palabra[80383];
    for( int i=0; i < tama; i++){
        _v[i] = Palabra("");
    }
}

/**
 * @brief Constructor copia
 * @param orig
 */
VectorEstatico::VectorEstatico(const VectorEstatico& orig) {
    _v = new Palabra[orig._tama];
    _tama = orig._tama;
    for (int i = 0; i < _tama; i++) 
        _v[i] = orig._v[i];
}

/**
 * @brief Método para buscar un dato en el vector
 * @param dato
 * @return devuelve la posicion
 */
int VectorEstatico::buscar(Palabra& dato) {
    int inf = 0;
    int sup = _tama - 1;
    int curIn=0;
    bool encontrado = false;
    while(encontrado == false){
        curIn = (inf+sup)/2;
        if(_v[curIn] == dato){
            encontrado = true;
            return curIn;
        }else if(inf > sup) {
            return -1;
        }else {
            if(_v[curIn] < dato ) inf = curIn + 1;
            else sup = curIn -1;
        }
    }
}
/**
 * @brief Metodo para insertar una palabra en una posicion del vector
 * @param palabra Palabra a insertar
 * @param pos Posicion en la que insertar
 */
void VectorEstatico::insertar(Palabra& palabra, long int pos){
    if( pos >= 0 && pos < _tama){
        _v[pos] = palabra;
    }else {
       throw std::out_of_range("Fuera de rango insertando");
    }
}
/**
 * @brief Método para leer el contenido de una posicion del vector
 * @param pos
 * @return Devuelve la palabra que se encuentra ahí
 */
Palabra VectorEstatico::leer(int pos){
    if(pos < _tama && pos > 0){
     return _v[pos];
    }else{
       throw std::out_of_range("Fuera de rango leyendo");
    }
}

/**
 * @brief Método para consultar el tamaño del vector
 * @return Devuelve el tamaño
 */
int VectorEstatico::getTama() const {
    return _tama;
}

/**
 * @brief Destructor
 */
VectorEstatico::~VectorEstatico() { 
        delete [] _v;
    
}

/**
 * @brief Método de ordenación del vector
 */
void VectorEstatico::ordenar() {
    sort(_v, _v+ _tama);
}
