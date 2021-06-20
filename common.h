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

#pragma once

#include <string>

#ifndef UNUSED
#define UNUSED(parameter) (parameter)
#endif


// Stripped down version of BZDBCache. Read-only access to specific values defined in global.h.
class PsuedoBZDBCache
{
public:
    static bool animatedTreads;

    static float tankLength;
    static float tankWidth;
    static float tankHeight;
};

#define BZDBCache PsuedoBZDBCache


// Stripped down version of StateDatabase. Read-only access to specific values defined in global.h.
class PsuedoStateDatabase
{
public:
    typedef void (*Callback)(const std::string& name, void* userData);

    static PsuedoStateDatabase& instance();

    float eval(std::string name);
    int evalInt(std::string name);
    bool evalBool(std::string name);

    std::string getDefault(std::string name);

    void addCallback(const std::string& name, Callback callback, void* userData);
    void removeCallback(const std::string& name, Callback callback, void* userData);

    static const std::string BZDB_TANKLENGTH;
    static const std::string BZDB_TANKWIDTH;
    static const std::string BZDB_TANKHEIGHT;
    static const std::string BZDB_OBESEFACTOR;
    static const std::string BZDB_TINYFACTOR;
    static const std::string BZDB_THIEFTINYFACTOR;
};

#define BZDB (PsuedoStateDatabase::instance())
#define StateDatabase PsuedoStateDatabase


// Stripped down version of SceneRenderer. This just returns the quality level.
class PsuedoSceneRenderer
{
public:
    static PsuedoSceneRenderer& instance();

    int useQuality();
};

#define RENDERER (PsuedoSceneRenderer::instance())


// Stripped down version of OpenGLGState. This does nothing except ease using code from BZFlag.
typedef void        (*OpenGLContextFunction)(void* userData);
class PsuedoOpenGLGState
{
public:
    static void registerContextInitializer(OpenGLContextFunction, OpenGLContextFunction, void*);
    static void unregisterContextInitializer(OpenGLContextFunction, OpenGLContextFunction, void*);
};

#define OpenGLGState PsuedoOpenGLGState
