#include "../include/caminhoMin.hpp"
#include <iostream>
#include <cmath>

/*Construtor*/
CaminhoMinimo::CaminhoMinimo(long long int vert, long long int aret): grafo(vert),vertices(vert), arestas(aret){};

/*Destrutor*/
CaminhoMinimo::~CaminhoMinimo(){};

/*ALGORITMOS --------------------------------------------------------------------------------------*/
/*Algoritmo para buscar caminho minimo quando E < V^2*/
std::vector<long long int> CaminhoMinimo::Dijkstra(long long int v_inicial, std::vector<std::vector<Vertice>>& ant){
    std::vector<int> marcados;                  //Booleano que sinaliza quais vertices já foram analizados
    std::vector<long long int> distancia;       //Armazena a distancia do vertice inicial até o vértice i
    Heap<Vertice> filaPrioridade;               //Fila de prioridade que orderna as distâncias

    //"Aloca" espaço com a quantidade de vértices
    marcados.resize(vertices);
    distancia.resize(vertices);
    ant.resize(vertices);

    /*INICIALIZAÇÃO -------------------*/
    for (long long int i = 0; i < vertices; i++){
        distancia[i] = INF;
        marcados[i] = 0;
    }
    distancia[v_inicial] = 0;
    filaPrioridade.Insere(Vertice(v_inicial, distancia[v_inicial]));

    /*LOOP PARA ENCONTRAR A MENOR DISTÂNCIA --------------*/
    while (!filaPrioridade.empty()){
        
        Vertice dv = filaPrioridade.Remove(); //Pega o vértice com menor distância
        
        if(dv.vertice < 0 || dv.vertice > this->vertices){ continue;}
        //Verifica se o vértice atual já foi analizado
        if (marcados[dv.vertice] == 1) { continue;}
        marcados[dv.vertice] = 1; //Marca

        //Para todo vizinho do vértice atual
        for(const auto& v: this->grafo.GetVizinhos(dv.vertice)){
            long long int vizinho = v.vertice;
            long long int custo = this->grafo.arestas[v.custo].second;

            //Verifica se a distancia do vizinho é minima
            if(distancia[vizinho] > distancia[dv.vertice] + custo){
                distancia[vizinho] = distancia[dv.vertice] + custo;
                filaPrioridade.Insere(Vertice(vizinho, distancia[vizinho]));
                ant[vizinho].clear();
                ant[vizinho].push_back(Vertice(dv.vertice, v.custo));
            }else if(distancia[vizinho] == distancia[dv.vertice] + custo){
                ant[vizinho].push_back(Vertice(dv.vertice, v.custo));
            }
        }
        
    }

    return distancia;
}

/*Algoritmo baseado em DFS que percorre o subgrafo de caminho minimo buscando arestas criticas*/
void CaminhoMinimo::DFS_Tarjan(const Grafo& G_min, Heap<long long int>& criticas,std::vector<long long int>& ordem_vist, 
                        std::vector<long long int>& menor_vist, long long int vert_u, long long int vert_pai, long long int& tempo) {

    ordem_vist[vert_u] = menor_vist[vert_u] = tempo++;      //Define o tempo de acesso e o menor tempo de acesso com tempo atual
    
    //Para cada vizinho de v
    for (const auto& v : G_min.GetVizinhos(vert_u)) {
        long long int vizinho = v.vertice;
        long long int indice_aresta = v.custo;

        //Se vizinho for o pai de v (ciclo), pula para o próximo vizinho
        if (vizinho == vert_pai) continue;

        //Se o vizinho ainda não foi visitado
        if (ordem_vist[vizinho] == -1) {
            DFS_Tarjan(G_min, criticas, ordem_vist, menor_vist, vizinho, vert_u, tempo);    //Chama DFS
            menor_vist[vert_u] = std::min(menor_vist[vert_u], menor_vist[vizinho]);         //Atualiza o menor tempo de acesso

            if (menor_vist[vizinho] > ordem_vist[vert_u]) {
                //Se o menor tempo de acesso do vizinho atual for maior que o tempo de acesso do vértice atual
                criticas.Insere(G_min.arestas[indice_aresta].second); //aresta critica
            }
        } else {
            //Se o vizinho ainda já foi visitado
            menor_vist[vert_u] = std::min(menor_vist[vert_u], ordem_vist[vizinho]); //Atualiza o menor tempo de acesso
        }
    }
}

