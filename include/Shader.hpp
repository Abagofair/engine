#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glPortableHeaders.hpp>

class Shader
{
public:
    Shader(uint32_t* shaderId);
    Shader(std::string filePath);
    Shader(Shader&& shader);
    ~Shader();

    Shader& operator=(Shader&& shader);

    uint32_t ShaderId() const;
    void Use() const;
    void SetUniformMat4(const glm::mat4& transform, const std::string& name);
    void SetUniformBoolArray(const unsigned int* array, int size, const std::string& name);

private:
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    unsigned int* _glShaderProgramId;
};