#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <set>
/* Uriel Delgado Guevara

Referencias usadas para el codigo:

https://www.naukri.com/code360/library/check-if-two-line-segments-intersect
https://www.youtube.com/watch?v=bvlIYX9cgls
https://www.luisllamas.es/cpp-que-son-tuplas/
https://en.cppreference.com/w/cpp/utility/pair
https://www.learncpp.com/cpp-tutorial/stdoptional/

///////////////*****************************************************************************////////////////*/

// defino mi segmento y punto

// Anterior segmento
// using segmento = std::tuple<int,int,int,int>;
using punto = std::pair<int,int>;
using segmento = std::tuple<punto,punto>;


// std::vector<segmento> extraerDatos(int n){    // Funcion para extraer datos del txt y guardarlos.
//     std::vector<segmento> segmentos;
//     for (int i=0; i<n; i++){
//         int x1,y1,x2,y2;
//         std::cin >> std::get<0>(std::get<0>(segmentos)) >> std::get<1>(std::get<0>(segmentos)) >> std::get<0>(std::get<1>(segmentos)) >> std::get<1x|>(std::get<1>(segmentos));
//         segmentos.push_back(std::make_tuple(x1,y1,x2,y2)); 
//     }
//     return segmentos;
// 

std::vector<segmento> extraerDatos(int n) {
    std::vector<segmento> segmentos;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        segmentos.push_back(std::make_tuple(punto(x1, y1), punto(x2, y2)));
    }
    return segmentos;
}

int orientacion(punto p, punto q, punto r) // Funcion para saber la orientacion de un segmento.
{   // Obtengo la orientacion del segmento.
    // return = 0 es colinear 
    // return > 0 En sentido horario 
    // return < 0 En sentido antihorario 
    return (std::get<1>(q)-std::get<1>(p))*(std::get<0>(r)-std::get<0>(q))-(std::get<0>(q)-std::get<0>(p))*(std::get<1>(r)-std::get<1>(q));
}


bool esColinear(punto a1,punto b1, punto a2, punto b2){
    //Verifica si la linea es colinear o no.
    if(orientacion(a1,b1,a2)==0){
        //checa solapamientos.
        if(std::get<0>(a2)<= std::max(std::get<0>(a1),std::get<0>(b1))&& std::get<0>(a2) >= std::min(std::get<0>(a1), std::get<0>(b1)) && std::get<1>(a2) <= std::max(std::get<1>(a1), std::get<1>(b1)) && std::get<1>(a2) >= std::min(std::get<1>(a1), std::get<1>(b1))){
            return true;
        }
    }
    return false;
}
//Funcion para saber si hay o no interseccion
bool seIntersecta(punto a1, punto b1, punto a2, punto b2) {
    int d1 = orientacion(a1, b1, a2);
    int d2 = orientacion(a1, b1, b2);
    int d3 = orientacion(a2, b2, a1);
    int d4 = orientacion(a2, b2, b1);

    // Comprueba si los dos segmentos de linea intersectan
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        return true;
    }

    // Comprueba si los dos segmentos de linea con colineales o se solapan
    if (esColinear(a1, b1, a2, b2) || esColinear(a2, b2, a1, b1)) {
        return true;
    }

    return false;
}

//Funcion que uso para imprimir un vector de segmentos

void print(const std::vector<segmento> &input) {
    for (const auto& seg : input) {
        const auto& p1 = std::get<0>(seg);
        const auto& p2 = std::get<1>(seg);
        std::cout << "(" << p1.first << ", " << p1.second << ", " << p2.first << ", " << p2.second << ")\n";
    }
}

void print1(const segmento& seg) {
    const auto& p1 = std::get<0>(seg);
    const auto& p2 = std::get<1>(seg);
    std::cout << "(" << p1.first << ", " << p1.second << ", " << p2.first << ", " << p2.second << ")\n";
}




// Función para calcular el punto de intersección cuando sabemos que se intersectan
punto calcularPuntoInterseccion(punto a1, punto b1, punto a2, punto b2) {
    int A1 = b1.second - a1.second;
    int B1 = a1.first - b1.first;
    int C1 = A1 * a1.first + B1 * a1.second;

    int A2 = b2.second - a2.second;
    int B2 = a2.first - b2.first;
    int C2 = A2 * a2.first + B2 * a2.second;

    int det = A1 * B2 - A2 * B1;

    // Dado que `seIntersecta` confirmó la intersección, no necesitamos verificar `det == 0`
    int x = (B2 * C1 - B1 * C2) / det;
    int y = (A1 * C2 - A2 * C1) / det;

    return punto(x, y); // Punto de intersección
}

// Función para manejar datos e intersecciones
void manejoDatosEinterseccion(const std::vector<segmento>& segmentos) {
    std::ofstream outfile("intersecciones.txt");
    int k = 0;
    std::string resultado;
    std::set<punto> interseccionesUnicas;
    for (size_t i = 0; i < segmentos.size(); i++) {
        for (size_t j = i + 1; j < segmentos.size(); j++) {
            const auto& a1 = std::get<0>(segmentos[i]);
            const auto& b1 = std::get<1>(segmentos[i]);
            const auto& a2 = std::get<0>(segmentos[j]);
            const auto& b2 = std::get<1>(segmentos[j]);

            if (seIntersecta(a1, b1, a2, b2)) {
                punto interseccion = calcularPuntoInterseccion(a1, b1, a2, b2);

                // Verificar que el punto está dentro de los límites de ambos segmentos
                if (std::min(a1.first, b1.first) <= interseccion.first && interseccion.first <= std::max(a1.first, b1.first) &&
                    std::min(a1.second, b1.second) <= interseccion.second && interseccion.second <= std::max(a1.second, b1.second) &&
                    std::min(a2.first, b2.first) <= interseccion.first && interseccion.first <= std::max(a2.first, b2.first) &&
                    std::min(a2.second, b2.second) <= interseccion.second && interseccion.second <= std::max(a2.second, b2.second)) {

                    // Intentamos insertar el punto en el set
                    if (interseccionesUnicas.insert(interseccion).second) {
                        k++;
                        resultado += std::to_string(interseccion.first) + " " + std::to_string(interseccion.second) + "\n";
                        
                        // Imprimir en consola el punto de intersección detectado
                        //std::cout << "Interseccion " << k << ": (" << interseccion.first << ", " << interseccion.second << ")\n";
                    }
        }
    }
    std::ofstream outfile("intersecciones.txt");
    outfile << k << "\n" << resultado;
    outfile.close();
  }
}
}


int main(){
  
    //pasamos el archivo para leerlo.
    std::tuple<int,int> puntos_interseccion;
    std::vector<segmento> segmentos;
    int n;
    std::cin >> n;
    segmentos = extraerDatos(n);
    //print(segmentos);
    manejoDatosEinterseccion(segmentos);
    // punto a1 = {1, 2}, b1 = {1, 7}, a2 = {5, 5}, b2 = {-5,5};
    // std::cout << orientacion(a1,b1,a2)<< std::endl;
    return 0;
}