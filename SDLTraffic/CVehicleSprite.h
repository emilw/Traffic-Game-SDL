//
//  CVehicleSprite.h
//  SDLTraffic
//
//  Created by Emil Westholm on 2014-04-11.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __SDLTraffic__CVehicleSprite__
#define __SDLTraffic__CVehicleSprite__

#include <iostream>
#include <SDL2/SDL.h>
#include <CEngine.h>
#include <SDL2_image/SDL_image.h>

class CVehicleSprite
{
public:
    CVehicleSprite(SDL_Renderer* renderer, int id, Color color);
    void render(SDL_Renderer* renderer);
    void move(float x, float y);
    int Id;
private:
    SDL_Texture* m_pTexture;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;
};

#endif /* defined(__SDLTraffic__CVehicleSprite__) */
