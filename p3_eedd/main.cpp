/* 
 * @file main.cpp
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 10 de octubre de 2017, 8:36
 * @note Práctica 3. Implementación de una lista dinámica mediante plantillas y operadores en C++
 */

#include <cstdlib>
#include "ListaEnlazada.h"
#include "Nodo.h"
#include "Diccionario.h"
#include "Iterador.h"
#include "Sucesor.h"
#include <iostream>
#include <vector>
using namespace std;

/*
 * @param argc Número de argumentos pasados por línea de orden
 * @param argv Argumentos pasados por línea de orden
 */
int main(int argc, char** argv) {

    //Cargamos el diccionario 
    std::string fichero("listado-sin-acentos_v2.txt");
    Diccionario diccionario(fichero);

    //Entrenamos el diccionario
    std::string micorpus("lista.txt");
    diccionario.usaCorpus(micorpus);

    //Variables de nuestro programa
    int opcion;
    int sucesor_elegido;
    int tiene_sucesores;
    bool sucesores;
    std::string frase = "";
    std::string palabra = "";

    while (opcion != 3) {
        /**
         * @brief Menú de opciones
         * @param 1 Introduce un frase para que se entrene el diccionario
         * @param 2 Introduce una palabra para ver si esta en el diccionario o para mostrar sus sucesores
         * @param 3 Para salir del menú
         */
        std::cout << "======================================================================================" << std::endl;
        std::cout << "||         Bienvenido a nuestro diccionario, por favor, elija una de las opciones:   ||" << std::endl;
        std::cout << "||         1. Introducir una frase para entrenar el diccionario.                     ||" << std::endl;
        std::cout << "||         2. Introducir una palabra.                                                ||" << std::endl;
        std::cout << "||         3. Para salir.                                                            ||" << std::endl;
        std::cout << "======================================================================================" << std::endl;

        std::cout << "> ";
        cin>>opcion;

        if (opcion == 1) {
            std::cout << "----------------------------------------------------------------------------" << std::endl;
            std::cout << "|                                 Opcion 1                                 |" << std::endl;
            std::cout << "----------------------------------------------------------------------------" << std::endl;
            std::cout << "> ";
            getline(cin>>ws, frase);
            diccionario.entrena(frase);
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Entrenamiento realizado con exito." << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        }

        if (opcion == 2) {
            std::cout << "----------------------------------------------------------------------------" << std::endl;
            std::cout << "|                                 Opcion 2                                 |" << std::endl;
            std::cout << "----------------------------------------------------------------------------" << std::endl;

            sucesores = true;

            std::cout << "> ";
            getline(cin>>ws, palabra);

            do { //Mientras tenga sucesores 
                auto p = diccionario.buscar(palabra); //Esta la palabra en el diccionario

                if (p != nullptr) {
                    tiene_sucesores = diccionario.mostrarSucesores(palabra);

                    if (tiene_sucesores != -1) { //Si tiene sucesores
                        std::cout << "Elija un sucesor: " << std::endl;
                        std::cin>>sucesor_elegido;

                        std::cout << std::endl;
                        int cont = 0;
                        auto it = p->sucesores().iterador();
                        while (!it.fin() && cont < sucesor_elegido) {
                            it.siguiente();
                            cont++;
                        }
                        palabra = it.dato().getTermino();
                        std::cout << palabra << std::endl;
                        sucesores = true;

                    } else //Si no tiene sucesores
                        sucesores = false;
                } else { //La palabra no esta en el diccionario
                    sucesores = false;
                    std::cout << "La palabra introducida no esta en el diccionario." << std::endl;
                }
            } while (sucesores);
        }
    }
    return 0;
}

