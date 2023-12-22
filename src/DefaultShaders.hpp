#pragma once
#include <string_view>
#include "utils.hpp"

NS_SPECTRUM_BEGIN
// default sprite shader
inline std::string_view sprShaderVert = R"(
#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 mvp;

out vec2 texCoord;

void main() {
    gl_Position = mvp * vec4(vertexPos, 1.0);
    texCoord = aTexCoord;
}
)";

inline std::string_view sprShaderFrag = R"(
#version 330 core

in vec2 texCoord;
uniform sampler2D tex;
uniform vec3 col;

void main() {
    gl_FragColor = texture(tex, texCoord) * vec4(col, 1.0);
}
)";

// default ttf font shader
inline std::string_view ttfShaderVert = R"(
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}  
)";

inline std::string_view ttfShaderFrag = R"(
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
} 
)";

NS_SPECTRUM_END