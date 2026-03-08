#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <string>
#include "game_controller.hpp"
#include "player_controller.hpp"

#define SUCESSO 0

class Manager{
private:
    Player_Controller player_contr;
public:
    Manager();
    ~Manager();
};
#endif