#include <iostream>
#include <vector>
#include <tuple>
/* Uriel Delgado Guevara

Referencias usadas para el codigo:

https://www.naukri.com/code360/library/check-if-two-line-segments-intersect
https://www.youtube.com/watch?v=bvlIYX9cgls
https://www.luisllamas.es/cpp-que-son-tuplas/
///////////////*****************************************************************************////////////////*/
using segmento = std::tuple<int,int,int,int>;
using punto = std::pair<int,int>

punto interseccion(punto p, punto q, punto r){

}

void print(std::vector<segmento> &input)
{
    for (const auto& segmento : input) { // for each para recorrer todo el vector
        std::cout << "("
                   <<std::get<0>(segmento)<<","
                   <<std::get<1>(segmento)<<","
                   <<std::get<2>(segmento)<<","
                   <<std::get<3>(segmento)<<")"<<std::endl;}
    
}

int main(){
  
    //pasamos el archivo para leerlo.
    std::tuple<int,int> puntos_interseccion;
    std::vector<segmento> segmentos;
    int n;
    std:: cin >> n;
    for (int i=0; i<n; i++){
        int x1,y1,x2,y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        segmentos.push_back(std::make_tuple(x1,y1,x2,y2)); 
    }
    print(segmentos);
    return 0;
}