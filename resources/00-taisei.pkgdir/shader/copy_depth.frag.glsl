#version 330 core

#include "interface/copy_depth.glslh"

void main(void) {
    gl_FragDepth = texture(tex, texCoord).r;
}
