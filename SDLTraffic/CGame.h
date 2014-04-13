//
//  CGame.h
//  SDLTraffic
//
//  Created by Emil Westholm on 2014-04-10.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __SDLTraffic__CGame__
#define __SDLTraffic__CGame__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include "CVehicleSprite.h"
#include "CEngine.h"

using namespace std;

class CGame
{
public:
    CGame();
    ~CGame();
    
    bool init(const char* title, int xpos, int ypos, int width, int height, bool  fullScreenMode);
    void render();
    void handleEvents();
    void update();
    void clean();
    bool isRunning();
    
    //Music
    void startBackgroundMusic();
    void stopBackgroundMusic();
    
    //Game engine init
    void initTrafficEngine(int width, int height, bool fullScreen);
    
    
    //Engine wrapper methods
    void addVehicle(float x, float y, int id, Color color);
    void moveVehicle(float x, float y, int id);
    void removeVehicle(int id);
    void renderAllVehicles();
    void updateAllVehicles();
    void gameOver();
    void mouseButtonDownAtPosition(float x, float y);
    void mouseButtonUpAtPosition(float x, float y);
    void mouseButtonDownAndMoving(float x, float y);
    
private:
    int m_selectedVehicle = 0;
    bool m_bRunning = false;
    SDL_Window* m_pWindow = 0;
    SDL_Renderer* m_pRenderer = 0;
    
    SDL_Texture* m_pTexture;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;
    
    Mix_Music* m_pMusic;
    
    vector<CVehicleSprite> m_vehicles;
    
    void log(string message);
    
    CEngine* m_pEngine;
    
    
    CVehicleSprite* tempVehicle;
    
    

};

#endif /* defined(__SDLTraffic__CGame__) */
