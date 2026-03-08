#include "../include/grafo.hpp"

/*Construtor*/
Grafo::Grafo(long long int v_):vertices(v_){
    lista_adjacencia.resize(vertices);
};

/*Destrutor*/
Grafo::~Grafo(){};

/*Insere nova aresta e seu custo*/
void Grafo::InserirAresta(long long int lin_, long long int col_, long long int dist){
    //Retira da linha e da coluna o resíduo para tornar que o menor indice seja zero
    long long int lin = lin_ - residuo_origem;
    long long int col = col_ - residuo_origem;

    //Adiciona nova aresta no vector
    this->arestas.push_back({{std::min(lin,col), std::max(lin,col)}, dist});
    
    //Verifica se o indice é válido e adiciona na lista
    if(lin < vertices && col < vertices && lin >= 0 && col >= 0){
        long long int indice_aresta = this->arestas.size() - 1;
        lista_adjacencia[lin].push_back({col, indice_aresta});
        lista_adjacencia[col].push_back({lin, indice_aresta});
    }

};

/*Retorna vizinho referente a um vértice*/
const std::vector<Vertice>& Grafo::GetVizinhos(long long int vertice_){         return this->lista_adjacencia[vertice_];    };
const std::vector<Vertice>& Grafo::GetVizinhos(long long int vertice_) const{   return this->lista_adjacencia[vertice_];    };
