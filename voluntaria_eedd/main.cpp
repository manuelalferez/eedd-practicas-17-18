/* 
 * @file main.cpp
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 14 de diciembre de 2017, 14:15
 * @note Práctica Voluntaria
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Editorial.h"
#include "LectorColaborador.h"
#include "Libro.h"

/**
 * @brief Lee un fichero en formato CSV sobre información de Libros
 * @param nombre_fichero Nombre del fichero a leer
 * @param editorial Editorial a la cuál asignar los Libros leídos
 * @post Leer un fichero en formato CSV sobre información de Libros y asignárselos a una Editorial
 */
void fromCSVLibros(std::string& nombre_fichero, Editorial& editorial) {
    std::ifstream fe;
    std::stringstream ss;
    std::string linea;
    int librosLeidos = 0;
    std::string titulo, autor, ISBN;

    fe.open(nombre_fichero);
    if (fe.good()) {
        getline(fe, linea);
        while (!fe.eof() && librosLeidos < 500) {
            getline(fe, linea);
            if (linea != "") {
                ss.str(linea);

                getline(ss, ISBN, ';');
                getline(ss, titulo, ';');
                getline(ss, autor, ';');

                editorial.nuevoLibro(ISBN, titulo, autor);

                librosLeidos++;
            }
        }
        fe.close();
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

/**
 * @brief Lee un fichero en formato CSV sobre información de LectorColaborador
 * @param nombre_fichero Nombre del fichero a leer
 * @param editorial Editorial a la cuál asignar los Lectores
 * @post Leer un fichero en formato CSV sobre información de LectorColaborador y asignarselos a una Editorial 
 */
void fromCSVLectores(std::string& nombre_fichero, Editorial& editorial) {
    std::ifstream fe;
    std::stringstream ss;
    std::string linea;
    int maxLibros;
    std::string alias;

    fe.open(nombre_fichero);
    if (fe.good()) {
        while (!fe.eof()) {
            getline(fe, linea);
            if (linea != "") {
                ss.clear();
                ss.str(linea);

                getline(ss, alias, ';');
                ss>>maxLibros;

                editorial.nuevoLector(alias, maxLibros);
            }
        }
        fe.close();
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

/*
 * @param argc Número de argumentos pasados por línea de orden
 * @param argv Argumentos pasados por línea de orden
 */
int main(int argc, char** argv) {

    std::cout << "====================================================" << std::endl;
    std::cout << "||             Programa de prueba                 ||" << std::endl;
    std::cout << "====================================================" << std::endl;

    //Elegir uno de los 500 libros y presentarlo al sistema como nuevoLibro() (marcar para
    //no repetir).Añadir un pequeño retardo al hacer esta operación si se ve necesario.

    Editorial editorial_Planeta;
    editorial_Planeta.nuevoLibro("446523992", "A Call to Conscience : The Landmark Speeches of Dr. Martin Luther King, Jr.", "Kris Shepard");

    //Un 20% de los libros subidos será rechazado de forma aleatoria por el editor
    //aceptarRevision(): false
    //Del 80% restante, aceptarlo para revisión (aceptarRevision(): true) se busca a tres
    //lectores de forma aleatoria pero balanceando correctamente su carga de trabajo.
    // En algún momento, la carga del sistema debe colapsar de tal forma que queden
    //colas de espera para adjudicar libros a los lectores ya que éstos están todos con el
    //máximo de​carga asignada

    std::string ficheroLibros("BX-Books.csv");
    std::string ficheroLectores("lectores.csv");

    fromCSVLibros(ficheroLibros, editorial_Planeta);
    fromCSVLectores(ficheroLectores, editorial_Planeta);

    int numLibrosEnEspera = editorial_Planeta.numLibrosEnEspera();
    int numAleatorio;

    for (int i = 0; i < numLibrosEnEspera; i++) {
        numAleatorio = rand() % 15;
        if (numAleatorio <= 1) {//El 20% se rechaza (se saca de la cola)
            editorial_Planeta.getSiguienteLibro();
        } else { //El 80% se acepta la revisión
            Libro l(editorial_Planeta.getSiguienteLibro());
            editorial_Planeta.aceptarRevision(l);
        }
    }

    // El estado del sistema debe mostrarse en pantalla de algún modo: los lectores con su
    //carga​de trabajo en cola,así como la cola de espera del sistema.
    std::cout << "- Número de Libros en espera: " << editorial_Planeta.numLibrosEnEspera() << "." << std::endl;
    std::cout << "- Número de Libros en revisión: " << editorial_Planeta.numLibrosEnRevision() << "." << std::endl;
    std::cout << "- La carga de los Lectores es: " << std::endl;
    editorial_Planeta.muestraCargaLectores();

    //Elegir un lector de los 10/20 y decir que ha terminado de leer un libro con una nota
    //entre​0 y 10.
    int numLibrosPuntuar= editorial_Planeta.numLibrosEnRevision();
    for (int i = 0; i < numLibrosPuntuar; i++) {
        editorial_Planeta.valorarAleatoriamente();
        i++;
    }
    //Esto provoca que haya libros que sí se publiquen (siPublicar()) y otros que no
    //(noPublicar()). Deben aparecer en consecuencia listas de libros publicados y colas
    //de espera que se ajustarán automáticamente como consecuencia de realizar esta
    //lectura.
    std::cout<<"- Listado de libros publicados: "<<std::endl;
    editorial_Planeta.muestraLibrosPublicados();
    
    std::cout<<"- Listado de libros no publicados: "<<std::endl;
    editorial_Planeta.muestraLibrosNoPublicados();
    
    return 0;
}