/* 
 * @file TextoPredictivo.h
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 31 de octubre de 2017, 11:56
 * @note Práctica 5. Árboles AVL
 */

#ifndef TEXTOPREDICTIVO_H
#define TEXTOPREDICTIVO_H

#include <string>
#include "Diccionario.h"
#include <stdexcept>

/**
 * @brief Clase TextoPredictivo
 */
class TextoPredictivo {
public:
    TextoPredictivo(Diccionario& diccidioma);
    TextoPredictivo(const TextoPredictivo& orig);
    virtual ~TextoPredictivo();
    
    std::list<std::string> sugerencia(std::string& termino);
    void entrena (std::string frase);
    
private:
    Diccionario *dicBase;
};

#endif /* TEXTOPREDICTIVO_H */

