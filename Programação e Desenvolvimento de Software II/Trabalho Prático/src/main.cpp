#include <iostream>
#include <string>
#include "game_controller.hpp"
#include "player_controller.hpp"
#include "reversi.hpp"

#define SUCESSO 0

int main(){
    
    int i;

    std::vector<Player*> test_players;
    
    test_players.push_back(new Player("tulhao77", "Tulio Faustino"));   // Esses players são placeholders para poder testar se as baseClasses conseguem rodar o jogo.
    test_players.push_back(new Player("enzoVII", "Enzo Romano"));

    std::cout << "O jogo sendo jogado eh o padrao\n" << "escolha o tamanho quadrado do tabuleiro de testes\n";

    std::cin >> i;
    Game *test_game = new Reversi(8, test_players[0], test_players[1]);

    Game_Controller test_menager = Game_Controller(test_game, test_players);

    
    std::cout << "QA " <<std::endl;
    // test_game.getTable()->setValue(0, 0, 5);
    // std::cout << test_game.getTable()->getValue(2, 3) << std::endl;
    // 

    for(int i = 0; i < 25; i++){
        test_menager.Game_Loop();
        test_menager.Get_Game()->Get_Table()->Table_Print();
    }

    return SUCESSO;
}