#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define NS_SPECTRUM_BEGIN namespace spl {
#define NS_SPECTRUM_END }

NS_SPECTRUM_BEGIN

void initialize();
void shutdown();

NS_SPECTRUM_END