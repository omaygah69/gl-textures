#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

std::string loadShaderSource(const char* filePath);
GLuint createShaderProgram(const char* vertPath, const char* fragPath);
