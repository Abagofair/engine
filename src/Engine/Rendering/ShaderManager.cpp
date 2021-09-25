#include <Engine/Rendering/ShaderManager.hpp>

namespace Engine::Rendering
{
	ShaderManager::ShaderManager()
	{
	}

	uint32_t ShaderManager::LoadShader(std::string filePath)
	{
		Shader* shader = new Shader(filePath);
		_shadersById.try_emplace(shader->ShaderId(), shader);
		return shader->ShaderId();
	}

	Shader& ShaderManager::GetShader(uint32_t shaderId) const
	{
		const auto& iter = _shadersById.find(shaderId);
		if (iter != _shadersById.end())
		{
			return *iter->second;
		}

		throw std::invalid_argument("shaderId does not exist");
	}
};