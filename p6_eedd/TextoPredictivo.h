/* 
 * @file TextoPredictivo.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 14 de noviembre de 2017, 15:40
 * @note Practica 6. Contenedores asociativos de STL
 */

#ifndef TEXTOPREDICTIVO_H
#define TEXTOPREDICTIVO_H

#include <string>
#include "Diccionario.h"
#include <stdexcept>
#include "Usuario.h"
#include <vector>
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

    void nuevoUsuario(std::string id, std::string nombre);
    Usuario* getUsuario(std::string id);
    Diccionario* getDicBase() const;

private:
    Diccionario *_dicBase;
    std::map<std::string, Usuario> _usuarios;
};

#endif /* TEXTOPREDICTIVO_H */