/*Função que percorre a arvore de caminho minimo com DFS afim de encontrar as arestas que compoem algum caminho minimo*/
void CaminhoMinimo::DFS_Minimos(const std::vector<std::vector<Vertice>>& ant, std::vector<int>& visitado,
                                Heap<long long int>& arestas_minimas, long long int v) {
    visitado[v] = 1; //Marca o vértice como visitado
    
    //Percorre todos vizinhos de v
    for (const auto& u : ant[v]) {
        long long int vizinho = u.vertice;
        long long int indice_aresta = u.custo;
        //Define a aresta como minima
        arestas_minimas.Insere(indice_aresta);

        if (visitado[vizinho] == 0) {
            //Chama recursivamente
            DFS_Minimos(ant, visitado, arestas_minimas, vizinho);
        }
    }
}

/*PROCEDIMENTOS ----------------------------------------------------------------------------------------*/
/*PARTE 1: aplica Dijkstra a partir do vertice de origem para encontra a distância entre ele e o vértice de destinho*/
void CaminhoMinimo::DistanciaMinima(std::vector<std::vector<Vertice>>& antecessores, long long int v_origem, long long int v_dest){
    std::vector<long long int> dist_origem = this->Dijkstra(v_origem, antecessores);
    long long int dist_min = dist_origem[v_dest];
    std::cout << dist_min << "\n";
}

/*PARTE 2: aplica dfs reverso no subgrafo de vertices antecessores encontrando as aresta que pertencem a um caminho minimo*/
void CaminhoMinimo::ArestasMinimas(const std::vector<std::vector<Vertice>>& antecessores, Grafo& grafo_min, long long int v_dest){
    Heap<long long int> arestas_minimas;            //Armazena arestas minimas ordernado
    std::vector<int> visitado(this->vertices, 0);   //Booleano de quais vertices já foram visitados no DFS
    DFS_Minimos(antecessores, visitado, arestas_minimas, v_dest); //DFS a partir do destino

    //Imprime o vetor de arestas minimas ordernardo e constroí o subgrafo com as arestas mininas
    while (!arestas_minimas.empty()) {
        long long int min_a = arestas_minimas.Remove();
        if(min_a < 0 || min_a >= arestas){ continue;}
        long long int vert_v = this->grafo.arestas[min_a].first.first;
        long long int vert_u = this->grafo.arestas[min_a].first.second;

        grafo_min.InserirAresta(vert_u,vert_v, min_a);
        std::cout << min_a + this->grafo.residuo_origem;
        if(min_a < arestas){ std::cout << " ";}

    }
    std::cout << "\n" ;
}

/*PARTE 3: aplica Tarjan ao subgrafo de caminho minimo verificando quais arestas são criticas*/
void CaminhoMinimo::ArestasCriticas(const Grafo& grafo_min, long long int v_origem){
    Heap<long long int> criticas;                                   //Heap para ordernar indices das arestas criticas
    std::vector<long long int> ordem_visitacao(this->vertices, -1); //Armazena quando cada vertice foi acessado
    std::vector<long long int> menor_visitacao(this->vertices);     //Armazena o menor tempo em que o vértice foi acessado
    long long int tempo = 0;                                        //O tempo de acesso aos vértices (iniciasse com zero)

    //Para todos os vértices pertencentes ao grafo
    for (long long int i = 0; i < this->vertices; i++) {
        //Caso ainda não tenha sido acessado
        if (ordem_visitacao[i] == -1) {
        this->DFS_Tarjan(grafo_min, criticas, ordem_visitacao, menor_visitacao, v_origem, i, tempo);
        }
    }

    /*ORDENA ARESTAS CRITICAS -------------------*/
    if(criticas.empty()){
        std::cout << "-1";
    }else{
        long unsigned int j = criticas.size();
        while(!criticas.empty()){
        std::cout << criticas.Remove() + 1;
        if(j > 1) std::cout << " ";
        j--;
        }
    }

    std::cout << "\n";
    }

/*GRAFO -------------------------------------------------------------------------------------------------*/
//Insere nova aresta no grafo
void CaminhoMinimo::InsereGrafo(long long int lin, long long int col, long long int dist){
    this->grafo.InserirAresta(lin,col,dist);
}

int CaminhoMinimo::GetResiduoOrigem(){
    return this->grafo.residuo_origem;
}