/* 
 * @file CodigoPost.h
 * @author Gema Parra Cabrera y Manuel Alférez Ruiz
 * @date on 5 de diciembre de 2017, 12:18
 */

#include "CodigoPost.h"

CodigoPost::CodigoPost(std::string zip, double latitud, double longitud, std::string city,
        std::string state, int timezone, int dst): _zip(zip), _latitud(latitud), _longitud(longitud),
        _state(state), _timezone(timezone), _dst(dst), _city(city){
    
}

CodigoPost::CodigoPost(const CodigoPost& orig): _zip(orig._zip), _latitud(orig._latitud), _longitud(orig._longitud),
        _state(orig._state),
        _timezone(orig._timezone), 
        _dst(orig._dst), 
        _city(orig._city)  {
}

CodigoPost::~CodigoPost() {
}

int CodigoPost::GetDst() const {
    return _dst;
}

int CodigoPost::GetTimezone() const {
    return _timezone;
}

std::string CodigoPost::GetState() const {
    return _state;
}

std::string CodigoPost::GetCity() const {
    return _city;
}

double CodigoPost::GetLongitud() const {
    return _longitud;
}

double CodigoPost::GetLatitud() const {
    return _latitud;
}

std::string CodigoPost::GetZip() const {
    return _zip;
}

