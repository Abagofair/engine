#include "Rendering/Shader.hpp"

namespace Engine::Rendering
{
    Shader::Shader(uint32_t* shaderId)
    : _glShaderProgramId(shaderId)
    {}

    Shader::Shader(std::string filePath)
    {
        std::cout << std::filesystem::current_path() << std::endl;
        if (std::filesystem::exists(filePath))
        {
            std::cout << "exists" << std::endl;
        }

        std::ifstream shaderFile(filePath);
        std::string line;

        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;

        if (!shaderFile.is_open())
            std::cout << "file is not open" << std::endl;

    //TODO: FileReader.hpp
        while (std::getline(shaderFile, line))
        {
            if (line.find("#shader vertex") != std::string::npos)
            {
                while (std::getline(shaderFile, line))
                {
                    if (line.find("#shader fragment") != std::string::npos)
                    {
                        while (std::getline(shaderFile, line))
                        {
                            fragmentShaderStream << line << std::endl;
                        }
                        break;
                    }
                    vertexShaderStream << line << std::endl;
                }
            }
        }

        std::string vertexShaderStr = vertexShaderStream.str();
        std::string fragmentShaderStr = fragmentShaderStream.str();

        const char* cstr_fragmentShader = fragmentShaderStr.c_str();
        const char* cstr_vertexShader = vertexShaderStr.c_str();

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &cstr_vertexShader, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &cstr_fragmentShader, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        _glShaderProgramId = new uint32_t;
        *_glShaderProgramId = glCreateProgram();

        glAttachShader(*_glShaderProgramId, vertexShader);
        glAttachShader(*_glShaderProgramId, fragmentShader);
        glLinkProgram(*_glShaderProgramId);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::Shader(Shader&& shader)
        : Shader(shader._glShaderProgramId)
    {
        shader._glShaderProgramId = nullptr;
    }

    Shader::~Shader()
    {
        glDeleteProgram(*_glShaderProgramId);
        delete _glShaderProgramId;
    }

    Shader& Shader::operator=(Shader&& shader)
    {
        std::swap(_glShaderProgramId, shader._glShaderProgramId);
        return *this;
    }

    uint32_t Shader::ShaderId() const
    {
        return *_glShaderProgramId;
    }

    void Shader::Use() const
    {
        glUseProgram(*_glShaderProgramId);
    }

    void Shader::SetUniformMat4(const glm::mat4& transform, const std::string& name)
    {
        unsigned int uniformLocation = glGetUniformLocation(*_glShaderProgramId, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(transform));
    }

    void Shader::SetUniformBoolArray(const unsigned int* array, int size, const std::string& name)
    {
        unsigned int uniformLocation = glGetUniformLocation(*_glShaderProgramId, name.c_str());
        glUniform1uiv(uniformLocation, size, array);
    }

    void Shader::SetUniformBool(bool value, const std::string& name)
    {
        unsigned int uniformLocation = glGetUniformLocation(*_glShaderProgramId, name.c_str());
        glUniform1ui(uniformLocation, value);
    }
};