#include "player.hpp"

Player::Player(std::string _nickname, std::string _name) 
    : nickname(_nickname), name(_name) {
        //std::cout << "Jogador " << _nickname << " construído" << std::endl;
    }

/* --- Gettes and Setters --- */

std::string Player::Get_Name(){ return this->name; }
std::string Player::Get_Nickname(){ return this->nickname; }
int Player::Get_Team(){ return this->team; }

void Player::Set_Team(int _team){ this->team = _team; }

/* ----------- // ----------- */

/*void Player::End_Match(int result) {
        if (result == VICTORIES){
            this->stats.victories++;
        }else if (result == DEFEATS){
            this->stats.defeats++;
        }else{
            this->stats.draws++;
        }
    }*/

void Player::Show_Player() {
    std::cout << "Nome: " << this->name << std::endl;
}

Player::~Player(){
    //std::cout << "Jogador " << nickname << " destruido" << std::endl;
}
