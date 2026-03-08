#include <iostream>
#include <string>
#include <fstream>
#include "../include/caminhoMin.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    istream* entrada;
    ifstream arquivo;

    //Abre arquivo
    if (argc >= 2) {
        // Lê pelo arquivo
        arquivo.open(argv[1]);

        if (!arquivo.is_open()) {
            cerr << "Erro ao abrir o arquivo: " << argv[1] << "\n";
            return 1;
        }
        entrada = &arquivo;  
    } else {
        // Lê entrada padrão
        entrada = &cin;     
    }

    //Verifica se a entrada não está vazia
    if(entrada == nullptr){ return 1; }

    //Iniciliza
    int vertices, arestas;
    *entrada >> vertices >> arestas;
    CaminhoMinimo caminho(vertices, arestas);
    
    //Insere dados na lista de adjacencia
    int vertice_1, vertice_2, dist_aresta;
    for(int i = 0; i < arestas; i++){
        *entrada >> vertice_1 >> vertice_2 >> dist_aresta;
        caminho.InsereGrafo(vertice_1, vertice_2,dist_aresta);
    }
    
    //Insere origem e destino do caminho
    long long int v_origem = 1 - caminho.GetResiduoOrigem();
    long long int v_dest = vertices - caminho.GetResiduoOrigem();

    std::vector<std::vector<Vertice>> antecessores; //Lista antecessores
    Grafo grafo_min(vertices); //Subgrafo do caminho minimo
    grafo_min.residuo_origem = 0;

    /*Encontra menor distância entre o vértice de origem e destino*/
    std::cout << "Parte 1: "; caminho.DistanciaMinima(antecessores,v_origem,v_dest);

    /*Encontra arestas que participam de caminho minino*/
    std::cout << "Parte 2: " ; caminho.ArestasMinimas(antecessores, grafo_min,v_dest);

    /*Encontra arestas criticas*/
    std::cout << "Parte 3: " ; caminho.ArestasCriticas(grafo_min,v_origem);

    return 0;
}