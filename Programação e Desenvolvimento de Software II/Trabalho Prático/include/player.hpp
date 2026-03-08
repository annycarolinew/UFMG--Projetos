#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "statistics.hpp"

#define VICTORY 1
#define DRAW 0
#define DEFEAT -1

class Player{
private:
    std::string nickname, name;
    //vector<std::shared_ptr<statistics>> stats;
    int team;

public:
    Player(std::string _nickname, std::string _name);
    
    void Set_Team(int _team);
    std::string Get_Nickname();
    std::string Get_Name();
    
    int Get_Team();
    //void End_Match(int result);

    void Show_Player();
    ~Player();
};
#endif