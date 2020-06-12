#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace BL
{
    std::string readShader(const GLchar* pathToFile)
    {
        std::string content;
        std::ifstream fileStream(pathToFile, std::ios::in);

        if (!fileStream.is_open()) {
            std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
            return "";
        }

        std::string line = "";
        while (!fileStream.eof()) {
            std::getline(fileStream, line);
            content.append(line + "\n");
        }

        fileStream.close();
        return content;
    };

    class Shader {
    private:
        unsigned int _id;

    public:
        Shader(const GLchar* vertPath, const GLchar* fragPath)
        {
            std::string vertStr, fragStr;
            std::ifstream vertFile, fragFile;

            const int exceptions = std::ifstream::failbit | std::ifstream::badbit;
            vertFile.exceptions(exceptions);
            fragFile.exceptions(exceptions);

            try
            {
                vertFile.open(vertPath);
                fragFile.open(fragPath);
                std::stringstream vertStream, fragStream;
                vertStream << vertFile.rdbuf();
                fragStream << fragFile.rdbuf();
                vertFile.close();
                fragFile.close();
                vertStr = vertStream.str();
                fragStr = fragStream.str();
            }
            catch (std::ifstream::failure e) {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
                std::cout << "Error code: " << e.code() << std::endl;
            }

            const char* vertCode = vertStr.c_str();
            const char* fragCode = fragStr.c_str();


            // prepare vertex shader
            unsigned int vertShader;
            vertShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertShader, 1, &vertCode, NULL);
            glCompileShader(vertShader);

            // prepare fragment shader
            unsigned int fragShader;
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader, 1, &fragCode, NULL);
            glCompileShader(fragShader);

            // verify shader compile results
            char infoLog[512];
            int  success;
            glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            // prepare shader program
            _id = glCreateProgram();
            glAttachShader(_id, vertShader);
            glAttachShader(_id, fragShader);
            glLinkProgram(_id);

            glGetProgramiv(_id, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(_id, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
            }
            glDeleteShader(vertShader);
            glDeleteShader(fragShader);
        }

        unsigned int id() { return _id; }
        void use() { glUseProgram(_id); }
        void activate() { use(); }

        Shader setBool(const std::string& name, bool value) const
        {
            glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
            return *this;
        }

        Shader setInt(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
            return *this;
        }

        Shader setFloat(const std::string& name, float value)
        {
            glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
            return *this;
        }
    };

};
