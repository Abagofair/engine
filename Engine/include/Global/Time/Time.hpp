#pragma once

#include <cstdint>

namespace Engine::Global::Time
{
    struct Time
    {
        uint32_t MsElapsedTotal;
        uint32_t MsElapsedFrame;
        float SecElapsedFrame;
    };
};