#ifndef CAMINHO_MIN_HPP
#define CAMINHO_MIN_HPP
#include "../include/heap.hpp"
#include "../include/grafo.hpp"

class CaminhoMinimo{
    private:
        Grafo grafo;
        long long int vertices, arestas;
    public:

        CaminhoMinimo(long long int vertices, long long int arestas);   //Construtor
        ~CaminhoMinimo();                                               //Destrutor
        
        //Função que busca o caminho minimo e retorna a distancia entres vértices desse caminho
        std::vector<long long int> Dijkstra(long long int v_inicial, std::vector<std::vector<Vertice>>& ant);
        void DistanciaMinima(std::vector<std::vector<Vertice>>& antecessores, long long int v_origem, long long int v_dest);

        //Função que percorre a arvore de caminho minimo do djasktra e encontras as arestas que compoem ao menos um caminho minimo
        void DFS_Minimos(const std::vector<std::vector<Vertice>>& ant,std::vector<int>& visitado,Heap<long long int>& arestas_minimas,long long int v);
        void ArestasMinimas(const std::vector<std::vector<Vertice>>& antecessores, Grafo& grafo_min, long long int v_dest);
            
        //Funções que percorrem o subgrafo de caminho minimo e busca arestas criticas
        void DFS_Tarjan(const Grafo& G_min, Heap<long long int>& criticas, std::vector<long long int>& ord_vist, 
            std::vector<long long int>& men_visit, long long int v_inicial, long long int vert_u, long long int& tempo); //Função recursiva
        void ArestasCriticas(const Grafo& G_min, long long int v_inicial); //Chama DFS para cada vértices
        
        /*Grafo ------------------*/
        void InsereGrafo(long long int lin_, long long int col_, long long int dist);
        int GetResiduoOrigem();
        
};


#endif