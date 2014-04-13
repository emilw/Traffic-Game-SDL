//
//  CGame.cpp
//  SDLTraffic
//
//  Created by Emil Westholm on 2014-04-10.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CGame.h"
#include "CTrafficEnginePlugin.h"

CGame::CGame()
{
    m_bRunning = false;
}

CGame::~CGame()
{
    
}

void CGame::log(string message)
{
    cout << "CGame::log: " + message << endl;
}

void CGame::initTrafficEngine(int width, int height, bool fullScreen)
{
    CTrafficEnginePlugin* plugin = new CTrafficEnginePlugin(this);
    //CEnginePlugin* plugin = new CEnginePlugin(this);
    
    m_pEngine = new CEngine(nullptr,plugin,width, height);
    m_pEngine->GetNewLane(Color::BLUE, 90);
    m_pEngine->GetNewLane(Color::RED, 160);
    m_pEngine->GetNewLane(Color::GREEN, 230);
    
    //this->addVehicle(0, 0, 1);
    //tempVehicle = new CVehicleSprite(m_pRenderer);
    //this->addVehicle(0, 0);
    m_pEngine->StartGame();
    
    //m_pEngine->StartNewVehicle(m_pEngine->GetLane(1));
}

bool CGame::init(const char *title, int xpos, int ypos, int width, int height, bool fullScreenMode)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        int flags = SDL_WINDOW_SHOWN;
        
        if(fullScreenMode)
            flags = SDL_WINDOW_FULLSCREEN;
        
        this->log("SDL is initialized");
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        
        if(m_pWindow != 0)
        {
            log("Window creation went ok!");
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            
            if(m_pRenderer != 0)
            {
                log("Renderer creation went ok!");
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
            }
            else
            {
                log("Failed to create Renderer");
                return false;
            }
        }
        else
        {
            log("Failed to create Window");
            return false;
        }
    }
    else
    {
        log("Could not initialize SDL");
        return false;
    }
    
    log("Init was successful");
    
    m_bRunning = true;
    
    
    //Temporary background binding
    
    //Get the image from disk
    //SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/Images/Road.bmp");
    SDL_Surface* pTempSurface = IMG_Load("Assets/Images/Road.png");
    //Get a pointer to the image
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    //Clean the surface and release un used memory
    SDL_FreeSurface(pTempSurface);
    
    //Get the dimensions from the image
    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
    
    //Set the destination rectangle to the same width and heigth as the image
    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;
    
    m_destinationRectangle.w = width;
    m_destinationRectangle.h = height;

    initTrafficEngine(width, height, fullScreenMode);
    
    return true;
}

void CGame::startBackgroundMusic()
{
    /*m_pMusic = Mix_LoadMUS("/Assets/Audio/MusicTrack.mp3");
    
    if(m_pMusic == 0)
    {
        log("Could not load the music track");
    }*/
    
    //Mix_PlayMusic(m_pMusic, 2);
    
}

void CGame::addVehicle(float x, float y, int id, Color color)
{
    CVehicleSprite sprite(m_pRenderer, id, color);
    sprite.move(x, y);
    m_vehicles.push_back(sprite);
}

void CGame::moveVehicle(float x, float y, int id)
{
    vector<CVehicleSprite>::iterator it = m_vehicles.begin();
    
    for(;it != m_vehicles.end(); it++)
    {
        if(it->Id == id)
        {
            it->move(x, y);
            break;
        }
    }
}

void CGame::removeVehicle(int id)
{
    vector<CVehicleSprite>::iterator it = m_vehicles.begin();
    
    for(;it != m_vehicles.end(); it++)
    {
        if(it->Id == id)
        {
            m_vehicles.erase(it);
            break;
        }
    }

}

void CGame::renderAllVehicles()
{
    vector<CVehicleSprite>::iterator it = m_vehicles.begin();
    
    for(;it != m_vehicles.end(); it++)
    {
        it->render(m_pRenderer);
    }
}

void CGame::render()
{
    //Set Alpha as color value
    //SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    
    //SDL_Load
    //This code should be restructured and checked against the tutorial again
    
    //Clear the window to black
    SDL_RenderClear(m_pRenderer);
    
    //Render the background
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    //tempVehicle->render(m_pRenderer);
    renderAllVehicles();
    
    //Show window
    SDL_RenderPresent(m_pRenderer);
}

void CGame::handleEvents()
{
    SDL_Event event;
    
    if(SDL_PollEvent(&event))
    {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;
            case SDL_KEYDOWN:
                log(SDL_GetKeyName(event.key.keysym.sym));
                log(to_string(event.key.keysym.sym));
                
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    log("Escape key pressed, closing the game");
                    m_bRunning = false;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                log("Mouse button down");
                log("x/y:(" + to_string(event.motion.x) + "/" + to_string(event.motion.y));
                mouseButtonDownAtPosition(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONUP:
                log("Mouse button upp");
                log("x/y:(" + to_string(event.motion.x) + "/" + to_string(event.motion.y));
                mouseButtonUpAtPosition(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEMOTION:
                log("Mouse is moving");
                if(m_selectedVehicle != 0)
                {
                    mouseButtonDownAndMoving(event.motion.x, event.motion.y);
                    log("Dragging vehicle");
                }
                break;
            default:
                break;
        }
    }
}

void CGame::mouseButtonDownAndMoving(float x, float y)
{
    //moveVehicle(x, y, m_selectedVehicle);
    m_pEngine->MoveVehicle(x, y, m_pEngine->GetVehicle(m_selectedVehicle));
}

void CGame::mouseButtonDownAtPosition(float x, float y)
{
    m_selectedVehicle = 0;
    m_selectedVehicle = ((CVehicle*)m_pEngine->GetVehicleForPosition(x, y))->getID();
    if(m_selectedVehicle != 0)
    {
        log("Clicked on vehicle " + to_string(m_selectedVehicle));
        //m_pSelectedVehicle = vehicle;
    }
}

void CGame::mouseButtonUpAtPosition(float x, float y)
{
    if(m_selectedVehicle != 0)
    {
        m_pEngine->MoveVehicle(x, y, m_pEngine->GetVehicle(m_selectedVehicle));
        m_selectedVehicle = 0;
    }
}


void CGame::gameOver()
{
    //m_bRunning = false;
}

void CGame::clean()
{
    
    log("Cleaning up after closed game");
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void CGame::update()
{
    //this->moveVehicle(300, 10, 1);
    //CVehicle* vehicle = new CVehicle(1, Color::GREEN, 10, 10);
    //m_pEngine->AddVehicle(vehicle);
    m_pEngine->Update();
}

bool CGame::isRunning()
{
    return m_bRunning;
}
