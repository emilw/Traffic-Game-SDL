//
//  main.cpp
//  SDLTraffic
//
//  Created by Emil Westholm on 2014-04-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include <iostream>
#include "CGame.h"

using namespace std;

CGame* g_pGame;

int main(int argc, const char * argv[])
{
    g_pGame = new CGame();
    
    
    
    //320, 480 - 640, 480
    if(!g_pGame->init("Chapter 1 test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 480, false))
    {
        return 1;
    }
    
    if(SDL_WasInit(SDL_INIT_AUDIO))
        cout << "Audio is initialized" << std::endl;
    
    while(g_pGame->isRunning())
    {
        g_pGame->handleEvents();
        g_pGame->update();
        g_pGame->render();
    }
    
    g_pGame->clean();
    
    return 0;
}

