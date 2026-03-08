#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include <vector>
#include "game.hpp"

class Game_Controller{
private:
    Game *managed_game;
    std::vector<Player*> ingame_players;
    int turn_counter;
    Player *victor;

public:
    Game_Controller(Game *_game, std::vector<Player*> players);
    bool Game_Loop();

    Game *Get_Game();
    int Get_Turn_Counter();
    ~Game_Controller();
};
#endif