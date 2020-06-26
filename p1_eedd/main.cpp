/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Gema
 *
 * Created on 18 de septiembre de 2017, 20:13
 */

#include <cstdlib>
#include "VectorEstatico.h"
#include "Palabra.h"
#include "Diccionario.h"

#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Diccionario d("listado-general.txt");
    bool continuar = true;
    int num = 0;
    while (continuar) {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "// Bienvenido al diccionario online:       //" << std::endl;
        std::cout << "// -Si quiere buscar una palabra pulse 1   // " << std::endl;
        std::cout << "// -Si quiere insertar una palabra pulse 2 //" << std::endl;
        std::cout << "// -Si quiere leer una palabra pulse 3     //" << std::endl;
        std::cout << "// -Si quiere salir pulse 4                //" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cin >> num;
        if (num == 1) {
            try {
                std::string termino;
                std::cout << "Introduzca el termino: " << std::endl;
                std::cin >> termino;
                int i = d.buscar(termino);
                if (i == -1) {
                    std::cout << "No esta la palabra" << std::endl;
                } else {
                    std::cout << "La posicion es : " << i << std::endl;
                }
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (num == 2) {
            try {
                std::string termino;
                std::cout << "Introduzca el termino: " << std::endl;
                std::cin >> termino;
                int pos;
                std::cout << "Introduzca la posición: " << std::endl;
                std::cin >> pos;
                d.insertar(termino, pos);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (num == 3) {
            try {
                int pos;
                std::cout << "Introduzca la posición: " << std::endl;
                std::cin >> pos;
                std::cout << d.leer(pos) << std::endl;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (num == 4) {
            continuar = false;
        } else {
            std::cout << "No ha introducido una opción válida" << std::endl;
        }
    }
    return 0;
}

