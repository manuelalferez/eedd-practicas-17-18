/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Gema
 *
 * Created on 25 de septiembre de 2017, 21:37
 */

#include <cstdlib>
#include "Diccionario.h"
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    std::string ruta = "listado-sin-acentos.txt";
    Diccionario diccionario(ruta);

    std::string palabra;
    int total = 0;
    std::cout << "Introducir frases y pulser enter (Ctrl+D para finalizar)" << std::endl;

    while (!std::cin.eof()) {
        try {
            std::cin >> palabra;
            if (palabra != "") {
                if (diccionario.buscar(palabra) == -1) {
                    std::cout << ++total << " " << palabra << std::endl;
                    diccionario.insertar(palabra);
                    std::cout << "Palabra insertada "<<std::endl;
                }
                palabra = "";
            }

        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    std::cout << "Total palabras: " << total << std::endl;

    std::cout << diccionario.tama();
    
    return 0;
}

