#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <memory>
#include "player.hpp"

#define FILE_PLAYERS_NAME "../src/players_list.txt"

class Player_Controller{
private:
    std::map<std::string, std::shared_ptr<Player>> players_list;
    //std::map<std::string, std::shared_ptr<Player>> players_in_match;

    /* Funções que nao devem ser acessadas pelos usuários */
    bool Add_Player_List(std::string _nickname, std::string _name);
    void Add_Player_File(std::string _nickname, std::string _name);

    bool Remove_Player_List(std::string nick);
    void Remove_Player_File(std::string nick);

public:
    Player_Controller();
    void Add_Player(std::string _name, std::string _nickname);
    void Remove_Player(std::string nick);
    std::shared_ptr<Player> Find_Player(std::string nick);
    void Show_Players_List();
    ~Player_Controller();
};
#endif