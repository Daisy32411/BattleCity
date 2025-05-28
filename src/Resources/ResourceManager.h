#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer {
    class ShaderProgram;
}



class ResourceManeger {
public:
    ResourceManeger(const std::string& executablePath);
    ~ResourceManeger() = default;

    ResourceManeger(const ResourceManeger&) = delete;
    ResourceManeger& operator=(const ResourceManeger&) = delete;
    ResourceManeger& operator=(ResourceManeger&&) = delete;
    ResourceManeger(ResourceManeger&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertextPath, const std::string& fragmentPath);
    std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

private:
    std::string getFileString(const std::string& relativeFilePath) const;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    std::string m_path;
};