#include <cmath>
#include <algorithm>
#include "dama.hpp"
#include "game.hpp"

Dama::Dama(int size, Player* _player1, Player* _player2)
:Game(size), player1(_player1), player2(_player2){ this->Initialize_Game(); }

Piece* Dama :: Game_define_piece(Player* owner, char print_c){
    /*add smart pointer*/
    int index = 1;

    if(owner == this->player2){
        index = 2;
    }
    this->Get_Player_Pieces(owner).push_back(new Piece(0, print_c, owner));
    return this->Get_Player_Pieces(owner).back();
}

char Dama :: Owner_color(Player* _player){
    if(_player == this->player1){
        return WHITE;
    }

    return BLACK;
}

void Dama :: Valid_movement(int line, int column, int line_path, int column_path, Player* owner){


}

void Dama :: Player_Input(Player* owner){
    
}

void Dama :: Input_piece(int line, int column, Player* current_player){
    this->Get_Table()->Set_Piece(line, column, Game_define_piece(current_player, this->Owner_color(current_player)));
}

void Dama :: Initialize_Game(){
    /* Dama starts with two pieces for each 
       player in the center of the board   */

    int n_pieces = 12;
    int line = 3;
    int column = 4;

    for(int i = 0; i < line; i++){
        for(int j = 0; j < column; i++){
            Input_piece(i, j * 2, this->player1);
            Input_piece((this->Get_Table()->Get_SizeX() - 1) - i, j + 1, this->player2);
        }
    }
    
    this->Get_Table()->Table_Print();
}

/*End Game*/

Dama :: ~Dama(){
    std::cout << "desconstrutor";
}

bool Dama :: Victory_Condition(){
    int player1_pieces;
    int player2_pieces;

    for (const auto& piece : this->Get_Player_Pieces(player1)) {
        if(piece->Get_Char() == WHITE){
            player1_pieces++;
        }
    }

    for (const auto& piece : this->Get_Player_Pieces(player2)) {
        if(piece->Get_Char() == BLACK){
            player2_pieces++;
        }
    }

    if(player1_pieces > 0 || player2_pieces > 0){
        return false;
    }

     if(player1_pieces > player2_pieces){
        /* player 1 wins*/
    }else if(player1_pieces < player2_pieces){
        /* player 2 wins*/
    }

    return true;
}


/* Movement*/

std::array<int, 2> Dama::Find_piece(int line_piece, int column_piece, int line_path, int column_path, Player* owner, int distance) {
    int brother_line = line_piece;
    int brother_column = column_piece;
    
    do{
        brother_line += line_path;
        brother_column += column_path;
        
        Piece* p = this->Get_Table()->Get_Piece(brother_line , brother_column);
        if (p && std::max(abs(line_piece - brother_line), abs(column_piece - brother_column)) <= distance) {
            return {brother_line, brother_column};
        }

    }while( brother_line > 0 && brother_line < this->Get_Table()->Get_SizeX() - 1 && 
            brother_column > 0 && brother_column < this->Get_Table()->Get_SizeY() - 1);

    return {-1,-1};
}

bool Dama::Movement_rules(int line_piece, int column_piece, int line_destination, int column_destination, Player* owner){

    Piece* p = this->Get_Table()->Get_Piece(line_piece, column_piece);
    //Peon
    if(p->Get_Type() == 0){
        if(column_piece - column_destination == 0 && abs(line_piece - line_destination) == 1){
            this->Peon_movement(line_piece,column_piece);
            
        }else{
            int diference = abs(line_piece - line_destination);
            if(diference == 2){
                if(column_piece - diference == column_destination){
                    //diagonal secondary
                    this->Peon_attack(line_piece,column_piece,p->Get_Owner(), 's');
                }else if(column_piece + diference == column_destination){
                    //diagonal principal
                    this->Peon_attack(line_piece,column_piece,p->Get_Owner(), 'p');
                }
            }
        }
    }

    if(p->Get_Type() == 1){
        int diference = line_piece - line_destination;
        if(column_piece - diference == column_destination){
            //diagonal secondary
            this->Queen_movement(line_piece,column_piece, diference, p->Get_Owner(), 's');
        }else if(column_piece + diference == column_destination){
            //diagonal principal
            this->Queen_movement(line_piece,column_piece, diference, p->Get_Owner(), 'p');
        }
    }
}

bool Dama:: Move_piece(int line, int column, int line_distance, int column_distance){
    bool valid_move = false;
    Piece *p = this->Get_Table()->Get_Piece(line + line_distance, column + column_distance);

    if(p && p->Get_Owner() != player1 && p->Get_Owner() != player2){
        valid_move = true;

        Piece* piece_actual = this->Get_Table()->Get_Piece(line, column);
        this->Get_Table()->Set_Piece(line + line_distance, column + column_distance, piece_actual /*colocar o smart pointer que faz copia*/);
        this->Get_Table()->Set_Piece(line, column, new Piece(0, ' ', nullptr));
    } 

    return valid_move;
}

bool Dama:: Remove_piece(int line, int column){
    Piece* p = this->Get_Table()->Get_Piece(line, column);
    if(p && p->Get_Char() != Owner_color(p->Get_Owner()) && p->Get_Char() != ' '){
        p->Set_Owner(nullptr);
        p->Set_Char(' ');

        return true;
    }

    return false;
}

bool Dama :: Peon_movement(int line, int column){
    return Move_piece(line, column, 1, 0);

}

bool Dama :: Peon_attack(int line, int column, Player* owner, char diagonal){
    int line_path, column_path;

    if(diagonal == 'p'){
        line_path = 1;
        column_path = 1;
    }else if(diagonal == 's'){
        line_path = 1;
        column_path = -1;
    }
    
    if(this->Move_piece(line, column, 2*line_path, 2*column_path)){
       return Remove_piece(line + line_path, column + column_path);
    } 

    return false;
}

bool Dama :: Queen_movement(int line, int column, int distance, Player* owner, char diagonal){
    std::array<int, 2> posc;
    int line_path, column_path;

    if(diagonal == 'p'){
        line_path = 1;
        column_path = 1;
    }else if(diagonal == 's'){
        line_path = 1;
        column_path = -1;
    }
    
    Piece *piece_destination = this->Get_Table()->Get_Piece(line + distance*line_path, column + distance*column_path);

    if(piece_destination){
        return false;
    }else{

        if(Move_piece(line, column, distance*line_path, distance*column_path)){
            posc = this->Find_piece(line, column, line_path,column_path, owner, distance);
            
            if(posc[0] > 1){
                Remove_piece(posc[0],posc[1]);
            }

            return true;
        }
    }
    return false;
}
