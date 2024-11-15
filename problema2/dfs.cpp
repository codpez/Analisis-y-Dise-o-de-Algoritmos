#include <iostream>
#include <vector>
#include <list>

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

//variables globales para tener acceso dentro de las funciones
typedef std::pair<int,int> arista;

std::list<std::pair<std::list<int>,int>> lista_camino;

//https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
std::vector<int> arr;
std::vector<std::pair<int,int>> combinaciones;
void combinationUtil(std::vector<int> arr,int data[],int start,int end,int index,int r);

int costo = 0;

//DFS recursivo
//camino actual
//peso actual
//lista de caminos
bool dfs(int v,int fin,std::vector<std::vector<arista>> adj_list,std::vector<bool> visitados,std::list<int> camino){

  visitados[v] = true;

  //agregar el nodo al camino
  camino.push_back(v);
  
  if(v==fin){
    
    // display the original list 
    
    //std::cout << "encontre el camino costo::" << costo<< std::endl;

    lista_camino.push_back(std::make_pair(camino,costo));
    
    costo = 0;
    return true;
  }

  
  for(int i=0;i<(int) adj_list[v].size();i++){
    
    if(visitados[adj_list[v][i].first]==false){
      
      //std::cout << "Analizando nodo: " << v << "a visitar: " << adj_list[v][i].first << " w: " << adj_list[v][i].second <<std::endl;

      costo = costo + adj_list[v][i].second; //si no esta visitado sumarlo al costo
            
      if(dfs(adj_list[v][i].first,fin,adj_list,visitados,camino))
	return true;
      else
	costo = 0;

    }
  }

  camino.pop_back();
  visitados[v] = false;
  
  return false;
}


//https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
void combination(std::vector<int> arr, int n, int r){
  int data[r];
  combinationUtil(arr,data,0,n-1,0,r);
}

//https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
void combinationUtil(std::vector<int> arr,int data[],int start,int end,int index,int r){
  if(index ==r){
    //std::cout << data[0] << "," << data[1] << std::endl;
    combinaciones.push_back(std::make_pair(data[0],data[1]));
    return;
  }

  for(int i=start;i<=end&&end-i+1>=r-index;i++){
    data[index] = arr[i];
    combinationUtil(arr,data,i+1,end,index+1,r);
  }
  
}

//hilo principal
int main(){

  int num_ciudades;   //vertices
  int num_carreteras; //aristas

  std::vector<bool> visitados;               //visitados
  std::vector<std::vector<arista>> adj_list; //lista de adjacencia
  
  std::list<int> camino; //camino actual
    
  //------ construir adj list ------------
  std::cin >> num_ciudades >> num_carreteras;
  
  //uno basado
  adj_list.resize(num_ciudades+1);
  visitados.resize(num_ciudades+1);
  
  for(int i=0;i<num_carreteras;i++){
    
    int u,v,w;
    std::cin >> u >> v >> w;
    adj_list[u].push_back(arista(v,w));
    
  }
  //--------------------------------------

  //llenar visitados respecto a adj list
  for(int i=0;i<(int)adj_list.size();i++){
    visitados[i] = false;
    arr.push_back(i);
  }

  //combinaciones par de ciudades
  int r = 2;
  int n = adj_list.size();

  combination(arr,n,r);

  //iterar en los pares
  for(int i=0;i<(int)combinaciones.size();i++){
    
    //std::cout << combinaciones[i].first <<","<< combinaciones[i].second<< std::endl;

    int inicio = combinaciones[i].first;
    int fin = combinaciones[i].second;
    
    dfs(inicio,fin,adj_list,visitados,camino);
    
  }

  //----- OBTENER PESO MAXIMO --------------
  int peso_max = 0;
  std::list<int> camino_max;
  
  //iterar en la lista_camino's encontrados
  for(auto nodo: lista_camino) {
    if(nodo.second>peso_max){
      peso_max = nodo.second;
      camino_max = nodo.first;
    }
  }
  
  std::cout << "PESO MAX: " << peso_max << std::endl;
  std::cout << "----------" << std::endl;
  std::cout << "RECORRIDO: " << std::endl;

  //iterar en la lista del camino max
  for(auto camino: camino_max){
    std::cout << camino << " " ;
  }

  std::cout << std::endl;
    
  return 0;

}
