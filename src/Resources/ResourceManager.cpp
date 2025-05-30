#include "ResourceManager.h"
#include "../Render/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManeger::ResourceManeger(const std::string& executablePath) {
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, found);
}

std::string ResourceManeger::getFileString(const std::string& relativeFilePath) const {
    std::ifstream f;
    f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
        return std::string{}; 
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManeger::loadShaders(const std::string& shaderName, const std::string& vertextPath, const std::string& fragmentPath) {
    std::string vertexString = getFileString(vertextPath);
    if (vertexString.empty()) {
        std::cerr << "No vertex shader!" << std::endl;
        return nullptr;
    }

    std::string fragmentString = getFileString(fragmentPath);
    if (fragmentString.empty()) {
        std::cerr << "No fragment shader!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;

    if (newShader->isCompiled())
        return newShader;
    
    std::cerr << "Can't load shader program:\n"
            << "Vertex: " << vertextPath << "\n"
            << "Fragment: " << fragmentPath << "\n";
    
    return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManeger::getShaderProgram(const std::string& shaderName) {
    ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
    if (it != m_shaderPrograms.end()) 
        return it->second;
    
    std::cerr << "Can't find the shader program: " << shaderName << std::endl;
    return nullptr;
}