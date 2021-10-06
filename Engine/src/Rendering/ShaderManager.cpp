#include "ShaderManager.hpp"
#include <utility>

namespace Engine::Rendering
{
	ShaderManager::ShaderManager()
	    = default;

	const Shader& ShaderManager::LoadShader(
		std::string filePath,
		const std::string& name)
	{
		auto* shader = new Shader(std::move(filePath));
		_shadersById.try_emplace(name, shader);
		return *shader;
	}

	Shader& ShaderManager::GetShader(const std::string& name) const
	{
		const auto& iter = _shadersById.find(name);
		if (iter != _shadersById.end())
		{
			return *iter->second;
		}

		throw std::invalid_argument("shader name does not exist");
	}
};