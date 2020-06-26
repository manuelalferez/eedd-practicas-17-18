/* 
 * @file TextoPredictivo.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 21 de noviembre de 2017, 13:19
 * @note Práctica 7. Tablas Hash
 */

#ifndef TEXTOPREDICTIVO_H
#define TEXTOPREDICTIVO_H

#include <string>
#include "Diccionario.h"
#include <stdexcept>
#include "Usuario.h"
#include <vector>
#include <map>
/**
 * @brief Clase TextoPredictivo
 */
class TextoPredictivo {
public:
    TextoPredictivo(Diccionario& dicBase);
    TextoPredictivo(const TextoPredictivo& orig);
    virtual ~TextoPredictivo();

    std::list<std::string> sugerencia(std::string& termino);
    bool entrena(std::string termino1, std::string termino2);
    void entrena(std::string frase);

    void nuevoUsuario(std::string id, std::string nombre);
    Usuario* getUsuario(std::string id);
    Diccionario* getDicBase() const;

private:
    Diccionario *_dicBase; //< Diccionario base del texto predictivo
    std::map<std::string, Usuario> _usuarios; //<Mapa con los usuarios
};

#endif /* TEXTOPREDICTIVO_H */



