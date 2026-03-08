#include <iostream>
#include <string>
#include <fstream>
#include "../include/gestaoDuendes.hpp"

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

    int n_duendes, m_conflitos;
    *entrada >> n_duendes >> m_conflitos;
    GestaoDuendes duendes(n_duendes, m_conflitos);

    int i_duende, j_duende;
    for(int i = 0; i < m_conflitos; i++){
        *entrada >> i_duende >> j_duende;
        duendes.InsereConflito(i_duende,j_duende);
    }

    int contador = 0;
    std::vector<int> maior_grupo = duendes.SelecaoDuendes();
    std::cout << maior_grupo.size() << "\n";
    for(int indice_duende : maior_grupo){
        std::cout << indice_duende;

        if(contador < int(maior_grupo.size())){      std::cout << " ";
        }else{                                  std::cout << "\n";}

        contador++;
    }
    
    return 0;
}