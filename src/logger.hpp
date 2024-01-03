#pragma once
#include <format>
#include <iostream>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

template <typename... Args>
void logD(std::format_string<Args...> s, Args&&... args) {
    // std::printf("[SPL] [I] %s\n", std::format(s, std::forward<Args>(args)...));
    std::printf("[SPL] [DBG] %s\n", std::format(s, std::forward<Args>(args)...).c_str());
}

template <typename... Args>
void logW(std::format_string<Args...> s, Args&&... args) {
    // fmt::print(fmt::fg(fmt::terminal_color::bright_yellow), "[SPL] [W] {}\n", fmt::format(s, std::forward<Args>(args)...));
    std::printf("[SPL] [WRN] %s\n", std::format(s, std::forward<Args>(args)...).c_str());
}

template <typename... Args>
void logE(std::format_string<Args...> s, Args&&... args) {
    // fmt::print(fmt::fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold, "[SPL] [E] {}\n",
    //            fmt::format(s, std::forward<Args>(args)...));
    std::printf("[SPL] [ERR] %s\n", std::format(s, std::forward<Args>(args)...).c_str());
}

NS_SPECTRUM_END