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

#include "glite.h"

// glGenTextures() should never return 0
#define INVALID_GL_TEXTURE_ID ((GLuint) 0)

// glGenLists() will only return 0 for errors
#define INVALID_GL_LIST_ID ((GLuint) 0)


void glWriterFileOpen(std::string filename);
void glWriterFileClose();

// Materials
struct MaterialInfo
{
    float diffuse[3] = {-1.0f, -1.0f, -1.0f}; // Kd
    std::string diffuseTexture; // map_Kd
};

void glWriterAddMaterial(std::string name, MaterialInfo material);
void glWriterSetCurrentMaterial(std::string name);


// GL functions

void glShadeModel(GLenum mode);

void glBegin(GLenum mode);
void glEnd();

GLuint glGenLists(GLsizei range); // NO-OP
void glNewList(GLuint list, GLenum mode);
void glEndList();
void glDeleteLists(GLuint list, GLsizei range); // NO-OP

void glVertex3f(GLfloat x, GLfloat y, GLfloat z);

void glNormal3f(GLfloat x, GLfloat y, GLfloat z);

void glTexCoord2f(GLfloat x, GLfloat y);
