#pragma once
#include <string_view>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

// default sprite shader
inline std::string_view sprShaderVert = R"(
#version 330 core

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 mvp;

out vec2 texCoord;

void main() {
    gl_Position = mvp * vec4(vertexPos, 1.0, 1.0);
    texCoord = aTexCoord;
}
)";

inline std::string_view sprShaderFrag = R"(
#version 330 core

in vec2 texCoord;

uniform sampler2D tex;
uniform vec3 col;
uniform float opacity;

void main() {
    gl_FragColor = texture(tex, texCoord) * vec4(col, opacity);
    // gl_FragColor = vec4(1,0,0,1);
}
)";

// default ttf font shader
inline std::string_view ttfShaderVert = R"(
#version 330 core

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 mvp;

out vec2 texCoord;

void main() {
    gl_Position = mvp * vec4(vertexPos, 1.0, 1.0);
    texCoord = aTexCoord;
}
)";

inline std::string_view ttfShaderFrag = R"(
#version 330 core

in vec2 texCoord;

uniform sampler2D tex;
uniform vec3 col;
uniform float opacity;

void main() {
    gl_FragColor = vec4(1.0, 1.0, 1.0, texture(tex, texCoord).r) * vec4(col, opacity);
}
)";

NS_SPECTRUM_END