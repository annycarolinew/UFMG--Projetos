#include "../include/triangulo.hpp"

/*Construtor*/
TrianguloIsoceles::TrianguloIsoceles(long long int n): pilhas(n), n_pilhas(n){}

/*Destrutor*/
TrianguloIsoceles::~TrianguloIsoceles(){}

/*Setter*/
void TrianguloIsoceles::SetPilha(long long int i, long long int quant_blocos){
    pilhas[i] = quant_blocos;
}

/*Percorre as pilhas de forma crescente e decrescente em relação ao índice em busca de encontrar a maior altura 
possível para cada pilha*/
long long int TrianguloIsoceles::BuscaMaiorAltura(){

    //Altura máxima a ser definida
    long long int max_altura = 0;

    //Altura por pilha
    long long int altura = 0;

    //Altura máxima alcançada por pilha pela esquerda e pela direita
    std::vector<long long> crescente(n_pilhas), decrescente(n_pilhas);
    crescente[0] = 1;
    decrescente[n_pilhas - 1] = 1;

    //Percorre todas as pilhas em ordem crescente e descrescente
    for (long long int i = 1; i < n_pilhas; i++) {

        //Sequência crescente de forma gradual (+1) sem ultrapassar as alturas originais
        //Se o menor valor for o da pilha não é possível formar a sequência
        crescente[i] = std::min(pilhas[i], crescente[i-1] + 1);

        //Sequência decrescente de forma gradual (+1) sem ultrapassar as alturas originais
        //Se o menor valor for o da pilha não é possível formar a sequência
        long long int j = (n_pilhas - 1) - i;
        decrescente[j] = std::min(pilhas[j], decrescente[j+1] + 1);
    }

    //Percorre todos centros (possíveis vertices principais)
    for (long long int centro = 1; centro < n_pilhas; centro++) {
        //Define a maior altura possível na pilha
        altura = std::min(crescente[centro], decrescente[centro]);
        
        //Verifica a maior altura encontrada
        if (altura > max_altura) {
            max_altura = altura;
        }
    }

    return max_altura; //Retorna mairo altura
    
}