#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <set>

//Empresa de transportes
//Conocer:
//la distancia total entre un par de ciudades
//la lista de almacenes que forman dicha ruta
//el tiempo total de ejecucion

/**

La empresa Transportes Eficientes dedicada a la logı́stica tiene almacenes 
situados en diversos estados del paı́s. 

Dado que se conocen las distancias de las carreteras comunican ciertos pares 
de almacenes, entonces es posible modelar esta situación como un grafo
ponderado no dirigido. 

El gerente de la empresa desea conocer la ruta más larga entre cualquier 
par de almacenes ya que esto le permitirá tomar decisiones estratégicas para
hacer más eficiente la operación de su empresa. Dado este problema práctico, 
desarrolle los siguientes puntos:
a) Diseñe e implemente en C++ un algoritmo recursivo basado en DFS para encontrar
la ruta más larga entre cualquier par de almacenes de la empresa. 
El programa recibe por redirección de la lı́nea de comandos 
el nombre de un archivo de texto que contiene un grafo ponderado 
dirigido con el formato que se utilizó en clase (sesión 9). 

El resultado que se imprimirá en pantalla es la distancia total de la ruta 
más larga entre cualquier par de almacenes de la empresa, 
la lista de almacenes que forman dicha ruta y el tiempo total de ejecución. 
Asegurese de utilizar una lista de adyacencia para representar el grafo.

 **/

typedef std::pair<int,int> arista;

int predfn = 0;
int postdfn = 0;
std::vector<bool> visitados;
std::vector<std::vector<arista>> adj_list;

//DFS
//int dfs(std::vector<std::vector<arista>> &adj_list){
int dfs(int v){
  
  
  
  predfn = predfn + 1;
  visitados[v] = true;
  for(int i=0;i<adj_list[v].size();i++){
    std::cout << "Analizando nodo: " << v << std::endl;
    std::cout << "visite: " << adj_list[v][i].first << std::endl;
    if(visitados[adj_list[v][i].first]==false){
      if(visitados[adj_list[v][i].first]==false){
	dfs(adj_list[v][i].first);
      }
    }
  }

  postdfn = postdfn + 1;

  /**-----------------------------------------------
  // imprimir lista de adjacencia
  //-----------------------------------------------
  int cc = 1;
  for(const auto& nodo: adj_list){
    
    std::cout << "---------------------" << std::endl;
    std::cout << "nodo: " << cc << std::endl;
    std::cout << "---------------------" << std::endl;
    for(const auto& vecinos: nodo){
      std::cout << cc << "," << vecinos.first << "-" << vecinos.second << std::endl;
    }
    cc = cc + 1;
  }
  //-----------------------------------------------**/

  return 0;
}

int main(){

  int num_ciudades;
  int num_carreteras;
  
  //------ construir adj list ------------
  std::cin >> num_ciudades >> num_carreteras;

  adj_list.resize(num_ciudades+1);
  visitados.resize(num_ciudades+1);
  
  for(int i=0;i<num_carreteras;i++){
    
    int u,v,peso;
    std::cin >> u >> v >> peso;
    //TODO: fix cero basado uno basado
    adj_list[u].push_back(arista(v,peso));
    
  }
  //--------------------------------------
  
  predfn  = 0;
  postdfn = 0;
  
  for(int i=0;i<adj_list.size();i++){
    visitados[i] = false;
    //std::cout << "*****" << std::endl;
    //std::cout << "Nodo:: " << i+1 << std::endl;
    //std::cout << "-----" << std::endl;
    //for(int j=0;j<adj_list[i].size();j++){
    //  std::cout << i+1 << " - " << adj_list[i][j].first << " - w:" << adj_list[i][j].second << std::endl;
    //}
  }

  for(int i=0;i<adj_list.size();i++){
    if(visitados[i]==false){
      dfs(i);
    }
  }
  
  //
  std::cout << predfn << std::endl;
  std::cout << postdfn << std::endl;
  return 0;
}
