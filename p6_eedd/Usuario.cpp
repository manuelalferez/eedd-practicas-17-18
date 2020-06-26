/* 
 * @file Usuario.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 14 de noviembre de 2017, 15:40
 * @note Practica 6. Contenedores asociativos de STL
 */

#include "Usuario.h"
#include "TextoPredictivo.h"

/**
 * @brief Constructor por defecto parametrizado
 * @param id El id del usuario
 * @param nombre El nombre del usuario
 * @param tp El texto predictivo del usuario
 * @post Crea un usuario por defecto o por parametrizacion
 */
Usuario::Usuario(std::string id, std::string nombre, TextoPredictivo *tp) :
_id(id), _nombre(nombre), _tp(tp), _miDicc(Diccionario()) {
}

/**
 * @brief Constructor de copia
 * @param orig El usuario que se quiere copiar
 * @post Crea un usuario que es una copia de orig
 */
Usuario::Usuario(const Usuario& orig) :
_id(orig._id), _nombre(orig._nombre), _tp(orig._tp), _miDicc(orig._miDicc) {
}

/**
 * @brief Destructor de la clase
 * @post Destruye un objeto
 */
Usuario::~Usuario() {
}

/**
 * @brief Entrenar dicBase y miDicc con una frase
 * @param frase Frase con la que se quiere realizar el entrenamiento
 * @note1 Descompone la frase en parejas de dos terminos, se le pasa a entrena de TextoPredictivo. Si ambos terminos estan en dicBase 
 * @note1 entonces TextoPredictivo::entrena() devuelve true (hubo exito) y se añade termino 2 como sucesor
 * @note2 Si no se tuvo exito, entonces se añade la palabra junto con el sucesor al miDicc mediante miDicc::inserta()
 * @post Entrenar dicBase y miDicc
 */
void Usuario::escribeFrase(std::string& frase) {
    std::string termino1, termino2, intermedia;
    std::stringstream ss;
    bool exito;
    ss << frase;

    ss>>termino1;

    while (!ss.eof()) {
        ss >> intermedia;
        if (intermedia != "") {
            termino2 = intermedia;
            exito = _tp->entrena(termino1, termino2);
            if (!exito) { //Si no se tuvo exito, insertamos la palabra en _miDicc
                auto esta = _miDicc.busca(termino1);
                if (esta) esta->nuevoSucesor(termino2);
                else {
                    Palabra p(termino1);
                    p.nuevoSucesor(termino2);
                    _miDicc.inserta(p);
                }
            }
            intermedia = "";
            termino1 = termino2;
        }
    }
    Palabra* esta = _tp->getDicBase()->busca(termino1); //Busco el ultimo termino de la frase en el dicBase
    if (!esta) {
        Palabra p(termino1);
        _miDicc.inserta(p);
    }
}

std::string Usuario::getId() const {
    return _id;
}

/**
 * @brief Método que devuelve una lista con las sugerencias de un termino
 * @param termino El termino que queremos hayar sus sucesores
 * @return Una lista de string (sucesores) del termino
 * @note1 Si no esta la palabra en el diccionario del texto predictivo o dicha palabra no tiene sucesores devuelve una lista de string vacia
 * @note2 Si no existe el termino en ambos diccionario se inserta en miDicc
 * @note3 Si el termino existe en un solo diccionario entonces se devuelven sus sucesores (hasta 10)
 * @note4 Si el termino existe en ambos diccionarios entonces se devuelve (hasta 5) sucesores de miDicc y a continuacion
 * @note4 sucesores de dicBase
 */
std::list<std::string> Usuario::sugerencia(std::string termino) {
    std::list<std::string> lista;
    Palabra p(termino);
    auto sugerencias_dicBase = _tp->sugerencia(termino);
    std::list<std::string> sugerencias_miDicc;

    //Calculamos la lista de sucesores de termino en miDicc
    Palabra* esta = 0;
    esta = _miDicc.busca(termino);
    if (esta) {
        if (esta->tieneSucesores()) {
            //Declaraciones
            std::priority_queue<Sucesor> listaOrdenada = esta->sucesores();

            int cont = 0;
            while (cont < 10 && !listaOrdenada.empty()) {
                sugerencias_miDicc.push_back(listaOrdenada.top().getTermino());
                listaOrdenada.pop();
                cont++;
            }
        }
    }

    if (sugerencias_dicBase.empty() && sugerencias_miDicc.empty()) {//Si no existe el termino en ambos diccionarios, se inserta en miDicc
        Palabra p(termino);
        _miDicc.inserta(p);
        return lista;
    } else {
        if (sugerencias_dicBase.empty()&&!sugerencias_miDicc.empty()) {//Si no hay sugerencias en dicBase y si en miDicc 
            return sugerencias_miDicc;
        } else {
            if (!sugerencias_dicBase.empty() && sugerencias_miDicc.empty()) {//Si hay sugerencias en dicBase y no en miDicc 
                return sugerencias_dicBase;
            } else {//Hay sugerencias en dicBase y en miDicc
                auto iterador_dicBase = sugerencias_dicBase.begin();
                auto iterador_miDicc = sugerencias_miDicc.begin();
                int contador = 0;
                while (contador < 5 && (iterador_miDicc != sugerencias_miDicc.end())) {//Meto en la lista los sucesores mas prioritarios de miDicc
                    lista.push_back(*iterador_miDicc);
                    iterador_miDicc++;
                    contador++;
                }
                contador = 0;
                while (contador < 5 && (iterador_dicBase != sugerencias_dicBase.end())) {//Meto en la lista los sucesores mas prioritarios de dicBase
                    lista.push_back(*iterador_dicBase);
                    iterador_dicBase++;
                    contador++;
                }
                return lista;
            }
        }
    }

}


