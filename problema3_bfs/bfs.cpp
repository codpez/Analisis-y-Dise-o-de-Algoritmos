#include <iostream> //entrada de datos
#include <fstream>  //escribir a archivo
#include <chrono>   //medir tiempo

//Un grafo es bipartita si todos sus vértices pueden ser divididos en dos subconjuntos disjuntos X y Y de forma tal que cada arco conecte un vertice en X con uno en Y.

//Diseñe un algoritmo basado en BFS para verificar si un grafo es bipartita o no.
//5 4
//0 1
//1 2
//1 4
//2 3

int main(){

  //***C++11 Style:***
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  
  int dato;

  std::cin >> dato;
    
  
  //escribir el dato en archivo de salida
  std::ofstream output_file("archivo_salida.txt");

  if(output_file.is_open()){
    //iterar en una lista
    //for(const auto& pair: lista){
      
    //}

    output_file << "El dato es: " << dato << std::endl;
    
  }else{
    std::cerr << "Errores " << std::endl;
  }

  //-------------------------------------------------------------------------------
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout << "Tiempo = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
  std::cout << "Tiempo = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
  std::cout << "Tiempo = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
  std::cout << "Tiempo = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[s]" << std::endl;
  
  return 0;
}
