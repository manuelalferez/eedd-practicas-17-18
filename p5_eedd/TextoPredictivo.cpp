/* 
 * @file TextoPredictivo.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 31 de octubre de 2017, 11:56
 * @note Práctica 5. Árboles AVL
 */

#include "TextoPredictivo.h"

/**
 * @brief Constructor parametrizado
 * @param diccidioma El diccionario que se usará para el texto predictivo
 * @post Crear un texto predictivo
 */
TextoPredictivo::TextoPredictivo(Diccionario& diccidioma) : dicBase(new Diccionario(diccidioma)) {
}

/**
 * @brief Constructor de copia 
 * @param orig El texto predictivo que quiero copiar
 * @post Crea un texto predictivo que es una copia de orig
 */
TextoPredictivo::TextoPredictivo(const TextoPredictivo& orig) : dicBase(orig.dicBase) {
}

/**
 * @brief Destructor de la clase
 * @post Destruir un objeto
 */
TextoPredictivo::~TextoPredictivo() {
    delete dicBase;
}

/**
 * @brief Entrena el diccionario de texto predictivo 
 * @param frase Frase que servirá para entrenar el diccionario del texto predictivo
 * @post Entrenar el diccionario del texto predictivo
 */
void TextoPredictivo::entrena(std::string frase) {
    dicBase->entrena(frase);
}

/**
 * @brief Método que devuelve una lista con las sugerencias de un termino
 * @param termino El termino que queremos hayar sus sucesores
 * @return Una lista de string (sucesores) del termino
 * @note Si no esta la palabra en el diccionario del texto predictivo o dicha palabra no tiene sucesores devuelve una lista de string vacia
 */
std::list<std::string> TextoPredictivo::sugerencia(std::string& termino) {
    Palabra* esta =0;
    esta= dicBase->busca(termino);
    std::list<std::string> lista;
    if (esta) {
        if (esta->tieneSucesores()) {
            //Declaraciones
            std::priority_queue<Sucesor> listaOrdenada = esta->sucesores();

            int cont = 0;
            while (cont < 10 && !listaOrdenada.empty()) {
                lista.push_back(listaOrdenada.top().getTermino());
                listaOrdenada.pop();
                cont++;
            }
            
        } 
    } else {
        Palabra p(termino);
        dicBase->insertar(p); //Si la palabra no esta, la introduzco  
    }

    return lista; //Tanto si la palabra no tiene sucesores, como si si tiene y como si no estaba en el diccionario 
}
