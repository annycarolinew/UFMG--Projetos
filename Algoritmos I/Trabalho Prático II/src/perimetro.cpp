#include "../include/perimetro.hpp"
#include <iostream>
#include <iomanip>

Perimetro::Perimetro(long long int n): n_arvores(n){ coordenadas.reserve(n);  }
Perimetro::~Perimetro(){}

//Retorna o menor perímetro e os respsectivos Vertices que compoem o trinagulo
void Perimetro::BuscaMelhoresArvores(){
    //Orderna os vertices em relação a X
    std::sort(coordenadas.begin(), coordenadas.end());
    
    //Busca conjunto de 3 ponstos com menor perímetro na esquerda e direita
    std::vector<Vertice> melhorTriangulo = BuscaTriangulos(0, n_arvores - 1);
    double menorPerimetro = GetPerimetro(melhorTriangulo);
    
    Resultado(melhorTriangulo,menorPerimetro);
}

//Saida com o resultado
void Perimetro::Resultado(std::vector<Vertice> melhorTri, double menor_per){

    //Ordernas os vertices do triangulo em relaçao ao indice
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2 - i; j++){
            if(melhorTri[j].indice > melhorTri[j+1].indice){
                std::swap(melhorTri[j], melhorTri[j+1]);
            }
        }
    }


    //Resultado
    std::cout << std::fixed << std::setprecision(4) << menor_per << " ";
    int i = 0;
    for(const auto &pts: melhorTri){
        std::cout << pts.indice;
        i++;

        if(i == 3){     std::cout << "\n";  }
        else{           std::cout << " ";   }
    }
}

/*Setter arvore*/
void Perimetro::SetArvores(long long int i, long long int x, long long int y){
    coordenadas.push_back(Vertice(i, x, y));
}

/*Get perimetro*/
double Perimetro::GetPerimetro(const std::vector<Vertice>& cood){
    //Se não ha vertices o suficiente
    if(cood.size() != 3){   return INF; }
    
    if(cood[0].dist(cood[1]) == 0 || cood[1].dist(cood[2]) == 0|| cood[2].dist(cood[0]) == 0){
        return INF;
    }

    return (cood[0].dist(cood[1]) + cood[1].dist(cood[2]) + cood[2].dist(cood[0]));
}

//Retorna o triangulo de menor perimetro em um sub conjunto de Vertices
std::vector<Vertice> Perimetro::GetMenorTriangulo(long long int inicio, long long int fim, std::vector<Vertice> const& vertices, double const menorPerimetro){
    //Se houver menos que 3 Vertices 
    if(fim - inicio + 1 < 3) return {};
    
    bool encontrado = false;

    double menorPer = menorPerimetro;         //Armazena o menor perímetro a ser encontrado
    Vertice p(-1,-1,-1);                      //Vertice para inicializar o vector de resultado
    
    //Vector que armazena os vértices do triangulo com menor perimetro
    std::vector<Vertice> vertMenorTriangulo {p,p,p}; 
    
    //Parte exaustiva da solução:
    //Busca de todas as combinações possíveis 3 vértices que
    for(long long int i = inicio; i <= fim; i++){
        for(long long int j = i+1; j <= fim; j++){

            //Verificação para versão otimizada do algortimo
            if (menorPerimetro != INF && std::fabs(vertices[j].y - vertices[i].y) >= menorPer) {   break;  }

            for(long long int k = j+1; k <= fim; k++){

                //Verificação para versão otimizada do algortimo
                if (menorPerimetro != INF && std::fabs(vertices[i].y - vertices[k].y) >= menorPer) {   break;  }

                //Se o perímetro calculado for o menor já encontrado
                //Atualiza vértices do triangulo com menor perimetro
                double perimetro = GetPerimetro({vertices[i],vertices[j],vertices[k]});

                if( perimetro <= menorPer){
                    menorPer = perimetro;
                    vertMenorTriangulo[0] = vertices[i];
                    vertMenorTriangulo[1] = vertices[j];
                    vertMenorTriangulo[2] = vertices[k];
                    encontrado = true;
                }
            }
        }
    }

    //Caso não seja encontra nenhum conjunto de vertices retorna um vectro vazio
    if(!encontrado){ return {}; } 

    return vertMenorTriangulo; //Retorna vértices
}

// Função que ordenar vertices em relação a Y 
bool ComparaY(const Vertice& a, const Vertice& b) {
    if (a.y != b.y) {
        return a.y < b.y;
    }
    return a.x < b.x; // Desempate por X
}

//Retorna o triangulo com menor perimetro no corte (meio)
std::vector<Vertice> Perimetro::BuscaTriangulosMeio(long long int inicio, long long int fim, double menorPerimetro){
    //double limiar_x = menorPerimetro / 2.0;     //Define limite
    long long int meio = (fim + inicio) / 2;    //Define a coorde

    std::vector<Vertice> vert_candidatos;   //vetores candidatos a minimizarem o perimetro
    for(long long int i = inicio; i <= fim; i++){
        // Adiciona se o vertices estiver proximo ao meio (vértice de corte)
        if(std::fabs(coordenadas[i].x - coordenadas[meio].x) < menorPerimetro){
            vert_candidatos.push_back(coordenadas[i]);
        }
    }

    //Orderna os vertices candidatos em Relação a Y
    std::sort(vert_candidatos.begin(), vert_candidatos.end(), ComparaY);

    //Retorna o trinagulo de menor perimetro
    return GetMenorTriangulo(0, vert_candidatos.size() - 1, vert_candidatos, menorPerimetro);
}

/*Retorna o triangulo com menor perimetrono do conjunto total, por meio de divisão e conquista busca em subconjunto de vertices
os que minimizam o permetro*/
std::vector<Vertice> Perimetro::BuscaTriangulos(long long int inicio, long long int fim){
    
    long long int n = fim - inicio + 1;
    //Verifica intervalores
    if(n < 3) return {}; // Não é possível formar um triângulo
    if(n == 3 && GetPerimetro(coordenadas) < INF) return coordenadas;
    if(n <= 6){
        //Busca vertices que minimizam perimetro por exaustão
        return GetMenorTriangulo(inicio, fim, coordenadas, INF);
    }

    long long int meio = (inicio + fim) / 2;

    /* Divide -------------------------------------------*/
    //Divide em esquerda e direita e busca o menor triângulo recursivamente
    std::vector<Vertice> MenorEsq = BuscaTriangulos(inicio, meio);
    std::vector<Vertice> MenorDir = BuscaTriangulos(meio + 1, fim);

    //Define o menor perímetro encontrado até agora (menorPerimetro / delta)
    double per_esq = GetPerimetro(MenorEsq);
    double per_dir = GetPerimetro(MenorDir);

    double menorPerimetro = per_esq;
    std::vector<Vertice> menorTriangulo = MenorEsq;

    //Verifica se é o menor perimetro
    if(per_dir < menorPerimetro){
        menorPerimetro = per_dir;
        menorTriangulo = MenorDir;
    }
    
    /* Conquista -------------------------------------------*/
    //Divide ao meio recursivamente
    std::vector<Vertice> MenorMeio = BuscaTriangulosMeio(inicio, fim, menorPerimetro);

    //Se não for encontrado nenhum triangulo no meio que miniminza o perimetro
    if(MenorMeio.empty()){  return menorTriangulo;  }

    double per_meio = GetPerimetro(MenorMeio);

    //Verifica se é o menor perimetro
    if(per_meio < menorPerimetro){
        menorPerimetro = per_meio;
        menorTriangulo = MenorMeio;
    }

    //Retorna vertices do menor triangulo
    return menorTriangulo; 
}

