/* 
 * @file main.cpp
 * @author Gema Parra Cabrera y Manuel Alferez Ruiz
 * @date 21 de noviembre de 2017, 13:19
 * @note Práctica 7. Tablas Hash
 */

#include <cstdlib>
#include <chrono>
#include "Diccionario.h"
#include "TextoPredictivo.h"

using namespace std;

/*
 * @param argc Numero de argumentos pasados por linea de orden
 * @param argv Argumentos pasados por linea de orden
 */
int main(int argc, char** argv) {

    std::cout << "======================================================================================" << std::endl;
    std::cout << "||             Programa de prueba 1: Ajustar el tamanio de la tabla                 ||" << std::endl;
    std::cout << "======================================================================================" << std::endl;

    std::string fich = "diccionario.txt";
    Diccionario dicc(fich);
    //    
    //    std::string primos="primes.txt";
    //    std::ifstream fe;
    //    std::string linea;
    //    
    //    std::vector<int> v;
    //    
    //    fe.open(primos);
    //    if (fe.good()) {
    //        while (!fe.eof()) {
    //            getline(fe, linea);
    //            if (linea != "") {
    //                auto n=std::stoi(linea);
    //                v.push_back(n);
    //            }
    //        }
    //        fe.close();
    //    } else {
    //        std::cerr << "No se puede abrir el fichero" << std::endl;
    //    }
    //   
    //    int min=50;
    //    int pri;
    //    for (int i=0;i<v.size();i++){
    //
    //        Diccionario dicc(fich,167777,v[i]);
    //        if(dicc.getPalabras()->maxColisiones()<min)  {
    //            min=dicc.getPalabras()->maxColisiones();
    //            pri=v[i];
    //            std::cout<<endl;
    //            std::cout<<"Primo: "<<pri<<std::endl;
    //            std::cout<<"Maximo de colisiones: "<<min<<std::endl;
    //        }
    //        }
    //                
    //        
    //    std::cout<<"Primo: "<<pri<<std::endl;
    //    std::cout<<"Maximo de colisiones: "<<min<<std::endl;
    std::cout << "Factor de carga: " << dicc.getPalabras()->factorCarga() << std::endl;
    std::cout << "Elementos en la tabla: " << dicc.numPalabras() << std::endl;
    std::cout << "El tamanio de la tabla es: " << dicc.getPalabras()->tamaTabla() << std::endl;
    std::cout << "Maximo de colisiones: " << dicc.getPalabras()->maxColisiones() << std::endl;

    std::cout << "======================================================================================" << std::endl;
    std::cout << "||             Programa de prueba 2: Entrenamiento y medición de tiempos             ||" << std::endl;
    std::cout << "======================================================================================" << std::endl;

    //Cargamos el diccionario
    auto start2 = std::chrono::system_clock::now();
    std::string fichero("diccionario.txt");
    Diccionario diccionario(fichero, 158519, 13477);
    std::cout << "Cargado: " << diccionario.numPalabras() << " palabras." << std::endl;

    //Entrenamos el diccionario
    std::string micorpus("corpus_spanish.txt");
    diccionario.usaCorpus(micorpus);
    std::cout << "Entrenado: " << diccionario.numPalabras() << " palabras." << std::endl;

    auto end2 = std::chrono::system_clock::now();
    auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

    std::cout << "Factor de carga: " << diccionario.getPalabras()->factorCarga() << std::endl;
    std::cout << "El tamanio de la tabla es: " << diccionario.getPalabras()->tamaTabla() << std::endl;
    std::cout << "Maximo de colisiones: " << diccionario.getPalabras()->maxColisiones() << std::endl;

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Tiempo gastado (ms): " << elapsed_ms2 << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Tiempo gastado en AVL (ms): 9425"<< std::endl;
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

