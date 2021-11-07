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
    static std::ostream _sink = std::ostream(std::cout.rdbuf());

    static constexpr const char *Info = "INFO";
    static constexpr const char *Warning = "WARNING";
    static constexpr const char *Error = "ERROR";

    static void printTime()
    {
        _sink << date::format("%T", std::chrono::system_clock::now()) << "Z: ";
    }

    static void printFormat(const char *format)
    {
        _sink << format;
    }

    template<typename T, typename... Targs>
    static void printFormat(const char *format,
                            T value,
                            Targs... Fargs) // recursive variadic function
    {
        for (; *format != '\0'; format++)
        {
            if (*format == '%')
            {
                _sink << value;
                printFormat(format + 1, Fargs...); // recursive call
                return;
            }
            _sink << *format;
        }
    }

    template<typename T, typename... Targs>
    void WriteInfo(const char *format, T value, Targs... Fargs)
    {
        _sink << rang::bgB::green << rang::fg::black << Info << rang::fg::reset << rang::bg::reset << " ";
        printTime();
        printFormat(format, value, Fargs...);
        _sink << std::endl;
    }

    template<typename T, typename... Targs>
    void WriteWarning(const char *format, T value, Targs... Fargs)
    {
        _sink << rang::bgB::yellow << rang::fg::black << Warning << rang::fg::reset << rang::bg::reset << " ";
        printTime();
        printFormat(format, value, Fargs...);
        _sink << std::endl;
    }

    template<typename T, typename... Targs>
    void WriteError(const char *format, T value, Targs... Fargs)
    {
        _sink << rang::bgB::red << rang::fg::black << Error << rang::fg::reset << rang::bg::reset << " ";
        printTime();
        printFormat(format, value, Fargs...);
        _sink << std::endl;
    }
};