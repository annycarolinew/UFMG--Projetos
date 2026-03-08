#include "../include/gestaoDuendes.hpp"
#include <iostream>

/*Construtor e Destrutor --------------------------------------*/
GestaoDuendes::GestaoDuendes(int numDuendes, int mConflitos):grafo_duendes(numDuendes), n_duendes(numDuendes), n_conflitos(mConflitos){
    for(int i = 0; i < numDuendes; i++){
        grafo_duendes[i].resize(n_duendes, FALSE);
    }
}
GestaoDuendes::~GestaoDuendes(){}

void GestaoDuendes::InsereConflito(int i_duende, int j_duende){
    //Adiciona a aresta referente ao conflito
    grafo_duendes[i_duende][j_duende] = TRUE;
    grafo_duendes[j_duende][i_duende] = TRUE;
}

/*Funcoes de definição de conjuntos --------------------------------------------*/
std::string GestaoDuendes::DefineIdGrupo(std::vector<int> grupo){
    std::string s(n_duendes, '0');
    //Os elementos que compoem o conjunto são representados por 1 na sua 
    //respectova posicao na string
    for (int x : grupo) s[x] = '1';

    return s;
}

//Define o grupo de duendes sem o i-esimo duende (i = n-1) em relacao ao grupo em analise
std::vector<int> GestaoDuendes::GrupoSemDuende(const std::vector<int>& grupo_atual){
    std::vector<int> grupo_sem_i = grupo_atual;
    grupo_sem_i.pop_back();
    //Retorna o grupo de trabalho sem o i_esimo duende
    return grupo_sem_i;
}

//Define o grupo de duendes com o i-esimo duende (i = n-1) em relacao ao grupo em analise
std::vector<int> GestaoDuendes::GrupoComDuende(const std::vector<int>& grupo_atual, int i_duende){
    std::vector<int> grupo_com_i;

    //Define conjunto de duendes pertencentes ao grupo que não conflitam com o i-esimo duende
    for (int d_atual : grupo_atual) {
        if (d_atual == i_duende) continue; 

        //Verifica conflito
        if (!grafo_duendes[i_duende][d_atual]) {
            grupo_com_i.push_back(d_atual); 
        }
    }
    
    //Retorna o grupo de duendes que podem trabalhar com i-esimo duende
    return grupo_com_i;
}

int GestaoDuendes::MenorLexicografico(const std::vector<int>& grupo1,const std::vector<int>& grupo2){
    
    //Verifica se o tamanho é igual
    int tamanho = int(grupo1.size());
    if(int(grupo2.size()) != tamanho){
        return -1;
    }

    //Percorre verificando qual é menor
    for (int i = 0; i < tamanho; ++i) {
        if (grupo1[i] < grupo2[i]) { // grupo1 menor que grupo2
            return 1;
        } else if (grupo1[i] > grupo2[i]) { // grupo2 menor que grupo1
            return 2;
        }
    }

    //São identicos
    return 0;
}

/*Funcoes que definem conjunto ---------------------------------------------*/

std::vector<int> GestaoDuendes::ArvoreDecisao(const std::vector<int>& grupo_atual, std::map<std::string, std::vector<int>>& registro_solucoes){

    //Verifica se esse porblema já foi resolvido
    std::string chave = DefineIdGrupo(grupo_atual);
    if (registro_solucoes.count(chave))     return registro_solucoes[chave];

    //Caso base:  se não houver nenhum elemento retorna conjunto vazio
    if (grupo_atual.empty())                return {};

    //Passo induitivo: define i
    int i_duende = grupo_atual.back(); 

    //Busca agrupamento sem o i-eesimo duende
    std::vector<int> solu_sem_i = GrupoSemDuende(grupo_atual);
    std::vector<int> grupo_sem_i = ArvoreDecisao(solu_sem_i, registro_solucoes);

    //Busca agrupamento com o i-eesimo duende
    std::vector<int> solu_com_i = GrupoComDuende(grupo_atual, i_duende); 
    std::vector<int> grupo_com_i = ArvoreDecisao(solu_com_i, registro_solucoes); 
    grupo_com_i.push_back(i_duende); 
    
    //Verifica se o grupo com ou sem o i-esimo duende maximiza o tamanho
    std::vector<int> maior_grupo;
    if(grupo_sem_i.size() > grupo_com_i.size()){
        maior_grupo = grupo_sem_i;

    }else if(grupo_sem_i.size() < grupo_com_i.size()){
        maior_grupo = grupo_com_i;

    }else{
        //Orderna os grupos
        std::sort(grupo_com_i.begin(), grupo_com_i.end()); 
        std::sort(grupo_sem_i.begin(), grupo_sem_i.end()); 

        //Verifica qual é menor lexicografiacemnete
        int menor_lex = MenorLexicografico(grupo_com_i, grupo_sem_i);
        if(menor_lex == 1){         maior_grupo = grupo_com_i;  }
        else if(menor_lex == 2){    maior_grupo = grupo_sem_i;  }
        else{                       maior_grupo = grupo_com_i;  }
    }
    
    //Orderna em relacao aos indices dos duendes
    std::sort(maior_grupo.begin(), maior_grupo.end());

    //Registra a solução encontrada
    registro_solucoes[chave] = maior_grupo;

    //Retorna o maior grupo
    return maior_grupo;
}

