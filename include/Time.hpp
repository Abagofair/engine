#pragma once

#include <cstdint>

namespace InternalTime
{
    struct Time
    {
        uint32_t MsElapsedTotal;
        uint32_t MsElapsedFrame;
        float SecElapsedFrame;
    };
};