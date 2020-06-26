/* 
 * @file main.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 14 de noviembre de 2017, 15:40
 * @note Practica 6. Contenedores asociativos de STL
 */

#include <cstdlib>
#include "Diccionario.h"
#include "TextoPredictivo.h"

using namespace std;

/*
 * @param argc Numero de argumentos pasados por linea de orden
 * @param argv Argumentos pasados por linea de orden
 */
int main(int argc, char** argv) {
    std::string us1("us1");
    std::string us2("us2");
    std::string nom1("Jose Perez");
    std::string nom2("Lola Gutierrez");
    std::string yo("yo");
    std::string el("de");


    std::string dicc("diccionario.txt");
    Diccionario dic(dicc);
    TextoPredictivo tp(dic);
    tp.nuevoUsuario(us1, nom1);
    tp.nuevoUsuario(us2, nom2);
    Usuario *usu1 = tp.getUsuario(us1);
    std::string frase("Hola colega como andas yo regu porque yo estoy pillao con las practicas de estructuras");
    usu1->escribeFrase(frase);

    std::ifstream fe;
    std::string linea;

    fe.open("ficheroUsuario1.txt");
    if (fe.good()) {
        while (!fe.eof()) {
            getline(fe, linea);
            if (linea != "") {
                usu1->escribeFrase(linea);
            }
        }
        fe.close();
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }


    list<std::string> lus1 = usu1->sugerencia(yo);

    std::cout << ">yo..." << std::endl;

    auto it = lus1.begin();
    while (it != lus1.end()) {
        std::cout << "- " << *it << std::endl;
        it++;
    }

    Usuario *usu2 = tp.getUsuario(us2);
    frase = "el whatsapp el colega el tuit el pillao";
    usu2->escribeFrase(frase);

    fe.open("ficheroUsuario2.txt");
    if (fe.good()) {
        while (!fe.eof()) {
            getline(fe, linea);
            if (linea != "") {
                usu1->escribeFrase(linea);
            }
        }
        fe.close();
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
    list<std::string> lus2 = usu2->sugerencia(el);

    std::cout << ">el..." << std::endl;

    auto it2 = lus2.begin();
    while (it2 != lus2.end()) {
        std::cout << "- " << *it2 << std::endl;
        it2++;
    }

    return 0;
}

