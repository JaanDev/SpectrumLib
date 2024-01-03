#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "utils.hpp"
#include "Shader.hpp"
#include "DefaultShaders.hpp"

NS_SPECTRUM_BEGIN

class SPL_API ShaderManager {
  public:
    static ShaderManager* get();
    ShaderManager();

    std::shared_ptr<Shader> getShader(const std::string& id) const;
    void addShader(std::shared_ptr<Shader> shader, const std::string& id);
    void removeShader(const std::string& id);
    void removeAllShaders();

  private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
};

NS_SPECTRUM_END