#pragma once

#include "date/date.h"

#include <ostream>
#include <string>
#include <memory>

#include <iostream>
#include <chrono>
#include <ctime>
#include <exception>

#include "rang/rang.hpp"

namespace Engine::Global::Utilities::Logger
{
    namespace
    {
        std::unique_ptr<std::ostream> _sink;

        std::ostream& GetStream()
        {
            if (_sink == nullptr)
                throw std::exception("_sink has not been initialized");

            return *_sink;
        }

        void printTime()
        {
            GetStream() << date::format("%T", std::chrono::system_clock::now()) << "Z: ";
        }

        void printFormat(const char *format)
        {
            GetStream() << format;
        }

        template<typename T, typename... Targs>
        void printFormat(const char *format,
                         T value,
                         Targs... Fargs) // recursive variadic function
        {
            for (; *format != '\0'; format++)
            {
                if (*format == '%')
                {
                    GetStream() << value;
                    printFormat(format + 1, Fargs...); // recursive call
                    return;
                }
                GetStream() << *format;
            }
        }
    };

    inline void SetupSink(std::ostream &sink)
    {
        _sink = std::make_unique<std::ostream>(sink.rdbuf());
    }

    static constexpr const char *Info = "INFO";
    static constexpr const char *Warning = "WARNING";
    static constexpr const char *Error = "ERROR";

    template<typename T, typename... Targs>
    inline void WriteInfo(const char *format, T value, Targs... Fargs)
    {
        GetStream() << rang::bgB::green << rang::fg::black << Info << rang::fg::reset << rang::bg::reset << " ";
        printTime();
        printFormat(format, value, Fargs...);
        GetStream() << std::endl;
    }

    template<typename T, typename... Targs>
    inline void WriteWarning(const char *format, T value, Targs... Fargs)
    {
        GetStream() << rang::bgB::yellow << rang::fg::black << Warning << rang::fg::reset << rang::bg::reset << " ";
        printTime();
        printFormat(format, value, Fargs...);
        GetStream() << std::endl;
    }

    template<typename T, typename... Targs>
    inline void WriteError(const char *format, T value, Targs... Fargs)
    {
        GetStream() << rang::bgB::red << rang::fg::black << Error << rang::fg::reset << rang::bg::reset << " ";
        printTime();
        printFormat(format, value, Fargs...);
        GetStream() << std::endl;
    }
};