#ifndef SHADER_CLASS
#define SHADER_CLASS

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

enum ShaderType{
    vertexShader,
    fragmentShader
};

unsigned int CompileShader(const char * source, GLenum shaderType);

unsigned int CreateShaderProgram(const char * vsPath, const char * fsPath);

#ifdef __APPLE__
std::string GetCurrentDirPath(const char * arg0);

#endif
#endif