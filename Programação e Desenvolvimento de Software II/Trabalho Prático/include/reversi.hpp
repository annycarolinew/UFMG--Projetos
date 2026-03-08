#ifndef REVERSI_H
#define REVERSI_H

#include <memory>

#include "game.hpp"
#include "player.hpp"
#include "piece.hpp"

#define MAX_PIECES 64
#define BLACK 'B'
#define WHITE 'W'

class Reversi : public Game{
    private:
        Player* player1;
        Player* player2;

        std::vector<Piece*> ingame_pieces;
    public:
        //Constructor
        Reversi (int size, Player* player1, Player* player2);

        //Derived class
        void Initialize_Game();
        void Player_Input(Player* current_player) override;
        bool Victory_Condition() override;
        
        //Possible movements
        /* add smart pointer all functions*/
        std::array<int, 2> Find_piece_in_direction(int line_piece, int column_piece, int line_path, int column_path, Player* owner);
        bool Swap_piece_in_direction(int line_piece, int column_piece, std::array<int, 2> posc, int line_path, int column_path, Player* owner);

        //Game
        void Valid_movement(int line_piece, int column_piece, int line_path, int column_path, Player* owner);
        Piece* Game_define_piece(int piece_line, int piece_column, Player* owner, char table_char);
        bool Game_swap_piece(int line, int column);
        char Owner_color(Player* _player);
        void Input_piece(int line, int column,Player* owner);
        int Who_wins();
        //Desconstructor
        ~Reversi() override;
};

#endif