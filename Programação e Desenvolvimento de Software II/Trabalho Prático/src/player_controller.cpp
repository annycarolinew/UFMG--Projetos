#include "player_controller.hpp"

Player_Controller::Player_Controller(){
    //std::cout << "Player_Controller criado" << std::endl;  
    std::ifstream file(FILE_PLAYERS_NAME, std::fstream::in);
    
    if(!file.is_open()){
        std::ofstream file(FILE_PLAYERS_NAME, std::ofstream::out);

        if(file.is_open()){
            std::cout << "Novo arquivo para o registro de jogadores criado com sucesso" << std::endl;
        }else{
            std::cout << "ERRO: nao foi possivel criar um novo arquivo para o registro de jogadores" << std::endl;
        }
        //Se o arquivo nao existia previamente, o construtor termina aqui
        file.close();
        return;
    }
        
    //falta: puxar estatisticas
    std::string line, _nickname, _name;
    while(getline(file, line)){

        std::stringstream ss(line);
        getline(ss, _nickname, '-');
        getline(ss, _name);
        
        this->Add_Player_List(_nickname, _name);
    }
    file.close();
};

bool Player_Controller::Add_Player_List(std::string _nickname, std::string _name){

    auto check = players_list.insert(std::pair<std::string, Player*>(_nickname, new Player(_nickname, _name)));
    
    if(check.second){
        return true;
    }else{
        std::cout << "Erro! Jogador " << _nickname << " ja existe" << std::endl;
        return false;
    }
}

void Player_Controller::Add_Player_File(std::string _nickname, std::string _name){
    
    std::ofstream arquivo(FILE_PLAYERS_NAME, std::ofstream::app);
    
    if(!arquivo.is_open()){
        std::cout << "Erro ao cadastrar" << std::endl;
        this->Remove_Player(_nickname);
        return;
    }

    arquivo << _nickname << "-" << _name << "\n";
    std::cout << "Jogador cadastrado com sucesso" << std::endl;
    arquivo.close();
}

bool Player_Controller::Remove_Player_List(std::string nick){
    
    auto it = players_list.find(nick);

    if (it == players_list.end()){
        std::cout << "Jogador nao encontrado" << std::endl;
        return false;
    }
    
    this->Remove_Player_File(nick);
    players_list.erase(it);
    
    std::cout << "Jogador " << nick << " deletado com sucesso" << std::endl;
    return true;
}

void Player_Controller::Remove_Player_File(std::string nick) {
    
    std::shared_ptr<Player> tmp_player = this->Find_Player(nick);

    if(tmp_player == nullptr){
        std::cout << "Player nao encontrado" << std::endl;
        return;
    }

    std::vector<std::string> lines_backup;
    std::string tmp = nick + "-" + tmp_player->Get_Name(); 

    std::ifstream file_write(FILE_PLAYERS_NAME, std::fstream::in);
    std::string line;
    while(getline(file_write, line)){
        if(line != tmp){
            lines_backup.push_back(line);
        }
    }
    file_write.close();

    std::ofstream file_read(FILE_PLAYERS_NAME, std::fstream::out);
    for (const auto& l : lines_backup) {
        file_read << l << std::endl;
    }
    file_read.close();
    std::cout << "Player " << nick << " removido" << std::endl; 
}

void Player_Controller::Add_Player(std::string _nickname, std::string _name){
    
    if(Add_Player_List(_nickname, _name)){
        Add_Player_File(_nickname, _name);
    }
}

void Player_Controller::Remove_Player(std::string nick){
    
    if(Remove_Player_List(nick)){
        Remove_Player_File(nick);
    }
}

std::shared_ptr<Player> Player_Controller::Find_Player(std::string nick){
    
    auto it = players_list.find(nick);
    std::cout << it->first << " - " << it->second << std::endl;
    return it->second;
}

void Player_Controller::Show_Players_List() {
    
    std::cout << "---------------------------" << std::endl;
    for (const auto& player : players_list) {
        std::cout << "Jogador: " << player.first << std::endl;
        player.second->Show_Player();
    }
    std::cout << "---------------------------" << std::endl;
}
Player_Controller::~Player_Controller(){
    
    players_list.clear();
    //std::cout << "Player_Controller destruido" << std::endl;
}
