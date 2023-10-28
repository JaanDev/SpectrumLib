#pragma once
#include <fmt/format.h>
#include <fmt/color.h>
#include <iostream>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

template <typename... Args>
void logD(Args... args) {
    fmt::print("[SPL] [I] {}\n", fmt::format(args...));
}

template <typename... Args>
void logW(Args... args) {
    fmt::print(fmt::fg(fmt::terminal_color::bright_yellow), "[SPL] [W] {}\n", fmt::format(args...));
}

template <typename... Args>
void logE(Args... args) {
    fmt::print(fmt::fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold, "[SPL] [E] {}\n", fmt::format(args...));
}

NS_SPECTRUM_END