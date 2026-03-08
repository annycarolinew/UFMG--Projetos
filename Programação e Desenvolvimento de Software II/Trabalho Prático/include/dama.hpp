#ifndef DAMA_H
#define DAMA_H

#include <memory>

#include "game.hpp"
#include "player.hpp"
#include "piece.hpp"

#define MAX_PIECES 36
#define BLACK 'B'
#define WHITE 'W'

class Dama : public Game{
    private:
        Player* player1;
        Player* player2;

    public:
        //Constructor
        Dama (int size, Player* player1, Player* player2);

        //Derived class
        void Initialize_Game();
        void Player_Input(Player* current_player) override;
        bool Victory_Condition() override;
        
        //Game
        void Valid_movement(int line_piece, int column_piece, int line_path, int column_path, Player* owner);
        Piece* Game_define_piece(Player* owner, char table_char);
        void Input_piece(int line, int column,Player* owner);
        int Who_wins();
        char Owner_color(Player* _player);

        bool Peon_movement(int line, int column);
        bool Peon_attack(int line, int column,Player* owner, char diagonal);

        bool Queen_movement(int line, int column, int distance, Player* owner, char diagonal);

        std::array<int, 2> Find_piece(int line_piece, int column_piece, int line_path, int column_path, Player* owner, int distance);
        bool Movement_rules(int line_piece, int column_piece, int line_destination, int column_destination, Player* owner);
        bool Move_piece(int line_piece, int column_piece, int line_destination, int column_destination);
        bool Remove_piece(int line_piece, int column_piece);

        //Desconstructor
        ~Dama() override;
};

#endif