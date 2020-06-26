
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include "img.h"
#include "MallaRegular.h"
#include "CodigoPost.h"

#include <math.h>

using namespace std;

int main(int argc, const char * argv[]) {

    int opcion;
    do {
        std::cout << " Elige una opcion " << std::endl;
        std::cout << "1. Programa 1 " << std::endl;
        std::cout << "2. Programa 2 " << std::endl;
        std::cin >> opcion;
    } while (opcion != 1 && opcion != 2);
    if (opcion == 1) {

        //Primer programa de prueba: 
        MallaRegular<CodigoPost> mr(0, -180, 360, 180, 530);

        Img img(1, 1);

        try {
            img = Img("./mapaUsa.ppm");
        } catch (ErrorLecturaFichero &e) {
            cout << "Error al leer imagen de entrada" << endl;
            return 1;
        }

        cout << "Imagen leida" << endl;

        int nfilas1 = img.numFilas();
        int ncol1 = img.numColumnas();

        int r1 = 0;
        int g1 = 255;
        int b1 = 0;

        double minlat1 = 9e99;
        double maxlat1 = 0;
        double minlon1 = 9e99;
        double maxlon1 = 0;

        vector<double> vlat1, vlon1;

        fstream fs1("./zipcode.csv", fstream::in | fstream::out);
        int nlineas1 = 0;
        while (!fs1.eof()) {
            char linea[250];

            fs1.getline(linea, 250); //la primera no la cuento
            fs1.getline(linea, 250);
            nlineas1++;

            string lin(linea);
            double numlat, numlon;

            size_t poscoma = lin.find(",", 0);
            string codigo = lin.substr(0, poscoma);
            if (codigo.size() > 2) codigo = codigo.substr(1, poscoma - 2);
            lin = lin.substr(poscoma + 1, 255);

            poscoma = lin.find(",", 0);
            string city = lin.substr(0, poscoma);
            if (city.size() > 2) city = city.substr(1, poscoma - 2);
            lin = lin.substr(poscoma + 1, 255);

            poscoma = lin.find(",", 0);
            string state = lin.substr(0, poscoma);
            if (state.size() > 2) state = state.substr(1, poscoma - 2);
            lin = lin.substr(poscoma + 1, 255);

            poscoma = lin.find(",", 0);
            string lon = lin.substr(0, poscoma);
            if (lon.size() > 2) {
                lon.erase(0, 1);
                lon.erase(lon.size() - 1);
                char * cslon = new char [lon.length() + 1];
                strcpy(cslon, lon.c_str());
                numlon = atof(cslon);
                vlon1.push_back(numlon);
                if (numlon < minlon1) minlon1 = numlon;
                if (numlon > maxlon1) maxlon1 = numlon;

            }
            lin = lin.substr(poscoma + 1, 255);

            poscoma = lin.find(",", 0);
            string lat = lin.substr(0, poscoma);
            if (lat.size() > 2) {
                // Borramos las comillas
                lat.erase(0, 1);
                lat.erase(lat.size() - 1);
                char * cslat = new char [lat.length() + 1];
                strcpy(cslat, lat.c_str());
                numlat = atof(cslat);
                vlat1.push_back(numlat);
                if (numlat < minlat1) minlat1 = numlat;
                if (numlat > maxlat1) maxlat1 = numlat;

            }
            lin = lin.substr(poscoma + 1, 255);

            CodigoPost postal(codigo, numlon, numlat, city, state);
            mr.insertar(numlon, numlat, postal);

        }
        
        std::cout << "Maximo de elementos en celda " << mr.maxElementosCelda() << std::endl;

        cout << "lat: xmin = " << minlat1 << ", " << "xmax = " << maxlat1 << endl;
        cout << "lon: ymin = " << minlon1 << ", " << "ymax = " << maxlon1 << endl;

        double rangox1 = maxlat1 - minlat1;
        double rangoy1 = maxlon1 - minlon1;

        cout << "rango x = " << rangox1 << endl;
        cout << "rango y = " << rangoy1 << endl;

        cout << "nfilas = " << nfilas1 << endl;
        cout << "ncol = " << ncol1 << endl;

        double pixelPorGradoX1 = (double) (nfilas1 - 1) / rangox1;
        double pixelPorGradoY1 = (double) (ncol1 - 1) / rangoy1;


        for (int i = 0; i < vlon1.size(); i++) {
            int posX = (vlat1[i] - minlat1) * pixelPorGradoX1;
            int posY = ncol1 - 1 - ((vlon1[i] - minlon1) * pixelPorGradoY1);
            img.pintarPixel(posX, posY, r1, g1, b1);
        }

        try {
            img.guardar("./mapaUsaResult1.ppm");
        } catch (ErrorEscrituraFichero &e) {
            cout << "Error al escribir fichero" << endl;
            return 1;
        }

        cout << "Operación realizada con exito: Primer ejercicio concluido." << endl;

    } else {

        //Segundo programa de prueba: 
        MallaRegular<CodigoPost> mr2(0, -180, 360, 180, 1500);

        Img img1(1, 1);

        try {
            img1 = Img("./mapaUsa.ppm");
        } catch (ErrorLecturaFichero &e) {
            cout << "Error al leer imagen de entrada" << endl;
            return 1;
        }

        cout << "Imagen leida" << endl;

        int nfilas = img1.numFilas();
        int ncol = img1.numColumnas();

        
        int r = 0;
        int g = 255;
        int b = 0;

        double minlat = 9e99;
        double maxlat = 0;
        double minlon = 9e99;
        double maxlon = 0;

        double lat1 = -125.0;
        double lon1 = 23.0;

        double lat2 = -65.0;
        double lon2 = 50.0;

        vector<double> vlat, vlon;
        vlat.clear();
        vlon.clear();
        fstream fs("./zipcode.csv", fstream::in | fstream::out);
        int nlineas = 0;
        while (!fs.eof()) {
            char linea[250];

            fs.getline(linea, 250); //la primera no la cuento
            fs.getline(linea, 250);
            nlineas++;

            string lin(linea);
            double numlat, numlon;

            size_t poscoma = lin.find(",", 0);
            string codigo = lin.substr(0, poscoma);
            if (codigo.size() > 2) codigo = codigo.substr(1, poscoma - 2);
            lin = lin.substr(poscoma + 1, 255);

            poscoma = lin.find(",", 0);
            string city = lin.substr(0, poscoma);
            if (city.size() > 2) city = city.substr(1, poscoma - 2);
            lin = lin.substr(poscoma + 1, 255);

            poscoma = lin.find(",", 0);
            string state = lin.substr(0, poscoma);
            if (state.size() > 2) state = state.substr(1, poscoma - 2);
            lin = lin.substr(poscoma + 1, 255);

            poscoma = lin.find(",", 0);
            string lon = lin.substr(0, poscoma);
            if (lon.size() > 2) {
                lon.erase(0, 1);
                lon.erase(lon.size() - 1);
                char * cslon = new char [lon.length() + 1];
                strcpy(cslon, lon.c_str());
                numlon = atof(cslon);
                vlon.push_back(numlon);
                if (numlon < minlon)
                    minlon = numlon;
                if (numlon > maxlon)
                    maxlon = numlon;

            }
            lin = lin.substr(poscoma + 1, 255);

            poscoma = lin.find(",", 0);
            string lat = lin.substr(0, poscoma);
            if (lat.size() > 2) {
                // Borramos las comillas
                lat.erase(0, 1);
                lat.erase(lat.size() - 1);
                char * cslat = new char [lat.length() + 1];
                strcpy(cslat, lat.c_str());
                numlat = atof(cslat);
                vlat.push_back(numlat);
                if (numlat < minlat) minlat = numlat;
                if (numlat > maxlat) maxlat = numlat;

            }
            lin = lin.substr(poscoma + 1, 255);

            CodigoPost postal(codigo, numlat, numlon, city, state);
            mr2.insertar(numlon, numlat, postal);

        } 

        std::cout << "Maximo de elementos en celda " << mr2.maxElementosCelda() << std::endl;

        cout << "lat: xmin = " << minlat << ", " << "xmax = " << maxlat << endl;
        cout << "lon: ymin = " << minlon << ", " << "ymax = " << maxlon << endl;

        double rangox = maxlat - minlat;
        double rangoy = maxlon - minlon;

        cout << "rango x = " << rangox << endl;
        cout << "rango y = " << rangoy << endl;

        cout << "nfilas = " << nfilas << endl;
        cout << "ncol = " << ncol << endl;

        double pixelPorGradoX = (double) (nfilas - 1) / rangox;
        double pixelPorGradoY = (double) (ncol - 1) / rangoy;

        img1.pintarRecuadro((lat1 - minlat) * pixelPorGradoX, ncol - 1 - ((lon1 - minlon) * pixelPorGradoY),
                (lat2 - minlat) * pixelPorGradoX, ncol - 1 - ((lon2 - minlon) * pixelPorGradoY), 255, 0, 0);

        // aqui se realiza el test del modo:
        auto v = mr2.buscarRango(lon1, lat1, lon2, lat2);
        for (int i = 0; i < v.size(); ++i) {
            int posX = (v[i]->GetLatitud() - minlat) * pixelPorGradoX;
            int posY = ncol - 1 - ((v[i]->GetLongitud() - minlon) * pixelPorGradoY);
            img1.pintarPixel(posX, posY, r, g, b);
        }


        try {
            img1.guardar("./mapaUsaResult2.ppm");
        } catch (ErrorEscrituraFichero &e) {
            cout << "Error al escribir fichero" << endl;
            return 1;
        }

        cout << "Operación realizada con exito" << endl;
    }
    return EXIT_SUCCESS;
}

