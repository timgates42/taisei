#version 330 core

#include "lib/render_context.glslh"
#include "lib/util.glslh"
#include "interface/laser_generic.glslh"

void main(void) {
	gl_Position = r_projectionMatrix * r_modelViewMatrix * vec4(a_position.x, a_position.y, 0.0, 1.0);
	v_laserID = a_laserID;
	v_texCoordRaw = a_texCoord;
	v_texCoord = uv_to_region(u_lasers[a_laserID].textureRegion, a_texCoord);
	v_color = u_lasers[a_laserID].color;
}
