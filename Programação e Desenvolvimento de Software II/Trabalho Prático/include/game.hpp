#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "player.hpp"
#include "tabletop.hpp"
#include "piece.hpp"

class Game{
private:
    Tabletop *table;
    std::vector<std::vector<Piece*>> ingame_pieces;
    
public:
    Game(int sizeX, int sizeY);
    Game(int SIZE);
    //virtual void Initialize_Pieces(Player *from_player); 

    std::vector<Piece*> Get_Player_Pieces(Player *from_player);
    Tabletop *Get_Table();

    //virtual bool Is_Play_Valid() = 0;
    virtual void Player_Input(Player *current_player);

    virtual ~Game();
    virtual bool Victory_Condition() = 0; 
};
#endif