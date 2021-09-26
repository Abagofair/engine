#include <Engine/Rendering/ShaderManager.hpp>

namespace Engine::Rendering
{
	ShaderManager::ShaderManager()
	{}

	const Shader& ShaderManager::LoadShader(
		std::string filePath,
		std::string name)
	{
		Shader* shader = new Shader(filePath);
		_shadersById.try_emplace(name, shader);
		return *shader;
	}

	Shader& ShaderManager::GetShader(std::string name) const
	{
		const auto& iter = _shadersById.find(name);
		if (iter != _shadersById.end())
		{
			return *iter->second;
		}

		throw std::invalid_argument("shader name does not exist");
	}
};