//
//  CTrafficEnginePlugin.cpp
//  SDLTraffic
//
//  Created by Emil Westholm on 2014-04-11.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CTrafficEnginePlugin.h"



void CTrafficEnginePlugin::PostUpdateVehicle(CVehicle* vehicle)
{
    game->moveVehicle(vehicle->Position->getX(), vehicle->Position->getY(), vehicle->getID());
}

void CTrafficEnginePlugin::PostNewVehicle(CVehicle* vehicle)
{
    game->addVehicle(vehicle->Position->getX(), vehicle->Position->getY(), vehicle->getID(), vehicle->Color);
}

void CTrafficEnginePlugin::PostRemoveVehicle(int id)
{
    game->removeVehicle(id);
}

void CTrafficEnginePlugin::PreUpdateVehicle(CVehicle* vehicle)
{
    //Do nothing
}

void CTrafficEnginePlugin::GameOver(GameOverReason reason)
{
    game->gameOver();
}