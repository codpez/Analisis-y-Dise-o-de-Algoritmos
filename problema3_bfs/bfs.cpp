#include <iostream>
#include <chrono>
#include <vector>
#include <queue>

//Un grafo es bipartita si todos sus vértices pueden ser divididos en dos subconjuntos disjuntos X y Y de forma tal que cada arco conecte un vertice en X con uno en Y.
//referencia https://www.geeksforgeeks.org/bipartite-graph/#using-breadthfirst-search-bfs

//Diseñe un algoritmo basado en BFS para verificar si un grafo es bipartita o no.

bool esBipartito(int V, std::vector<std::vector<int>> adj_list){
  int n = V;
  std::vector<int> visitado(n,-1);
  
  for(int i=0;i<n;i++){
    if(visitado[i]==-1){

      //BFS
      std::queue<int> cola;
      visitado[i] = 0;
      cola.push(i);
      
      while(!cola.empty()){
	int nodoActual = cola.front();
	cola.pop();
	
	for(auto &v : adj_list[nodoActual]){
	  if(visitado[v]==-1){
	    visitado[v] = 1 - visitado[nodoActual];
	    cola.push(v);
	  }else if(visitado[v]==visitado[nodoActual]){
	    return false;
	  }
	  
	}
      }
      //BFS
    }
  }

  return true;
}

int main(){

  //medir tiempo
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  
  int vertice; 
  int arista;

  //guardar datos
  std::cin >> vertice >> arista;

  //se crea un array de vectores con la cardinalidad de vertices(nodos)
  std::vector<std::vector<int>> adj(vertice+1);
  
  //ir poblando con la lectura de consola respecto
  //al num de aristas, este indica el num de conexiones en el grafo
  //decimos que existe una conexion entre el nodo 0 y nodo 1 de la siguiente forma: 0 1
  for (int i = 0; i < arista; i++) {

    int v1, v2;  //auxiliares que representan los vertices
    std::cin >> v1 >> v2; 
    //std::cout << v1 << "-" << v2 << std::endl;
    adj[v1].push_back(v2); //agregar en dos vias las 
    adj[v2].push_back(v1); //conexiones del grafo
  }
  

  //imprimir resultados
  
  if(esBipartito(vertice,adj)==true){
    std::cout << "El grafo SI es bipartita" << std::endl;
  }else{
    std::cout << "El grafo NO es bipartita" << std::endl;
  }
  
  //-------------------------------------------------------------------------------
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout << " - tiempo = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
  std::cout << " - tiempo = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
  std::cout << " - tiempo = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
  std::cout << " - tiempo = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[s]" << std::endl;
  
  return 0;
}
