/* bzflag-model-writer
 * Copyright (c) 2021 Scott Wichser
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named LICENSE.md that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "TankGeometryMgr.h"
#include "glwriter.h"

enum TeamColor
{
    RogueTeam = 0,
    RedTeam = 1,
    GreenTeam = 2,
    BlueTeam = 3,
    PurpleTeam = 4,
    ObserverTeam = 5,
    RabbitTeam = 6,
    HunterTeam = 7
};

static float           tankColors[8][3] =
{
    { 1.0f, 1.0f, 0.0f },   // rogue
    { 1.0f, 0.0f, 0.0f },   // red
    { 0.0f, 1.0f, 0.0f },   // green
    { 0.1f, 0.2f, 1.0f },   // blue
    { 1.0f, 0.0f, 1.0f },   // purple
    { 1.0f, 1.0f, 1.0f },   // observer
    { 0.8f, 0.8f, 0.8f },   // rabbit
    { 1.0f, 0.5f, 0.0f }    // hunter orange
};


int main()
{
    // Enable textures
    bool textured = true;

    // Pick a team, any team
    TeamColor team = RedTeam;

    // Convert that team to a string
    std::string teamString;
    switch(team)
    {
    case RedTeam:
        teamString = "red";
        break;
    case GreenTeam:
        teamString = "green";
        break;
    case BlueTeam:
        teamString = "blue";
        break;
    case PurpleTeam:
        teamString = "purple";
        break;
    case ObserverTeam:
        teamString = "observer";
        break;
    case RabbitTeam:
        teamString = "rabbit";
        break;
    case HunterTeam:
        teamString = "hunter";
        break;
    default:
        teamString = "rogue";
        break;
    }

    float color[3] = { tankColors[team][0], tankColors[team][1], tankColors[team][2] };

    // do not use color modulation with tank textures
    if (textured)
        color[0] = color[1] = color[2] = 1.0f;

    // Create materials
    MaterialInfo body, barrel, turret, casing, tread, wheel;
    int i;

    // Body material
    for (i = 0; i <= 2; ++i)
        body.diffuse[i] = color[i];
    if (textured)
        body.diffuseTexture = "data/" + teamString + "_tank.png";

    // Barrel material
    for (i = 0; i <= 2; ++i)
        barrel.diffuse[i] = 0.25f;

    // Turret material
    for (i = 0; i <= 2; ++i)
        turret.diffuse[i] = 0.9f * color[i];
    if (textured)
        turret.diffuseTexture = "data/" + teamString + "_tank.png";

    // (Tread) casing material
    for (i = 0; i <= 2; ++i)
        casing.diffuse[i] = 0.7f * color[i];
    if (textured)
        casing.diffuseTexture = "data/" + teamString + "_tank.png";

    // Tread material
    for (i = 0; i <= 2; ++i)
        tread.diffuse[i] = 0.3f * color[i];
    if (textured)
        tread.diffuseTexture = "data/treads.png";

    // Wheel material
    for (i = 0; i <= 2; ++i)
        wheel.diffuse[i] = 0.4f * color[i];
    if (textured)
        wheel.diffuseTexture = "data/" + teamString + "_tank.png";


    // Add our materials
    glWriterAddMaterial("body", body);
    glWriterAddMaterial("barrel", barrel);
    glWriterAddMaterial("turret", turret);
    glWriterAddMaterial("casing", casing);
    glWriterAddMaterial("tread", tread);
    glWriterAddMaterial("wheel", wheel);

    // Build all the tank sizes
    TankGeometryMgr::init();
    TankGeometryMgr::buildLists();
    TankGeometryMgr::kill();

    return 0;
}
