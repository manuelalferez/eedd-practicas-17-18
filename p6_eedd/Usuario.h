/* 
 * @file Usuario.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 14 de noviembre de 2017, 15:40
 * @note Practica 6. Contenedores asociativos de STL
 */

#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <list>
#include "Diccionario.h"
class TextoPredictivo; 

/**
 * @brief Clase que almacena la informacion de un usuario
 */
class Usuario {
public:
    Usuario(std::string id, std::string nombre, TextoPredictivo *tp);
    Usuario(const Usuario& orig);
    virtual ~Usuario();
    
    std::list<std::string> sugerencia(std::string termino);
    void escribeFrase(std::string& frase);
    std::string getId() const;
    
private:
    std::string _id;
    std::string _nombre;
    TextoPredictivo *_tp;
    Diccionario _miDicc;
};

#endif /* USUARIO_H */

