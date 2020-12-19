/*
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 * ---
 * Copyright (c) 2011-2019, Lukas Weber <laochailan@web.de>.
 * Copyright (c) 2012-2019, Andrei Alexeyev <akari@taisei-project.org>.
*/

#include "taisei.h"

#include "draw.h"

#include "renderer/api.h"
#include "stageutils.h"
#include "global.h"
#include "util/glm.h"

static void stage2_bg_setup_pbr_lighting() {

	vec3 light_pos[] = {
		{0, 0, 0},
	};

	mat4 camera_trans;
	glm_mat4_identity(camera_trans);
	camera3d_apply_transforms(&stage_3d_context.cam, camera_trans);

	vec3 light_colors[] = {
		{10, 0, 0},
	};

	vec3 cam_light_positions[1];
	glm_mat4_mulv3(camera_trans, light_pos[0], 1, cam_light_positions[0]);

		
	r_uniform_vec3_array("light_positions[0]", 0, ARRAY_SIZE(cam_light_positions), cam_light_positions);
	r_uniform_vec3_array("light_colors[0]", 0, ARRAY_SIZE(light_colors), light_colors);
	r_uniform_int("light_count", 1);


	r_uniform_vec3("ambient_color",1,1,1);
}

static void stage2_bg_branch_draw(vec3 pos) {
	r_state_push();

	real f1 = sin(12123*pos[1]*pos[1]);
	real f2 = cos(2340*f1*f1);
	real f3 = cos(2469*f2*f2);
	
	r_mat_mv_push();
	r_mat_mv_translate(pos[0]-f3*f3, pos[1]+f2, pos[2]+0.5*f1);

	r_mat_mv_rotate(-M_PI/2+0.4*f1, 0, 0.05*f3, 1);


	r_shader("pbr");
	stage2_bg_setup_pbr_lighting();
	
	r_uniform_float("metallic", 0);
	r_uniform_sampler("tex", "stage2/branch_diffuse");
	r_uniform_sampler("roughness_map", "stage2/branch_roughness");
	r_uniform_sampler("normal_map", "stage2/branch_normal");
	r_uniform_sampler("ambient_map", "stage2/branch_ambient");
	r_draw_model("stage2/branch");
	r_uniform_sampler("tex", "stage2/leaves_diffuse");
	r_uniform_sampler("roughness_map", "stage2/leaves_roughness");
	r_uniform_sampler("normal_map", "stage2/leaves_normal");
	r_uniform_sampler("ambient_map", "stage2/leaves_ambient");
	r_draw_model("stage2/leaves");
	r_mat_mv_pop();


	r_state_pop();
}

static void stage2_bg_grass_draw(vec3 pos) {
	r_state_push();

	real f1 = sin(123*pos[1]*pos[1]);
	real f2 = cos(234350*f1*f1);
	real f3 = cos(24269*f2*f2);
	
	r_mat_mv_push();
	r_mat_mv_translate(pos[0]-f3*f3, pos[1]+f2, pos[2]);
	

	//r_mat_mv_rotate(-M_PI/2+0.4*f1, 0, 0.05*f3, 1);


	r_shader("pbr");
	stage2_bg_setup_pbr_lighting();
	
	r_uniform_float("metallic", 0);
	r_uniform_sampler("tex", "stage2/grass_diffuse");
	r_uniform_sampler("roughness_map", "stage2/grass_roughness");
	r_uniform_sampler("normal_map", "stage2/grass_normal");
	r_uniform_sampler("ambient_map", "stage2/grass_ambient");
	r_uniform_vec3("ambient_color", 0.4, 0.4, 0.4);
	r_mat_mv_rotate(-M_PI/2*1.2,1,0,0);
	r_mat_mv_scale(2,2,2);

	r_disable(RCAP_CULL_FACE);
	r_disable(RCAP_DEPTH_WRITE);

	int n = 3;
	for(int i = 0; i < n; i++) {
		r_mat_mv_push();
		r_mat_mv_rotate(M_PI*(i-n/2)/n*0.6,0,1,0);
		r_mat_mv_translate((i-n/2)*0.2*f1,0,0);
		r_draw_quad();
		r_mat_mv_pop();
	}
	r_mat_mv_pop();


	r_state_pop();
}

