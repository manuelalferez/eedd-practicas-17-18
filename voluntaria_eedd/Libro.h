/* 
 * @file Libro.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 14 de diciembre de 2017, 14:15
 * @note Práctica Voluntaria
 */

#ifndef LIBRO_H
#define LIBRO_H

#define MAX_OPINIONES 3 //Máximo de opiniones 
#define MIN_PUNTOS 21 //Mínimo de puntos para publicar el Libro

class Editorial;

#include <string>

/**
 * @brief Situación del Libro
 * @param espera De ser aceptado o no por la Editorial
 * @param en_revision En proceso de revisión por los Lectores
 * @param no_publicable Si el Libro no es publicado
 * @param publicado Si el Libro es publicado
 */
enum Estado{
    espera, en_revision, no_publicable, publicado
};

/**
 * @brief Clase que almacena la información de un Libro
 */
class Libro {
public:
    
    std::string _isbn; //<ISBN del Libro
    std::string _titulo; //<Título del libro
    std::string _autor; //<Autor del libro
    Estado _estado; //<Estado del libro
    
    Libro();
    Libro(std::string isbn, std::string titulo, std::string autor, Editorial *editorial);
    Libro(const Libro& orig);
    virtual ~Libro();
    
    void opinionRecibida(int nota);
    void decisionTomada(bool se_publica);
    
    void asignarURL(std::string url);
    
private:
    float _notaAcumulada; //<Puntuación que lleva acumulada el Libro
    int _numOpiniones; //<Número de opiniones que se le realizaron al Libro
    std::string _url; //<URL a través de la cuál se puede comprar el Libro
    Editorial *_editorial; //<Asociación con Editorial
};

#endif /* LIBRO_H */