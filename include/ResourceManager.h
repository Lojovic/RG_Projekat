#pragma once
#ifndef PROJECT_BASE_RESOURCEMANAGER_H
#define PROJECT_BASE_RESOURCEMANAGER_H
/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <map>
#include <string>

#include <glad/glad.h>

#include "Texture.h"
#include <learnopengl/model.h>
#include <learnopengl/shader.h>

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class ResourceManager
{
public:
  // resource storage
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture2D> Textures;
  static std::map<std::string, Model> Models;

  static unsigned int
  loadCubemap(vector<std::string> faces);

  static Model
  LoadModel(std::string const &path, std::string name);
  static Model
  GetModel(std::string name);
  // loads (and generates) a shader program from file loading vertex, fragment
  // (and geometry) shader's source code. If gShaderFile is not nullptr, it also
  // loads a geometry shader
  static Shader
  LoadShader(const char *vShaderFile, const char *fShaderFile,
             const char *gShaderFile, std::string name);
  // retrieves a stored sader
  static Shader
  GetShader(std::string name);
  // loads (and generates) a texture from file
  static Texture2D
  LoadTexture(const char *file, bool alpha, std::string name);
  // retrieves a stored texture
  static Texture2D
  GetTexture(std::string name);
  // properly de-allocates all loaded resources
  static void
  Clear();

private:
  // private constructor, that is we do not want any actual resource manager
  // objects. Its members and functions should be publicly available (static).
  ResourceManager() {}
  // loads and generates a shader from file
  static Shader
  loadShaderFromFile(const char *vShaderFile, const char *fShaderFile,
                     const char *gShaderFile = nullptr);
  // loads a single texture from file
  static Texture2D
  loadTextureFromFile(const char *file, bool alpha);
};
#endif // PROJECT_BASE_RESOURCEMANAGER_H
