/* 
 * @file main.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 31 de octubre de 2017, 11:56
 * @note Practica 5. Árboles AVL
 */

#include <cstdlib>
#include <chrono>
#include "Diccionario.h"
#include "AVL.h"
#include "TextoPredictivo.h"

using namespace std;

/*
 * @param argc Numero de argumentos pasados por linea de orden
 * @param argv Argumentos pasados por linea de orden
 */
int main(int argc, char** argv) {

    std::cout << "======================================================================================" << std::endl;
    std::cout << "||             Programa de prueba 1: Comprobación de la estructura de datos         ||" << std::endl;
    std::cout << "======================================================================================" << std::endl;

    auto start = std::chrono::system_clock::now();

    int num = 5;
    int num1 = 2;
    int num2 = 8;
    int num3 = 7;
    int num4 = 6;
    int num5 = 9;

    AVL<int> miAVL;
    miAVL.inserta(num);
    miAVL.inserta(num1);
    miAVL.inserta(num2);
    miAVL.inserta(num3);
    miAVL.inserta(num4);
    miAVL.inserta(num5);

    AVL<int> copia(miAVL);

    std::cout << "~~~~~~~~~~~~~~~MUESTRO miAVL~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Numero de elementos: " << miAVL.numElementos() << std::endl;
    cout << "La altura de mi AVL es: " << miAVL.altura() << std::endl;
    miAVL.recorreInorden();

    std::cout << "~~~~~~~~~~~~~~~MUESTRO copia de miAVL~~~~~~~" << std::endl;
    std::cout << "Copia exitosa." << std::endl;
    std::cout << "Numero de elementos: " << copia.numElementos() << std::endl;
    std::cout << "La altura de mi AVL es: " << copia.altura() << std::endl;
    copia.recorreInorden();


    auto end = std::chrono::system_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Tiempo gastado (ms): " << elapsed_ms << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    std::cout << "======================================================================================" << std::endl;
    std::cout << "||             Programa de prueba 2: Mostrar los términos más habituales             ||" << std::endl;
    std::cout << "======================================================================================" << std::endl;

    //Cargamos el diccionario
    auto start2 = std::chrono::system_clock::now();
    std::string fichero("listado-sin-acentos_v2.txt");
    Diccionario diccionario(fichero);
    std::cout << "Cargado: " << diccionario.numPalabras() << " palabras." << std::endl;

    //Entrenamos el diccionario
    std::string micorpus("corpus_spanish.txt");
    diccionario.usaCorpus(micorpus);
    std::cout << "Entrenado: " << diccionario.numPalabras() << " palabras." << std::endl;

    auto end2 = std::chrono::system_clock::now();
    auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Tiempo gastado (ms): " << elapsed_ms2 << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    TextoPredictivo texto_inteligente(diccionario);

    int opcion;
    int sucesor_elegido;
    bool sucesores;
    std::string frase = "";
    std::string palabra = "";
    std::string opcion_menu2 = "";

    while (opcion != 4) {
        /**
         * @brief Menu de opciones
         * @param 1 Introduce un frase para que se entrene el diccionario
         * @param 2 Introduce una palabra para ver si esta en el diccionario o para mostrar sus sucesores
         * @param 3 Para salir del menu
         */
        std::cout << "======================================================================================" << std::endl;
        std::cout << "||         Bienvenido a nuestro diccionario, por favor, elija una de las opciones:   ||" << std::endl;
        std::cout << "||         [1]. Introducir una frase para entrenar el diccionario.                   ||" << std::endl;
        std::cout << "||         [2]. Introducir una palabra.                                              ||" << std::endl;
        std::cout << "||         [v]. Volver al menú.                                                      ||" << std::endl;
        std::cout << "||         [4]. Para salir.                                                          ||" << std::endl;
        std::cout << "======================================================================================" << std::endl;

        std::cout << "> ";
        cin>>opcion;

        if (opcion == 1) {
            std::cout << "----------------------------------------------------------------------------" << std::endl;
            std::cout << "|                                 Opcion 1                                 |" << std::endl;
            std::cout << "----------------------------------------------------------------------------" << std::endl;
            std::cout << "> ";
            getline(cin>>ws, frase);
            texto_inteligente.entrena(frase);
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
            do { //Mientras tenga sucesores
                auto lista_con_sucesores_ordenados = texto_inteligente.sugerencia(palabra);
                auto ite = lista_con_sucesores_ordenados.begin();
                opcion_menu2 = "";

                if (!lista_con_sucesores_ordenados.empty()) {//Si la palabra tiene sucesores entra 
                    int cont = 0;
                    while (ite != lista_con_sucesores_ordenados.end()) {
                        std::cout << cont << " . Sucesor: " << *ite << std::endl;
                        cont++;
                        ite++;
                    }
                } else {
                    std::cout << "La palabra introducida no tiene sucesores o no estaba en el diccionario." << std::endl;
                }
                int accion = 0;
                std::cout << "> ";
                getline(cin>>ws, palabra);

                opcion_menu2 = palabra;
                if (!lista_con_sucesores_ordenados.empty()) {
                    if (isdigit(palabra[0])) {
                        sucesor_elegido = std::stoi(palabra.c_str());
                        accion = 1;
                    }
                }
                if (accion == 1) { //Se eligio una opcion entre los sucesores
                    ite = lista_con_sucesores_ordenados.begin();
                    int micontador = 0;
                    while (micontador < sucesor_elegido) {
                        ite++;
                        micontador++;
                    }
                    palabra = *ite;
                    system("clear");
                    std::cout << std::endl;
                    frase = " " + frase + " " + palabra;
                    std::cout << frase << " " << std::endl;
                } else { //Se introdujo una palabra      
                    system("clear");

                    frase = " " + frase + " " + palabra;

                    if (opcion_menu2 != "v") texto_inteligente.entrena(frase); //Entrenamos nuestro texto predictivo (su diccionario)

                    std::cout << frase << " ";
                    std::cout << std::endl;
                }
            } while (opcion_menu2 != "v");
        }
        system("clear");
    }
    return 0;
}


