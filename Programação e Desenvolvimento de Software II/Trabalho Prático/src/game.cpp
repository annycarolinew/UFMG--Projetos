#include "game.hpp"

/*Game*/
Game::Game(int sizeX, int sizeY){
    
    table = new Tabletop(sizeX, sizeY);   
    std::cout << "construtor do jogo foi chamado\n";
}
//Relaciona a posição de turno, paralelo ao vetor de ingame_players
//Método virtual, pode ser modificado de acordo com o tipo das peças e das necessidades do jogo
/*void Game::Initialize_Pieces(Player *from_player){

    ingame_pieces.emplace_back();                 
    ingame_pieces.back().push_back(new Piece(1, from_player->Get_Nickname()[0], from_player));
    //Ex.jogo da velha: a peça do p1 é incializada com new piece(1, from_player, 'o')
    // e o p2 new piece(1, from_player, 'x')
};
 
std::vector<Piece*> Game::Get_Player_Pieces(Player *from_player){
    return ingame_pieces[from_player->Get_Team()];
};*/

Game::Game(int SIZE):Game(SIZE,SIZE){};

Game::~Game(){
    std::cout << "destrutor chamado\n";
}

Tabletop *Game::Get_Table(){
    return this->table;
};

//void game::Victory_Condition() não precisa ser definido aqui pois a intenção é a função ser abstrata
//já que não faz sentido criar um victory condition pra nenhum jogo

//Precisa ser virtual, pois o input pode ser diferente, como no lig4, que só espera uma coluna
void Game::Player_Input(Player *current_player){ 
    
    int X, Y;
    std::cin >> X >> Y;
    
    //por padrão, a peça jogada é a de índice 0 pois só existe um tipo de peça de player, mas em jogos
    //que possuem mais peças, uma lógica deve ser implementada para saber qual peça está sendo posicionada ou movida.
    //table->Set_Piece(X-1, Y-1, ingame_pieces[current_player->Get_Team()][0]);
};
