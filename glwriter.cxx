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

#include "glwriter.h"

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <iostream>
#include <fstream>

#include <vector>
#include <map>

static std::fstream modelFile;
static std::fstream materialFile;
static std::fstream logFile;

struct VertInfo
{
    glm::vec3 vertice;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

// Default state
static glm::vec3 defaultNormal(0.0f, 0.0f, 1.0f);
static glm::vec2 defaultTexCoord(0.0f, 0.0f);

// State
static bool shadeModelIsSmooth = true;
static GLenum faceMode = 0;
static glm::vec3 normal = defaultNormal;
static glm::vec2 texCoord = defaultTexCoord;
static std::vector<VertInfo> vertices;
static unsigned int groupCount = 0;

// Model state
static std::map<std::string, MaterialInfo> materials;
static std::vector<glm::vec3> modelVertices;
static std::vector<glm::vec3> modelNormals;
static std::vector<glm::vec2> modelTexCoords;

void glWriterFileOpen(std::string baseFilename)
{
    modelFile.open(baseFilename + ".obj", std::ios_base::out);
    materialFile.open(baseFilename + ".mtl", std::ios_base::out);
    logFile.open(baseFilename + ".log", std::ios_base::out);
    if (!modelFile.is_open() || !materialFile.is_open() || !logFile.is_open())
    {
        std::cerr << "Failed to open model, material, or log for writing. TERMINATING!" << std::endl;
        exit(-1);
    }

    modelFile << "mtllib " << baseFilename << ".mtl" << std::endl;
    modelFile << "o " << baseFilename << std::endl;
}

void glWriterFileClose()
{
    // Write out the vertices
    for (const auto &mv : modelVertices)
        modelFile << "v " << mv.x << " " << mv.y << " " << mv.z << std::endl;

    // Write out the normals
    for (const auto &mn : modelNormals)
        modelFile << "vn " << mn.x << " " << mn.y << " " << mn.z << std::endl;

    // Write out the texcoords
    for (const auto &mt : modelTexCoords)
        modelFile << "vt " << mt.x << " " << mt.y << std::endl;

    // Write out materials
    for (auto &material : materials)
    {
        materialFile << "newmtl " << material.first << std::endl;
        if (material.second.diffuse[0] >= 0.0f)
            materialFile << "  Kd " << material.second.diffuse[0] << " " << material.second.diffuse[1] << " " <<
                         material.second.diffuse[2] << std::endl;
        if (material.second.diffuseTexture.length() > 0)
            materialFile << "  map_Kd " << material.second.diffuseTexture << std::endl;
    }

    modelFile.flush();
    modelFile.close();
    materialFile.flush();
    materialFile.close();
    logFile.flush();
    logFile.close();
}

void glWriterAddMaterial(std::string name, MaterialInfo material)
{
    materials[name] = material;
}

void glWriterSetCurrentMaterial(std::string name)
{
    modelFile << "usemtl " << name << std::endl;
}


int glWriterGetVerticeIndex(glm::vec3 v)
{
    int index = 1;
    for (const auto &mv : modelVertices)
    {
        if (v == mv)
            return index;
        index++;
    }
    std::cerr << "FATAL ERROR: Unable to find vertice: << " << v.x << " " << v.y << " " << v.z << std::endl;
    exit(-1);
}

int glWriterGetNormalIndex(glm::vec3 n)
{
    int index = 1;
    for (const auto &mn : modelNormals)
    {
        if (n == mn)
            return index;
        index++;
    }
    std::cerr << "FATAL ERROR: Unable to find normal: << " << n.x << " " << n.y << " " << n.z << std::endl;
    exit(-1);
}

int glWriterGetTexCoordIndex(glm::vec2 t)
{
    int index = 1;
    for (const auto &mt : modelTexCoords)
    {
        if (t == mt)
            return index;
        index++;
    }
    std::cerr << "FATAL ERROR: Unable to find texCoord: << " << t.x << " " << t.y << std::endl;
    exit(-1);
}

void writeFaceVertInfo(VertInfo vi)
{
    modelFile << " " << glWriterGetVerticeIndex(vi.vertice);
    if (vi.texCoord != defaultTexCoord || vi.normal != defaultNormal)
    {
        modelFile << "/";
        if (vi.texCoord != defaultTexCoord)
            modelFile << glWriterGetTexCoordIndex(vi.texCoord);
        modelFile << "/";
        if (vi.normal != defaultNormal)
            modelFile << glWriterGetNormalIndex(vi.normal);
    }
}


void glShadeModel(GLenum mode)
{
    logFile << "glShadeModel(" << mode << ")" << std::endl;
    if (mode == GL_FLAT)
        shadeModelIsSmooth = false;
    else if (mode == GL_SMOOTH)
        shadeModelIsSmooth = true;
    else
        logFile << "\tERROR: Invalid shade model mode: " << mode << std::endl;
}


void glBegin(GLenum mode)
{
    logFile << "glBegin(" << mode << ")" << std::endl;
    faceMode = mode;
    modelFile << "g Group" << ++groupCount << std::endl;
    if (shadeModelIsSmooth)
        modelFile << "s " << groupCount << std::endl;
    else
        modelFile << "s off" << std::endl;
}

void glEnd()
{
    logFile << "glEnd()" << std::endl;

    // {0, 1, 2}, {3, 4, 5}, ...
    if (faceMode == GL_TRIANGLES)
    {
        unsigned long index = 0;
        for (const auto &v : vertices)
        {
            if (index % 3 == 0)
                modelFile << "f";
            writeFaceVertInfo(v);
            if (index % 3 == 2)
                modelFile << std::endl;
            index++;
        }
    }
    // {0, 1, 2}, {1, 2, 3}, ...
    else if (faceMode == GL_TRIANGLE_STRIP)
    {
        for (unsigned long i = 0; i < vertices.size() - 2; ++i)
        {
            modelFile << "f";
            writeFaceVertInfo(vertices.at(i));
            writeFaceVertInfo(vertices.at(i+1));
            writeFaceVertInfo(vertices.at(i+2));
            modelFile << std::endl;
        }
    }
    // {0, 1, 2}, {1, 2, 3}, ...
    else if (faceMode == GL_TRIANGLE_FAN)
    {
        for (unsigned long i = 1; i < vertices.size() - 1; ++i)
        {
            modelFile << "f";
            writeFaceVertInfo(vertices.at(0));
            writeFaceVertInfo(vertices.at(i));
            writeFaceVertInfo(vertices.at(i+1));
            modelFile << std::endl;
        }
    }
    else
    {
        std::cerr << "\tERROR: Unsupported face mode: " << faceMode << std::endl;
        exit(-1);
    }

    faceMode = 0;
    vertices.clear();
    normal = defaultNormal;
    texCoord = defaultTexCoord;
}


GLuint glGenLists(GLsizei range) // NO-OP
{
    logFile << "glGenLists(" << range << ")" << std::endl;
    return 1;
}

void glNewList(GLuint list, GLenum mode)
{
    logFile << "glNewList(" << list << ", " << mode << ")" << std::endl;
}

void glEndList()
{
    logFile << "glEndList()" << std::endl;
}

void glDeleteLists(GLuint list, GLsizei range) // NO-OP
{
    logFile << "glDeleteLists(" << list << ", " << range << ")" << std::endl;
}


void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
    logFile << "\tglVertex3f(" << x << ", " << y << ", " << z << ")" << std::endl;

    glm::vec3 vert(x, y, z);

    VertInfo vi;
    vi.normal = normal;
    vi.texCoord = texCoord;
    vi.vertice = vert;

    vertices.push_back(vi);

    for (const auto &mv : modelVertices)
    {
        if (mv == vert)
            return;
    }
    modelVertices.push_back(vert);
}


void glNormal3f(GLfloat x, GLfloat y, GLfloat z)
{
    logFile << "\tglNormal3f(" << x << ", " << y << ", " << z << ")" << std::endl;

    normal = glm::vec3(x, y, z);

    for (const auto &mn : modelNormals)
    {
        if (mn == normal)
            return;
    }
    modelNormals.push_back(normal);
}


void glTexCoord2f(GLfloat x, GLfloat y)
{
    logFile << "\tglTexCoord2f(" << x << ", " << y << ")" << std::endl;

    texCoord = glm::vec2(x, y);

    for (const auto &mt : modelTexCoords)
    {
        if (mt == texCoord)
            return;
    }
    modelTexCoords.push_back(texCoord);
}
