//
//  CVehicleSprite.cpp
//  SDLTraffic
//
//  Created by Emil Westholm on 2014-04-11.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CVehicleSprite.h"


CVehicleSprite::CVehicleSprite(SDL_Renderer* renderer, int id, Color color)
{
    string carImage;
    
    switch (color) {
        case Color::RED:
            carImage = "RedCar";
            break;
        case Color::BLUE:
            carImage = "BlueCar";
            break;
        case Color::GREEN:
            carImage = "GreenCar";
            break;
        default:
            break;
    }
    
    string path = "Assets/Images/" + carImage + ".png";
    //Get the image from disk
    SDL_Surface* pTempSurface = IMG_Load(path.c_str());
    //Get a pointer to the image
    m_pTexture = SDL_CreateTextureFromSurface(renderer, pTempSurface);
    //Clean the surface and release un used memory
    //SDL_FreeSurface(pTempSurface);
    
    //Get the dimensions from the image
    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
    
    //Set the destination rectangle to the same width and heigth as the image
    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;
    Id = id;
    
    //m_destinationRectangle.w = width;
    //m_destinationRectangle.h = height;
}

void CVehicleSprite::move(float x, float y)
{
    m_destinationRectangle.x = x-(m_destinationRectangle.w/2);
    m_destinationRectangle.y = y-(m_destinationRectangle.h/2);
}

void CVehicleSprite::render(SDL_Renderer* renderer)
{
    //Render the background
    SDL_RenderCopy(renderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
}