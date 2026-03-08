#include <iostream>
#include <string>
#include <fstream>
#include "../include/triangulo.hpp"
#include "../include/perimetro.hpp"

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

    /* TRIANGULO COM MAIOR ALTURA ----------------------*/
    /*Busca pilha que ao centro maximiza a altura do triangulo isoceles formado*/

    //Define o numero de pilhas
    long long int numero_pilhas;
    *entrada >> numero_pilhas;
    TrianguloIsoceles maiorPiramede(numero_pilhas);

    //Define a quantidade de blocos por pilha
    long long int quantidade_blocos;
    for(long long int i = 0; i < numero_pilhas; i++){
        *entrada >> quantidade_blocos;
        maiorPiramede.SetPilha(i, quantidade_blocos);
    }

    /* TRINAGULO COM MENOR PERIMETRO --------------------*/
    /* Busca conjunto de 3 arvores que minimizam o perimetro entre elas*/

    //Define o numero de arestas 
    long long int numero_arvores;
    *entrada >> numero_arvores;
    Perimetro menorPerimetro(numero_arvores);


    //Define coordernadas e indice para cada arvore
    long long int x, y;
    for(long long int j = 1; j < numero_arvores + 1; j++){
        *entrada >> x >> y;
        menorPerimetro.SetArvores(j, x, y);
    }

    /*Resultado*/
    std::cout << "Parte 1: " << maiorPiramede.BuscaMaiorAltura() << "\n";
    std::cout << "Parte 2: " ; menorPerimetro.BuscaMelhoresArvores();
    std::cout << "\n";

    return 0;
}