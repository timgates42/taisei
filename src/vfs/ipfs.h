/*
 * This software is licensed under the terms of the MIT-License
 * See COPYING for further information.
 * ---
 * Copyright (c) 2011-2017, Lukas Weber <laochailan@web.de>.
 * Copyright (c) 2012-2017, Andrei Alexeyev <akari@alienslab.net>.
 */

#pragma once

#include "private.h"
#include "ipfs_public.h"

bool vfs_ipfs_init(VFSNode *node, const char *path);
void vfs_ipfs_global_init(void);
