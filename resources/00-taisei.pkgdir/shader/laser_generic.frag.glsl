#version 330 core

#include "lib/render_context.glslh"
#include "lib/util.glslh"
#include "interface/laser_generic.glslh"

void main(void) {
	// o_fragColor = vec4(vec2(v_texCoordRaw.x, v_texCoordRaw.y) * 0.9 + vec2(0.1), 0.0, 1.0);
	// o_fragColor = vec4(hsv2rgb(vec3(v_texCoord.x, 0.5 + 0.5 * v_texCoord.y, 0.5 + 0.5 * (float(gl_FrontFacing)))), 1.0);
	// o_fragColor = vec4(hsv2rgb(vec3(v_texCoord.y, 0.3 + 0.7 * v_texCoord.y, 0.3 + 0.7 * float(gl_FrontFacing))), 1.0);
	// o_fragColor = vec4(texture(u_texture, v_texCoord).rgb * r_color.rgb, 0.0);
	// o_fragColor = vec4(texture(u_texture, v_texCoord).rgb * v_color.rgb, 0.0);
    vec4 texel = textureLod(u_texture, v_texCoord, 0);
    o_fragColor = vec4((texel.g * v_color.rgb + vec3(texel.b)) * v_color.a, 0.0);





    // o_fragColor = vec4(vec2(v_texCoordRaw.x, v_texCoordRaw.y) * 0.9 + vec2(0.1), 0.0, 1.0);
    o_fragColor = vec4(1.0, 0.25, v_texCoordRaw.x, 0.0);
}