static void stage2_bg_ground_draw(vec3 pos) {
	r_state_push();

	r_mat_mv_push();
	r_mat_mv_translate(pos[0], pos[1], pos[2]);

	r_shader("pbr");
	stage2_bg_setup_pbr_lighting();

	r_uniform_float("metallic", 0);
	r_uniform_sampler("tex", "stage2/ground_diffuse");
	r_uniform_sampler("roughness_map", "stage2/ground_roughness");
	r_uniform_sampler("normal_map", "stage2/ground_normal");
	r_uniform_sampler("ambient_map", "stage2/ground_ambient");
	r_draw_model("stage2/ground");

	r_uniform_sampler("tex", "stage2/rocks_diffuse");
	r_uniform_sampler("roughness_map", "stage2/rocks_roughness");
	r_uniform_sampler("normal_map", "stage2/rocks_normal");
	r_uniform_sampler("ambient_map", "stage2/rocks_ambient");
	r_draw_model("stage2/rocks");

	r_uniform_sampler("tex", "stage2/grass_diffuse");
	r_uniform_sampler("roughness_map", "stage2/grass_roughness");
	r_uniform_sampler("normal_map", "stage2/grass_normal");
	r_uniform_sampler("ambient_map", "stage2/grass_ambient");
	r_uniform_vec3("ambient_color", 0.4, 0.4, 0.4);
	r_draw_model("stage2/grass");



	r_mat_mv_pop();


	r_state_pop();
}

static void stage2_bg_water_draw(vec3 pos) {
	r_state_push();

	r_shader("stage1_water");
	r_uniform_sampler("tex", "stage2/ground_ambient");
	r_uniform_float("time", 0.5 * global.frames / (float)FPS);

	r_mat_mv_push();
	static const Color water_color = { 0, 0.08, 0.08, 1 };
	r_uniform_vec4_rgba("water_color", &water_color);
	r_uniform_float("wave_offset", 0);
	
	r_mat_mv_translate(pos[0], pos[1], pos[2]);
	//r_disable(RCAP_DEPTH_WRITE);
	//r_color4(0, 0.08, 0.08, 0.5);
	r_mat_mv_scale(-25,25,5);
	r_draw_quad();
	r_mat_mv_pop();


	r_state_pop();
}



static uint stage2_bg_pos(Stage3D *s3d, vec3 pos, float maxrange) {
	vec3 p = {0, 0, 0};
	vec3 r = {0, 5, 0};

	return linear3dpos(s3d, pos, maxrange, p, r);
}
static uint stage2_bg_water_pos(Stage3D *s3d, vec3 pos, float maxrange) {
	vec3 p = {7, 0, -1};
	vec3 r = {0, 25, 0};

	return linear3dpos(s3d, pos, maxrange, p, r);
}

static uint stage2_bg_water_start_pos(Stage3D *s3d, vec3 pos, float maxrange) {
	vec3 p = {7, 0, -1};
	vec3 r = {25, 0, 0};

	return linear3dpos(s3d, pos, maxrange, p, r);
}

static uint stage2_bg_branch_pos(Stage3D *s3d, vec3 pos, float maxrange) {
	vec3 p = {-1, 0, 3.5};
	vec3 r = {0, 2, 0};

	return linear3dpos(s3d, pos, maxrange, p, r);
}

static uint stage2_bg_grass_pos(Stage3D *s3d, vec3 pos, float maxrange) {
	vec3 p = {-2.6, 0, 0.7};
	vec3 r = {0, 0.7, 0};

	return linear3dpos(s3d, pos, maxrange, p, r);
}

static bool stage2_fog(Framebuffer *fb) {
	r_shader("zbuf_fog");
	r_uniform_sampler("depth", r_framebuffer_get_attachment(fb, FRAMEBUFFER_ATTACH_DEPTH));
	r_uniform_vec4("fog_color", 0.5, 0.6, 0.9, 1.0);
	r_uniform_float("start", 0.2);
	r_uniform_float("end", 3.8);
	r_uniform_float("exponent", 3.0);
	r_uniform_float("sphereness", 0);
	draw_framebuffer_tex(fb, VIEWPORT_W, VIEWPORT_H);
	r_shader_standard();
	return true;
}

static bool stage2_bloom(Framebuffer *fb) {
	r_shader("bloom");
	r_uniform_int("samples", 10);
	r_uniform_float("intensity", 0.05);
	r_uniform_float("radius", 0.03);
	draw_framebuffer_tex(fb, VIEWPORT_W, VIEWPORT_H);
	r_shader_standard();
	return true;
}

void stage2_draw(void) {
	r_mat_proj_perspective(STAGE3D_DEFAULT_FOVY, VIEWPORT_W/(real)VIEWPORT_H, 1, 60);

	Stage3DSegment segs[] = {
		{ stage2_bg_ground_draw, stage2_bg_pos},
		{ stage2_bg_water_draw, stage2_bg_water_pos},
		{ stage2_bg_water_draw, stage2_bg_water_start_pos},
		{ stage2_bg_grass_draw, stage2_bg_grass_pos },
		{ stage2_bg_branch_draw, stage2_bg_branch_pos },
	};

	stage3d_draw(&stage_3d_context, 70, ARRAY_SIZE(segs), segs);
}

void stage2_drawsys_init(void) {
	stage3d_init(&stage_3d_context, 16);
}

void stage2_drawsys_shutdown(void) {
	stage3d_shutdown(&stage_3d_context);
}

ShaderRule stage2_bg_effects[] = {
	stage2_fog,
//	stage2_bloom,
	NULL
};
