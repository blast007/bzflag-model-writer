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

#include "common.h"
#include "global.h"

#include <iostream>

bool PsuedoBZDBCache::animatedTreads = ANIMATED_TREADS;

float PsuedoBZDBCache::tankLength = TANK_LENGTH;
float PsuedoBZDBCache::tankWidth = TANK_WIDTH;
float PsuedoBZDBCache::tankHeight = TANK_HEIGHT;

const std::string PsuedoStateDatabase::BZDB_TANKLENGTH = "_tankLength";
const std::string PsuedoStateDatabase::BZDB_TANKWIDTH = "_tankWidth";
const std::string PsuedoStateDatabase::BZDB_TANKHEIGHT = "_tankHeight";

const std::string PsuedoStateDatabase::BZDB_OBESEFACTOR = "_obeseFactor";
const std::string PsuedoStateDatabase::BZDB_TINYFACTOR = "_tinyFactor";
const std::string PsuedoStateDatabase::BZDB_THIEFTINYFACTOR = "_thiefTinyFactor";

PsuedoStateDatabase& PsuedoStateDatabase::instance()
{
    static PsuedoStateDatabase bzdb;
    return bzdb;
}

float PsuedoStateDatabase::eval(std::string name)
{
    if (name == "_tankLength") return TANK_LENGTH;
    else if (name == "_tankWidth") return TANK_WIDTH;
    else if (name == "_tankHeight") return TANK_HEIGHT;
    else if (name == "_obeseFactor") return OBESE_FACTOR;
    else if (name == "_tinyFactor") return TINY_FACTOR;
    else if (name == "_thiefTinyFactor") return THIEFTINY_FACTOR;

    std::cerr << "PsuedoStateDatabase::eval(\"" << name << "\") - error, variable not found" << std::endl;
    exit(-2);
}

int PsuedoStateDatabase::evalInt(std::string name)
{
    if (name == "treadStyle") return TREAD_STYLE;

    std::cerr << "PsuedoStateDatabase::evalInt(\"" << name << "\") - error, variable not found" << std::endl;
    exit(-2);
}

bool PsuedoStateDatabase::evalBool(std::string name)
{
    if (name == "animatedTreads") return ANIMATED_TREADS;

    std::cerr << "PsuedoStateDatabase::evalBool(\"" << name << "\") - error, variable not found" << std::endl;
    exit(-2);
}

std::string PsuedoStateDatabase::getDefault(std::string name)
{
    if (name == "_tankLength") return DEFAULT_TANK_LENGTH;
    else if (name == "_tankWidth") return DEFAULT_TANK_WIDTH;
    else if (name == "_tankHeight") return DEFAULT_TANK_HEIGHT;

    std::cerr << "PsuedoStateDatabase::getDefault(\"" << name << "\") - error, variable not found" << std::endl;
    exit(-2);
}

void PsuedoStateDatabase::addCallback(const std::string&, Callback, void*)
{

}
void PsuedoStateDatabase::removeCallback(const std::string&, Callback, void*)
{

}


PsuedoSceneRenderer& PsuedoSceneRenderer::instance()
{
    static PsuedoSceneRenderer renderer;
    return renderer;
}

int PsuedoSceneRenderer::useQuality()
{
    return QUALITY;
}


void PsuedoOpenGLGState::registerContextInitializer(OpenGLContextFunction, OpenGLContextFunction, void*)
{

}

void PsuedoOpenGLGState::unregisterContextInitializer(OpenGLContextFunction, OpenGLContextFunction, void*)
{

}
