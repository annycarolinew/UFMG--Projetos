#include <iostream>
#include <fstream>
#include <sstream>
#include "manager.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    //Verifica se o usuário passou algum valor
    if (argc < 2) {
        cout << "Nenhum arquivo foi adicionado\n";
        return 1;
    }

    //Abre o arquivo passado pelo usuario
    string caminhoArquivo = argv[1];    
    ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << caminhoArquivo << "\n";
        return 1;
    }


    //Cria o gerenciador de eventos
    Manager manager;

    //Iniciliza
    string linha;
    while (getline(arquivo, linha)) {
        istringstream iss(linha);

        int tempo;
        string tipo_linha;

        iss >> tempo >> tipo_linha;

        if (tipo_linha == "EV") {
            string tipo_evento;
            iss >> tipo_evento;

            int id_pct;
            iss >> id_pct;

            if (tipo_evento == "RG") {
                string remetente, destinatario;
                int arm_origem, arm_destino;
                iss >> remetente >> destinatario >> arm_origem >> arm_destino;

                Evento evt (tempo, tipo_evento, id_pct, arm_destino,arm_origem, remetente,destinatario);
                manager.AddEvento(evt);
            }
            else if (tipo_evento == "AR" || tipo_evento == "RM" || tipo_evento == "UR" || tipo_evento == "TR") {
                int arm_atual, arm_destino;
                iss >> arm_atual >> arm_destino;

                Evento evt (tempo, tipo_evento, id_pct, arm_destino, arm_atual);
                manager.AddEvento(evt);
            }

            else if (tipo_evento == "EN") {
                int arm_destino;
                iss >> arm_destino;

                Evento evt (tempo, tipo_evento, id_pct, arm_destino);
                manager.AddEvento(evt);
            }
        }else{
            std::ostringstream oss;
            oss <<  std::setw(6) << std::setfill('0') << tempo << " " << tipo_linha;

            
            if (tipo_linha == "CL") {
                
                string nome_cliente;
                iss >> nome_cliente;
                
                cout << oss.str() << " " << nome_cliente << endl;
                manager.ConsultaCliente(tempo, nome_cliente);
            }
            else if (tipo_linha == "PC") {
                int id_pacote;
                iss >> id_pacote;

                cout << oss.str() << " " << std::setw(3) << std::setfill('0') <<id_pacote << endl;
                manager.ConsultaPacote(tempo, id_pacote);
            }
        }
    }


    return 0;
}