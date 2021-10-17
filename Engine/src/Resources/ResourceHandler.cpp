#include "ResourceHandler.hpp"

namespace Engine::Resources
{
    ResourceHandler::ResourceHandler()
    {}

    uint32_t ResourceHandler::GenerateId()
    {
        return static_cast<uint32_t>(++_id);
    }
};