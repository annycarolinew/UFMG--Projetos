#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#define INF 0x3F3F3F3F3F3F3F3F //Infinito

//Struct que armazena vértice e distância
struct Vertice {
    long long int vertice;
    long long int custo;

    //Construtores
    Vertice(long long int v, long long int d): vertice(v),custo(d){}
    Vertice(long long int x): vertice(x), custo(INF){}
    Vertice(): vertice(-1), custo(INF){}
    
    //Sobreescrição operadores, ordernação com base na distância
    bool operator<(const Vertice& outro) const  { return custo < outro.custo;  }
    bool operator<=(const Vertice& outro) const { return custo <= outro.custo; }
};

template <typename T>
//Estrutura de Dados Min Heap
class Heap {
private:
    std::vector<T> data; //Vector da fila de Prioridade

    //Get indices
    long long int GetAncestral(long long int posicao);
    long long int GetSucessorEsq(long long int posicao);
    long long int GetSucessorDir(long long int posicao);

    /*Reorderna dados*/
    void HeapifyPorCima(long long int posicao);
    void HeapifyPorBaixo(long long int posicao);

public:
    //Constutor
    Heap();     
    //Destrutor
    ~Heap();    

    /*Funções de alteração no heap*/
    void Insere(const T& elemento);
    T Remove();

    //Verifica se o heap está vazio
    bool empty() const { return data.empty(); } 

    //Retorna tamanho do heap
    long unsigned int size() const { return data.size(); }
};

/* IMPLEMENTAÇÃO --------------------------------*/ 

/*Construtor*/
template <typename T>
Heap<T>::Heap(){}

/*Destrutor*/
template <typename T>
Heap<T>::~Heap(){}

/*Insere elemento*/
template <typename T>
void Heap<T>::Insere(const T& elemento) {
    //Insere e reordena
    data.push_back(elemento);
    HeapifyPorCima(data.size() - 1);
}

/*Remove o menor elemento*/
template <typename T>
T Heap<T>::Remove() {
    if (data.empty()) {
        //Se o heap estive vazio retorna nulo
        return T(-1);  
    }

    //Troca a raiz com uma folha
    T aux_raiz = data[0];
    data[0] = data.back();
    data.pop_back();

    //Reordena
    HeapifyPorBaixo(0);
    return aux_raiz;
}

/*Getters -------------------------------------*/
template <typename T>
long long int Heap<T>::GetAncestral(long long int posicao){
    return (posicao - 1)/2;
}
template <typename T>
long long int Heap<T>::GetSucessorEsq(long long int posicao){
    return (2* posicao) + 1;
}
template <typename T>
long long int Heap<T>::GetSucessorDir(long long int posicao){
    return (2* posicao) + 2;
}


template <typename T>
/*Reestrutura o heap de forma top-down*/
void Heap<T>::HeapifyPorBaixo(long long int posicao){
    long long int menor = posicao;
    long long int esq = GetSucessorEsq(posicao);
    long long int dir = GetSucessorDir(posicao);
    long long int tamanho = data.size();

    // Verifica se o sucessor a esquerda é menor que o atual
    if (esq < tamanho && data[esq] < data[menor])
        menor = esq;
    // Verifica se o sucessor a direita é menor que o atual
    if (dir < tamanho && data[dir] < data[menor])
        menor = dir;

    //Se o sucessor é menor que atual, troca e chama a função recursivamente
    if (menor != posicao) {
        std::swap(data[posicao], data[menor]);
        HeapifyPorBaixo(menor);
    }
}

template <typename T>
/*Reestrutura o heap de forma bottom-up*/
void Heap<T>::HeapifyPorCima(long long int posicao){
    //Enquanto não estiver na raiz e o valor for menor que do antecessor
    while (posicao > 0 && data[posicao] < data[GetAncestral(posicao)]) {
        //Troca os elementos e a posição
        std::swap(data[posicao], data[GetAncestral(posicao)]);
        posicao = GetAncestral(posicao);
    }
}

#endif // HEAP_HPP
