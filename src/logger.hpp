#pragma once
#include <fmt/format.h>
#include <fmt/color.h>
#include <iostream>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

template <typename... Args>
void logD(fmt::format_string<Args...> s, Args&&... args) {
    fmt::print("[SPL] [I] {}\n", fmt::format(s, std::forward<Args>(args)...));
}

template <typename... Args>
void logW(fmt::format_string<Args...> s, Args&&... args) {
    fmt::print(fmt::fg(fmt::terminal_color::bright_yellow), "[SPL] [W] {}\n", fmt::format(s, std::forward<Args>(args)...));
}

template <typename... Args>
void logE(fmt::format_string<Args...> s, Args&&... args) {
    fmt::print(fmt::fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold, "[SPL] [E] {}\n",
               fmt::format(s, std::forward<Args>(args)...));
}

NS_SPECTRUM_END