#include "shaders.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

unsigned int CompileShader(const char* source, GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    if (!shader) {
        std::cerr << "ERROR::SHADER::" << ((shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT")
                  << "::CREATION_FAILED" << std::endl;
        return 0;
    }

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << ((shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT")
                  << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

unsigned int CreateShaderProgram(const char* vsPath, const char* fsPath) {
    // Read vertex shader file
    printf("%s\n", vsPath);
    std::ifstream vsStream(vsPath);
    if (!vsStream) {
        std::cerr << "ERROR::SHADER::VERTEX::FILE_NOT_FOUND: " << vsPath << std::endl;
        return 0;
    }
    std::string vs((std::istreambuf_iterator<char>(vsStream)), std::istreambuf_iterator<char>());

    // Read fragment shader file
    std::ifstream fsStream(fsPath);
    if (!fsStream) {
        std::cerr << "ERROR::SHADER::FRAGMENT::FILE_NOT_FOUND: " << fsPath << std::endl;
        return 0;
    }
    std::string fs((std::istreambuf_iterator<char>(fsStream)), std::istreambuf_iterator<char>());

    // Compile shaders
    unsigned int vertexShader = CompileShader(vs.c_str(), GL_VERTEX_SHADER);
    if (!vertexShader) {
        std::cerr << "ERROR::SHADER::VERTEX::FAILED_TO_COMPILE" << std::endl;
        return 0;
    }

    unsigned int fragmentShader = CompileShader(fs.c_str(), GL_FRAGMENT_SHADER);
    if (!fragmentShader) {
        std::cerr << "ERROR::SHADER::FRAGMENT::FAILED_TO_COMPILE" << std::endl;
        glDeleteShader(vertexShader); // Cleanup vertex shader
        return 0;
    }

    // Create and link shader program
    unsigned int shaderProgram = glCreateProgram();
    if (!shaderProgram) {
        std::cerr << "ERROR::SHADER::PROGRAM::CREATION_FAILED" << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glDeleteProgram(shaderProgram);
        shaderProgram = 0; // Mark as invalid
    }

    // Cleanup shaders (no matter success or failure of linking)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

#ifdef __APPLE__
std::string GetCurrentDirPath(const char * arg0)
{
    char *resolved = realpath(arg0, NULL);
    if (resolved != NULL) {
        char *fname = strrchr(resolved, '/');
        if (fname != NULL) {
            fname[1] = '\0';
        }
        std::string path = std::string(resolved);
        free(resolved);
        return path;
    } else {
        perror("realpath");
        return "";
    }
}
#endif