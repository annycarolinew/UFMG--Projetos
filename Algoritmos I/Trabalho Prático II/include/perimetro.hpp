#include <vector>
#include <algorithm>
#include <cmath>
#define INF 1e300 //Infinito

#ifndef PERIMETRO_HPP

/*Struct com coordernada e indice do Vertice*/
struct Vertice{
    long long int indice;
    long long int x;
    long long int y;

    /*Construtores*/
    Vertice(long long int i,long long int x_,long long int y_): indice(i), x(x_), y(y_){}
    Vertice(const Vertice& outro): indice(outro.indice), x(outro.x), y(outro.y){}

    /*Operadores*/
    bool operator<(const Vertice& outro) const {
        if (x != outro.x)
            return x < outro.x;

        if (y != outro.y)
            return y < outro.y;

        return indice < outro.indice;
    }

    bool operator==(const Vertice& outro) const {
        if (x == outro.x && y == outro.y)
            return true;

        return false;
    }

    Vertice& operator=(const Vertice& outro) {
        indice = outro.indice;
        x = outro.x;
        y = outro.y;
        return *this;
    }

    /*Retorna a distancia entre dois Vertices*/
    double dist(const Vertice &outro) const{
        if(x == outro.x && y == outro.y){ return 0; }
        long long int dx = x - outro.x;
        long long int dy = y - outro.y;
        return std::sqrt(dx*dx + dy*dy);
    }
};


class Perimetro{
private:
    //Vetor que armazena as coordenadas das árvores
    std::vector<Vertice> coordenadas;
    //Quantidade de árvores
    long long int n_arvores;

public:
    /*Construtor e Destrutor*/
    Perimetro(long long int n);
    ~Perimetro();

    /*Adiciona a posição i do vector de coordernadas as coordernas x e y*/
    void SetArvores(long long int i, long long int x, long long int y);

    /*Retorna o perímetro dado um conjunto de vértices*/
    double GetPerimetro(const std::vector<Vertice>& cood);

    /*Retorna o indice das coordenadas que compoem o triangulo com menor perimetro*/
    void Resultado(std::vector<Vertice> melhorTri, double menor_per);
    
    /*Retorna o menor perímetro e os respsectivos Vertices que compoem o triangulo*/
    void BuscaMelhoresArvores();

    /*Retorna os vertices do triangulo com menor perimetro dado um conjunto de vertices*/
    std::vector<Vertice> GetMenorTriangulo(long long int inicio, long long int fim, std::vector<Vertice> const& cood, double const menorPerimetro);

    /*Retorna os vertices do triangulo com menor perimetro no conjunto total por meio de D&C*/
    std::vector<Vertice> BuscaTriangulos(long long int inicio, long long int fim);

    /*Retorna os vertices do triangulo ao meio com menor perimetro no conjunto total por meio de D&C*/
    std::vector<Vertice> BuscaTriangulosMeio(long long int inicio, long long int fim, double menorPerimetro);
    
};

#endif
