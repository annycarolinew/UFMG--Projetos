#include "game_controller.hpp"

/*Game_Controller*/
Game_Controller::Game_Controller(Game *_game, std::vector<Player*> players)
    : managed_game(_game), turn_counter(0){
    
    int size = players.size();
    for(int i = 0; i < size; i++){
        ingame_players.push_back(players[i]); 
        ingame_players[i]->Set_Team(i);
        //managed_game->Initialize_Pieces(players[i]);
    }
};

//controlando o turno por (turn % ingame_players[size])
//consegue-se inserir mais players caso haja essa vontade
bool Game_Controller::Game_Loop(){

    Player *current_player = ingame_players[turn_counter % ingame_players.size()];
    std::cout << "Current player:" << current_player->Get_Name() << " ";
    std::cout << turn_counter << " --- " << turn_counter % ingame_players.size()<< std::endl;

    //int x, y; //Nick - pra que serve?
    managed_game->Player_Input(current_player);

    this->turn_counter++;
    return 1;
};

Game *Game_Controller::Get_Game(){
    return this->managed_game;
};

int Game_Controller::Get_Turn_Counter(){
    return this->turn_counter;
};

Game_Controller::~Game_Controller(){};