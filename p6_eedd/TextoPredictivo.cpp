/* 
 * @file TextoPredictivo.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 14 de noviembre de 2017, 15:40
 * @note Practica 6. Contenedores asociativos de STL
 */


#include "TextoPredictivo.h"

/**
 * @brief Constructor parametrizado
 * @param dicBase El diccionario que se usará para el texto predictivo
 * @post Crear un texto predictivo
 */
TextoPredictivo::TextoPredictivo(Diccionario& dicBase) : _dicBase(&dicBase), _usuarios() {
}

/**
 * @brief Constructor de copia 
 * @param orig El texto predictivo que quiero copiar
 * @post Crea un texto predictivo que es una copia de orig
 */
TextoPredictivo::TextoPredictivo(const TextoPredictivo& orig) : _dicBase(orig._dicBase), _usuarios(orig._usuarios){
}

/**
 * @brief Destructor de la clase
 * @post Destruir un objeto
 */
TextoPredictivo::~TextoPredictivo() {
}

/**
 * @brief Entrena el diccionario del texto predictivo
 * @param termino1 Primer termino
 * @param termino2 El segundo termino (el que le sigue a termino1)o 
 * @return Si ambos terminos estan en el diccionario se inserta termino2 como sucesor de la palabra con el termino1 
 * @        y se devuelve true, sino no se hace nada y se devuelve false
 */
bool TextoPredictivo::entrena(std::string termino1, std::string termino2) {
    auto esta_termino1= _dicBase->busca(termino1);
    if (esta_termino1){
        auto esta_termino2= _dicBase->busca(termino2);
        if (esta_termino2){
            esta_termino1->nuevoSucesor(termino2);
            return true;
        }
    }
    return false;
}

/**
 * @brief Método que devuelve una lista con las sugerencias de un termino
 * @param termino El termino que queremos hayar sus sucesores
 * @return Una lista de string (sucesores) del termino
 * @note Si no esta la palabra en el diccionario del texto predictivo o dicha palabra no tiene sucesores devuelve una lista de string vacia
 */
std::list<std::string> TextoPredictivo::sugerencia(std::string& termino) {
    Palabra* esta = 0;
    esta = _dicBase->busca(termino);
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
    }
    return lista;
}

/**
 * @brief Devolver un usuario
 * @param id El identificador del usuario
 * @return Devuelve un puntero al Usuario con el id si se encontro y NULL si no se encontró
 */
Usuario* TextoPredictivo::getUsuario(std::string id) {
    auto i= _usuarios.find(id);
    if (i!=_usuarios.end()) return &(i->second);
    return nullptr;
}

/**
 * @brief Devuelve el dicBase
 * @return Devolver el dicBase
 */
Diccionario* TextoPredictivo::getDicBase() const {
    return _dicBase;
}

/**
 * @brief Añade un nuevo usuario al texto predictivo
 * @param id El identificador del usuario
 * @param nombre El nombre del usuario
 * @post Añadir un nuevo usuario al texto predictivo, pero si ese usuario ya estaba no se añade
 */
void TextoPredictivo::nuevoUsuario(std::string id, std::string nombre) {
    Usuario nuevo_usuario(id, nombre, this);
    _usuarios.insert(std::pair<std::string, Usuario>(id, nuevo_usuario));
}
