#include <iostream>

//para compilar
//g++ -std=c++17 datos_a_programa.cpp -o datos

//la bandera -std=c++17 dependera de la version que tengas del compilador

//como especificamos un nombre al archivo de salida llamado datos
//se deberá ejecutar de la siguiente manera, donde datos.txt será el archivo txt a pasarle
//en este ejemplo el archivo espera solo dos valores y se almacenan en las variables valor1, valor2
// ./datos < datos.txt

int main(){

  //vamos a pasarle dos valores y que los imprima
  int valor1,valor2; 

  std::cin >> valor1 >> valor2;

  std::cout << "El valor1 es:" << valor1 << std::endl;
  std::cout << "El valor2 es:" << valor2 << std::endl;

  return 0;
  
}
