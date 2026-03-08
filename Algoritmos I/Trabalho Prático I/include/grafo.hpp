#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "../include/heap.hpp"
#include <vector>

class Grafo{
    private:
        //Armazena os vizinhos do vértice e o indice da aresta referente
        std::vector<std::vector<Vertice>> lista_adjacencia;
        long long int vertices;
        
    public:
        //Vector que armazena arestas e seu custo, na ordem de inserção
        std::vector<std::pair<std::pair<long long int,long long int>, long long int>> arestas;
        //Diferença dos dados em relação a 0
        int residuo_origem = 1;

        Grafo(long long int vertices); //Construtor
        ~Grafo();                      //Destrutor

        //Inclui aresta e seu custo a lista de adjacencia
        void InserirAresta(long long int lin, long long int col, long long int dist);

        /*Função que retona vizinhos de um vértice*/
        const std::vector<Vertice>& GetVizinhos(long long int vertice);
        const std::vector<Vertice>& GetVizinhos(long long int vertice) const;
        
};


#endif