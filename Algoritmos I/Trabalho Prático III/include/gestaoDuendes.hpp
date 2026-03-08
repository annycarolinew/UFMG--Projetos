#include <vector>
#include <map>
#include <set>
#include <string> 
#include <algorithm>
#define TRUE 1
#define FALSE 0

class GestaoDuendes{

    private:
        std::vector<std::vector<int>> grafo_duendes;
        int n_duendes;
        int n_conflitos;

    public:
        /*Construtor e Destrutor*/
        GestaoDuendes(int numDuendes, int mConflitos);
        ~GestaoDuendes();

        /*Funções Auxiliares*/
        std::string DefineIdGrupo(std::vector<int> grupo);
        //Adiciona a aresta que representa o conflito na lista de adjacencia
        void InsereConflito(int i_duende, int j_duende);
        //Funça que retorna qual é menor lexigroficamente
        int MenorLexicografico(const std::vector<int>& grupo1,const std::vector<int>& grupo2);

        /*Funções de definição de conjuntos*/
        //Função que define o maior grupo de duendes das metades da distribuição ena intersecçao dessas
        std::vector<int> SelecaoDuendes();
        //Função que constroi arvore de decisao e registra solucoes já calculadas
        std::vector<int> ArvoreDecisao(const std::vector<int>& grupo_atual, std::map<std::string, std::vector<int>>& registro_solucoes);
        //Representa o nó da arvore de decisão com o duende não incluso
        std::vector<int> GrupoSemDuende(const std::vector<int>& grupo_atual);
        //Representa o nó da arvore de decisão com o duende incluso
        std::vector<int> GrupoComDuende(const std::vector<int>& grupo_atual, int i_duende);


        /*Funções para geraçõe de grupos de um conjuntos*/
        //Gera todos os grupos possiveis sem conflito
        std::vector<std::vector<int>> GeraTodosGrupos(const std::vector<int>& grupo_candidato);
        //Gera todos os grupos possiveis sem conflito para o i-esimo duende
        void GeraGrupo(const std::vector<int>& conjunto,int i_duende, std::vector<int>& subconjunto_atual,std::vector<std::vector<int>>& grupos);
        
};