/* 
 * @file Usuario.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 21 de noviembre de 2017, 13:19
 * @note Práctica 7. Tablas Hash
 */

#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <list>
#include "Diccionario.h"
#include <map>
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
    std::string _id; //<Identificador del usuario 
    std::string _nombre; //<Nombre del usuario
    TextoPredictivo *_tp;//<Texto predictivo del usuario
    Diccionario _miDicc;//<Diccionario particular del usuario
};

#endif /* USUARIO_H */

