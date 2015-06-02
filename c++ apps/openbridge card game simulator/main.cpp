#include <iostream>

#include "Game.h"

using namespace std;

int main()
{

    Game game;





    game.setup(false);
    game.deal();
    cout << game;



    return 0;

}
