//
//  CTrafficEnginePlugin.h
//  SDLTraffic
//
//  Created by Emil Westholm on 2014-04-11.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __SDLTraffic__CTrafficEnginePlugin__
#define __SDLTraffic__CTrafficEnginePlugin__

#include <iostream>
#include <CEngine.h>
#include "CGame.h"
class CTrafficEnginePlugin: public CEnginePlugin
{
public:
    CGame* game;
    CTrafficEnginePlugin(void* game): CEnginePlugin(game)
    {
        this->game = (CGame*)game;
    };
    
    void PostUpdateVehicle(CVehicle* vehicle);
    void PostNewVehicle(CVehicle* vehicle);
    void PostRemoveVehicle(int id);
    void PreUpdateVehicle(CVehicle* vehicle);
    void GameOver(GameOverReason reason);
};

#endif /* defined(__SDLTraffic__CTrafficEnginePlugin__) */
