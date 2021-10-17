#pragma once

#include <cstdint>
#include <atomic>

namespace Engine::Resources
{
    class ResourceHandler
    {
    public:
        ResourceHandler();
        uint32_t GenerateId();
    private:
        std::atomic_int _id;
    };
};