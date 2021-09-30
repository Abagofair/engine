#pragma once

#include <string>
#include <unordered_map>

namespace Engine::Global
{
    template<typename T = int>
    class GameEventBus
    {
    public:

        void Emit(T)
        {

        }
    private:
       // std::unordered_map<T, std::function<>> _eventHandlers;
    };
}