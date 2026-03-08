#include <vector>
#include <list>

#ifndef TRIANGULO_HPP

class TrianguloIsoceles{
    private:
        //Vetor com a quantidade de blocos por pilha
        std::vector<long long int> pilhas;
        //Quantidade de Pilhas
        long long int n_pilhas;
    public:
        /*Construtor e Destrutor*/
        TrianguloIsoceles(long long int n);
        ~TrianguloIsoceles();

        /*Define quantidade de blocos da i-esima pilha*/
        void SetPilha(long long int i, long long int quantidade_blocos);

        /*Função que retorna a maior altura possível no conjunto de pilhas*/
        long long int BuscaMaiorAltura();
};


#endif