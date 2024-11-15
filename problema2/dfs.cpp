#include <iostream>
#include <vector>

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

int predfn = 0;
int postdfn = 0;

std::vector<bool> visitados;               //visitados
std::vector<std::vector<arista>> adj_list; //lista de adjacencia

//int costo;

std::vector<int> arr;
std::vector<std::pair<int,int>> combinaciones;

void combinationUtil(std::vector<int> arr,int data[],int start,int end,int index,int r);

int costo = 0;

//encontrar todos los caminos
std::vector<std::vector<int>> caminos(int inicio, int fin){
  std::vector<std::vector<int>> lista_caminos;
  std::vector<int> ruta_actual;
  std::vector<bool> visitados;
  dfs(inicio,fin,ruta_actual,visitados,lista_caminos);
  return lista_caminos;
}

//DFS recursivo
int dfs(int v,int fin,std::vector<int> ruta_actual,std::vector<bool> visitados, std::vector<std::vector<int>> lista_caminos){

  ruta_actual.push_back(v);
  
  visitados[v] = true;
  
  for(int i=0;i<adj_list[v].size();i++){

    if(visitados[adj_list[v][i].first]==false){

      std::cout << "Analizando nodo: " << v << "a visitar: " << adj_list[v][i].first
		<< " w: " << adj_list[v][i].second <<std::endl;

      costo = costo + adj_list[v][i].second; //si no esta visitado sumarlo al costo
      
      
      if(adj_list[v][i].first == fin){ //si es el resultado parar
	std::cout << "encontre el camino costo::" << costo<< std::endl;
	//std::cout << "encontre el camino ::" << std::endl;
	costo = 0;
	return 0;
      }

      
      //peso = dfs(adj_list[v][i].first);      

      
      //************cosas del problema*******************

      dfs(adj_list[v][i].first,fin);
      
      
    }
  }

  //postdfn = postdfn + 1;
  //std::cout << "post: " << postdfn << std::endl;
  return -1;
}

//https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
void combination(std::vector<int> arr, int n, int r){
  int data[r];
  combinationUtil(arr,data,0,n-1,0,r);
}

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

int main(){

  int num_ciudades;
  int num_carreteras;
  
  int peso;

  //------ construir adj list ------------
  std::cin >> num_ciudades >> num_carreteras;
  
  //TODO: fix cero basado uno basado
  adj_list.resize(num_ciudades+1);
  visitados.resize(num_ciudades+1);
  
  for(int i=0;i<num_carreteras;i++){
    
    int u,v,w;
    std::cin >> u >> v >> w;
    adj_list[u].push_back(arista(v,w));
    
  }
  //--------------------------------------

  
  predfn  = 0;
  postdfn = 0;
  
  for(int i=0;i<adj_list.size();i++){
    visitados[i] = false;
    arr.push_back(i);
  }

  /*
    for(int i=0;i<adj_list.size();i++){
    if(visitados[i]==false){
      dfs(i);
    }
  }
  */

  int r = 2;
  int n = adj_list.size();

  combination(arr,n,r);

  //iterar en los pares
  //for(int i=0;i<combinaciones.size();i++){
    
  //std::cout << combinaciones[i].first <<","<< combinaciones[i].second<< std::endl;

  int inicio = 1;//combinaciones[i].first;
  int fin = 8;//combinaciones[i].second;

  if(visitados[inicio]==false){
    dfs(inicio,fin);
  }
  //  std::vector<bool> visitados(n,false);
  //}
  
  /*
  for(int i=0;i<combinaciones.size();i++){

    //std::cout << combinaciones[i].first <<","<< combinaciones[i].second<< std::endl;

    std::cout << "VISITAR:" << combinaciones[i].first << "," << combinaciones[i].second << std::endl;

    

    
    
  }
  */
    

  /*
  for(int i=0;i<adj_list.size();i++){
    if(visitados[i]==false){
      dfs(i);
    }
  }
  */

  
  
  return 0;

}
