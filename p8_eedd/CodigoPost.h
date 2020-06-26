/* 
 * @file CodigoPost.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date 5 de diciembre de 2017, 12:18
 */

#ifndef CODIGOPOST_H
#define CODIGOPOST_H
#include <iostream>
class CodigoPost {
    std::string _zip; //<Código postal
    double _latitud; //<Latitud (y)
    double _longitud; //<Longitud (x)
    std::string _city; //<Ciudad
    std::string _state;//<Estado
    int _timezone; //<Zona horaria
    int _dst; //<Distrito
    
public:
    CodigoPost(std::string zip="", double latitud =0, double longitud = 0, std::string city="", 
            std::string state="", int timezone=0, int dst=0);
    CodigoPost(const CodigoPost& orig);
    virtual ~CodigoPost();
    int GetDst() const;
    int GetTimezone() const;
    std::string GetState() const;
    std::string GetCity() const;
    double GetLongitud() const;
    double GetLatitud() const;
    std::string GetZip() const;
   
};

#endif /* CODIGOPOST_H */

