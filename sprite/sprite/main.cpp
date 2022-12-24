//
//  main.cpp
//  Sprite
//
//  Created by 叶子寻 on 24/12/2022.
//

#include <iostream>
#include "Game.hpp"

int main(int argc, const char * argv[]) {
    Game game;
    bool success = game.Initialize();
    
    if (success) {
        game.RunLoop();
    }
    
    game.ShutDown();
    return 0;
}
