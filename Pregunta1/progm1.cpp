#include <iostream>
#include <vector>
#include <tuple>
/* Uriel Delgado Guevara

Referencias usadas para el codigo:

https://www.naukri.com/code360/library/check-if-two-line-segments-intersect
https://www.youtube.com/watch?v=bvlIYX9cgls
https://www.luisllamas.es/cpp-que-son-tuplas/
https://en.cppreference.com/w/cpp/utility/pair
///////////////*****************************************************************************////////////////*/

// defino mi segmento y punto

// Anterior segmento
// using segmento = std::tuple<int,int,int,int>;
using punto = std::pair<int,int>;
using segmento = std::tuple<punto,punto>;


std::vector<segmento> extraerDatos(int n){    // Funcion para extraer datos del txt y guardarlos.
    std::vector<segmento> segmentos;
    for (int i=0; i<n; i++){
        int x1,y1,x2,y2;
        std::cin >> std::get<0>(std::get<0>(segmentos)) >> std::get<1>(std::get<0>(segmentos)) >> std::get<0>(std::get<1>(segmentos)) >> std::get<1x|>(std::get<1>(segmentos));
        segmentos.push_back(std::make_tuple(x1,y1,x2,y2)); 
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
//Funcion para encontrar si hay o no interseccio
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
void print(std::vector<segmento> &input)
{
    for (const auto& segmento : input) { // for each para recorrer todo el vector
        std::cout << "("
                   <<std::get<0>(segmento)<<","
                   <<std::get<1>(segmento)<<","
                   <<std::get<2>(segmento)<<","
                   <<std::get<3>(segmento)<<")"<<std::endl;}
    
}
//Funcion que uso para imprimir un elemento del vector de segmentos
void print1(segmento segmento)
{
        std::cout << "("
                   <<std::get<0>(segmento)<<","
                   <<std::get<1>(segmento)<<","
                   <<std::get<2>(segmento)<<","
                   <<std::get<3>(segmento)<<")"<<std::endl;
    
}


//Funcion para transformar mis datos antes de meterlos a la funcion seIntersecta y que itera sobre el vector para verificar todas las posibles intersecciones

void manejoDatosEinterseccion(std::vector<segmento> segmentos){
    for(auto sec = segmentos.rbegin(); sec != segmentos.rend();++sec){
        print1(*sec);
        for
    }
    // for(int i=0;i<segmentos.size();i++){
    //     print1(segmentos[i]);
    //     for(int=1;i<segmentos.size();i++){

    //     }
    // }


}

int main(){
  
    //pasamos el archivo para leerlo.
    std::tuple<int,int> puntos_interseccion;
    std::vector<segmento> segmentos;
    int n;
    std::cin >> n;
    segmentos = extraerDatos(n);
    manejoDatosEinterseccion(segmentos);
    // punto a1 = {1, 2}, b1 = {1, 7}, a2 = {5, 5}, b2 = {-5,5};
    // std::cout << orientacion(a1,b1,a2)<< std::endl;
    return 0;
}