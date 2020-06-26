/* 
 * @file Editorial.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 14 de diciembre de 2017, 14:15
 * @note Práctica Voluntaria
 */

#ifndef EDITORIAL_H
#define EDITORIAL_H

#include "Libro.h"
#include "LectorColaborador.h"

#include <vector>
#include <map>
#include <list>
#include <iostream> //QUITAR

/**
 * @brief Clase Editorial
 */
class Editorial {
public:
    Editorial();
    Editorial(const Editorial& orig);
    virtual ~Editorial();
    
    void nuevoLibro(std::string isbn, std::string titulo, std::string autor);
    Libro getSiguienteLibro();
    bool aceptarRevision(Libro& l);
    void noPublicarLibro(Libro* l);
    void siPublicarLibro(Libro* l);
    void adjudicarLibro3Lectores(Libro& l);
    
    void nuevoLector(std::string alias, int maxLibros);
    int numLibrosEnEspera();
    int numLibrosEnRevision();
    void muestraCargaLectores();
    void valorarAleatoriamente();
    void muestraLibrosPublicados();
    void muestraLibrosNoPublicados();
    
private:
    std::queue<Libro,std::list<Libro> > _libros; //<Cola de Libros en espera de ser ojeados
    std::vector<LectorColaborador> _colaboradores; //<Colaboradores de la Editorial
    
    std::map<std::string,Libro> _librosPublicados; //<Libros publicados
    std::map<std::string,Libro> _librosNoPublicados; //<Libros del histórico sin publicar
    std::list<Libro> _librosEnRevision; //<Libros en proceso de revisión
    
    std::string generaURL();
};

#endif /* EDITORIAL_H */