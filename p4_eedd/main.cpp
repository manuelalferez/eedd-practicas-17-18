/* 
 * @file main.cpp
 * @author Gema Parra Cabrera y Manuel AlfÃ©rez Ruiz
 * @date 24 de octubre de 2017, 16:11
 * @note Práctica 4. STL de contenedores lineales
 */

#include <cstdlib>
#include "Diccionario.h"
#include "Sucesor.h"
#include <iostream>
#include <vector>

using namespace std;

/*
 * @param argc Numero de argumentos pasados por linea de orden
 * @param argv Argumentos pasados por linea de orden
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
         * @brief Menu de opciones
         * @param 1 Introduce un frase para que se entrene el diccionario
         * @param 2 Introduce una palabra para ver si esta en el diccionario o para mostrar sus sucesores
         * @param 3 Para salir del menu
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
            std::string frase = palabra;
            Palabra* p;
            do { //Mientras tenga sucesores
                 p = diccionario.busca(palabra); //Esta la palabra en el diccionario
                
                if (p != nullptr) {
                    tiene_sucesores = diccionario.tieneSucesores(palabra);

                    if (tiene_sucesores != -1) { //Si tiene sucesores

                        int cont = 0;
                        auto sucesors = p->sucesores();
                        
                        std::vector<Sucesor> aux ; //Para no perder los sucesores
                        while (!sucesors.empty() && cont < p->sucesores().size() && cont <10 ) {
                            auto it = sucesors.top();
                            aux.push_back((it));
                            sucesors.pop();
                            std::cout << cont << " . Sucesor: " << it.getTermino() << ". Numero de ocurrencias: " << it.getNumOcurrencias() << std::endl;
                            cont++;

                            if (sucesors.empty() || cont == 9 || cont ==p->sucesores().size() ) {
                                int accion = 0;

                                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                                std::cout << "Si quiere elegir sucesor pulso 1" << std::endl;
                                std::cout << "Si quiere elegir escribir una palabra a continuación pulso 2" << std::endl;
                                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                                std::cin>>accion;
                                if (accion == 1) {
                                    std::cout << "Elija un sucesor: " << std::endl;
                                    std::cin>>sucesor_elegido;
                                    
                                    palabra = aux[sucesor_elegido].getTermino();
                                    system("clear");
                                    std::cout << std::endl;
                                    frase = " " + frase + " " + palabra;
                                    std::cout << frase << " " << std::endl;
                                    break;
                                } else {
                                    std::cout << frase << " ";
                                    getline(cin>>ws, palabra);
                                    std::cout << std::endl;
                                    frase = " " + frase + " " + palabra;
                                    std::cout << frase << " ";
                                    break;
                                }
                            }

                        }

                    } else //Si no tiene sucesores
                        sucesores = false;

                } else { //La palabra no esta en el diccionario
                    sucesores = false;
                    std::cout << "La palabra introducida no esta en el diccionario." << std::endl;
                }
            } while (sucesores);
        }
    }
    system("clear");

    return 0;
}




