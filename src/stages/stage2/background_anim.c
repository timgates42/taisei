/*
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 * ---
 * Copyright (c) 2011-2019, Lukas Weber <laochailan@web.de>.
 * Copyright (c) 2012-2019, Andrei Alexeyev <akari@taisei-project.org>.
*/

#include "taisei.h"

#include "background_anim.h"

#include "stageutils.h"
#include "coroutine.h"

TASK(animate_bg_fullstage, NO_ARGS) {
	//stage_3d_context.cx[2] = 10;
	//stage_3d_context.cx[0] = 0;
	//stage_3d_context.crot[0] = 20;
	////stage_3d_context.crot[2] = -90;
	//stage_3d_context.cv[1] = 0.05;

	
	stage_3d_context.cx[2] = 10;
	stage_3d_context.cx[0] = 10;
	stage_3d_context.crot[0] = 50;
	stage_3d_context.crot[2] = -90;
	stage_3d_context.cv[0] = -0.1;

	for(;;) {
		YIELD;
		
		fapproach_p(&stage_3d_context.crot[0], 20, 0.1f);
		fapproach_p(&stage_3d_context.crot[2], 0.0f, 0.2f);
		fapproach_p(&stage_3d_context.cv[0], 0.0f, 0.0005f);
		fapproach_p(&stage_3d_context.cv[1], 0.05f, 0.01f);
		//stage_3d_context.crot[2] += fmin(0.5f, -stage_3d_context.crot[2] * 0.02f);
		stage3d_update(&stage_3d_context);
	}
}

void stage2_bg_init_fullstage(void) {
	INVOKE_TASK(animate_bg_fullstage);
}

TASK(animate_bg_spellpractice, NO_ARGS) {
	stage_3d_context.cx[2] = 10;
	stage_3d_context.cx[0] = 0;
	stage_3d_context.crot[0] = 20;
	stage_3d_context.cv[1] = 0.05;


	for(;;) {
		YIELD;
		stage3d_update(&stage_3d_context);
	}
}

void stage2_bg_init_spellpractice(void) {
	INVOKE_TASK(animate_bg_spellpractice);
}