//Busca solução para melhor grupo nas metades e na interseccão dessas 
std::vector<int> GestaoDuendes::SelecaoDuendes(){
    //Define indice para cada metade
    int meio = n_duendes / 2;
    std::vector<int> metade_A;
    std::vector<int> metade_B;

    // Metade A: Duendes de 0 até (meio - 1)
    for (int i = 0; i < meio; i++) {            metade_A.push_back(i);}
    
    // Metade B: Duendes de 'meio' até (n_duendes - 1)
    for (int j = meio; j < n_duendes; j++) {    metade_B.push_back(j);}   

    //Maps para registros das solução já calculadas para cada metade
    std::map<std::string, std::vector<int>> resgit_soluc_B;
    
    //Chama função que define melhro solução para cada metade afim de registrar as soluçoes
    //já calculadas
    std::vector<std::vector<int>> todas_solucoes_A = GeraTodosGrupos(metade_A);
    ArvoreDecisao(metade_B, resgit_soluc_B); 

    //Registram o melhor grupo
    std::vector<int> melhor_grupo;
    int melhor_tamanho = 0;

    //Para todas solucoes registradas de A
    for (const auto& solucao_A : todas_solucoes_A) {
        
        //Verifica as solucoes compostas pelas interseccao dos conjuntos
        std::vector<int> interseccao;

        //Solucoes definidas pelo não conflitos enetre os elementos de cada metade
        //Para todo duende na metade B verifica se há conflito na solucao em A
        for (int duende_b : metade_B) {
            bool conflito = false;
            
            //Para os duendes na metade A que compoem solucao
            for (int duende_a : solucao_A) {
                //Verifica se há aresta entre o duende de a e de b
                if (grafo_duendes[duende_a][duende_b]) {
                    conflito = true;
                    break; // Quebra o loop sobre solucao_A
                }

                if (conflito) {
                    break;
                }
            }
            
            //Caso não haja conflito o elemento b pode ser adicionado a solucao de A
            if (!conflito) {
                interseccao.push_back(duende_b);
            }
        }
        
        //Busca melhor solucao para o conjunto de duendes de B que não conflitam com a solucao A atual
        //Como já foi registarda solucao para B essa busca na arvore e quase constante
        std::vector<int> solucao_B = ArvoreDecisao(interseccao, resgit_soluc_B);

        //O tamanho total é a soma dos duendes de A e B que não conflitam
        int tamanho_total = int(solucao_A.size() + solucao_B.size());

        std::vector<int> teste = solucao_A;
        teste.insert(teste.end(), solucao_B.begin(), solucao_B.end());

        //Verifica se encontrou a melhor solucao
        if (tamanho_total > melhor_tamanho) {
            //Caso encontrado define o melhor grupo como a interseccao
            melhor_grupo = solucao_A;
            melhor_grupo.insert(melhor_grupo.end(), solucao_B.begin(), solucao_B.end());
            
            melhor_tamanho = tamanho_total;

        }else if (tamanho_total == melhor_tamanho) {
            //Caso seja encontardo boas oslucoes com o mesmo tamanho 
            //Define a melhor como a com menor ordem lexicografica

            //Ordena o grupo candidato
            std::vector<int> candidato = solucao_A;
            candidato.insert(candidato.end(), solucao_B.begin(), solucao_B.end());
            std::sort(candidato.begin(), candidato.end()); 
            
            //Orderna o melhor grupo encontrado
            std::sort(melhor_grupo.begin(), melhor_grupo.end()); 

            //Verifica qual é menor lexicografiacemnete
            int menor_lex = MenorLexicografico(candidato, melhor_grupo);
            if(menor_lex == 1){         melhor_grupo = candidato;  }
            else if(menor_lex == 2){    melhor_grupo = melhor_grupo;  }
        }
    }
    
    //Retorna o melhor grupo
    std::sort(melhor_grupo.begin(), melhor_grupo.end());
    return melhor_grupo;
}

/*Funcoes que definem o todos os grupos possiveis do conjunto ---------------------------------------------*/
//Função que gera todos os grupos possiveis sem conflito de um conjunto
std::vector<std::vector<int>> GestaoDuendes::GeraTodosGrupos(const std::vector<int>& conjunto) {
    std::vector<std::vector<int>> grupos; //Armazena os grupos a serem gerados
    std::vector<int> subconjunto_atual;
    
    //Gera grupos com o i_duende para i = 0
    GeraGrupo(conjunto, 0, subconjunto_atual, grupos);
    
    return grupos;
}

//Função que gera todos os grupos sem conflito para o i_ésimo duende
void GestaoDuendes::GeraGrupo(const std::vector<int>& conjunto,int i_duende, std::vector<int>& subconjunto_atual,std::vector<std::vector<int>>& grupos) {
    
    //Caso que já foi gerado grupos para todos os duendes
    if (i_duende == int(conjunto.size())) {
        grupos.push_back(subconjunto_atual);
        return;
    }

    int duende_atual = conjunto[i_duende];

    bool conflito = false;
    //Verifica se há conflito no subconjunto
    for (int duende : subconjunto_atual) {
        
        //Verifica no grafo se ha aresta
        if (grafo_duendes[duende_atual][duende]) {
            conflito = true;
            break;
        }
    }

    //Caso não haja conflito
    if (!conflito) {
        //Gera grupos com o i_esimo duende incluso
        subconjunto_atual.push_back(duende_atual);
        GeraGrupo(conjunto, i_duende + 1, subconjunto_atual, grupos);
        subconjunto_atual.pop_back();
    }
    
    //Gera grupos com o i_esimo duende nao incluso
    GeraGrupo(conjunto, i_duende + 1, subconjunto_atual, grupos);
}