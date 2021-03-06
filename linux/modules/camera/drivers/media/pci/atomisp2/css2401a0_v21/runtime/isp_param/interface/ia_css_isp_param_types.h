/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#ifndef _IA_CSS_ISP_PARAM_TYPES_H_
#define _IA_CSS_ISP_PARAM_TYPES_H_

#include "ia_css_acc_types.h"

/* Explicit member numbering to avoid fish type checker bug */
enum ia_css_param_class {
	IA_CSS_PARAM_CLASS_PARAM  = 0,	/* Late binding parameters, like 3A */
	IA_CSS_PARAM_CLASS_CONFIG = 1,	/* Pipe config time parameters, like resolution */
	IA_CSS_PARAM_CLASS_STATE  = 2,    // State parameters, like tnr buffer index
	/* Not yet implemented
	IA_CSS_PARAM_CLASS_FRAME	  = 3,    // Frame time parameters, like output buffer
	*/
};
#define IA_CSS_NUM_PARAM_CLASSES (IA_CSS_PARAM_CLASS_STATE + 1)


/* Address/size of each parameter class in each isp memory, host memory pointers */
struct ia_css_isp_param_host_segments {
	struct ia_css_host_data params[IA_CSS_NUM_PARAM_CLASSES][IA_CSS_NUM_ISP_MEMORIES];
};

/* Address/size of each parameter class in each isp memory, css memory pointers */
struct ia_css_isp_param_css_segments {
	struct ia_css_data      params[IA_CSS_NUM_PARAM_CLASSES][IA_CSS_NUM_ISP_MEMORIES];
};

/* Address/size of each parameter class in each isp memory, isp memory pointers */
struct ia_css_isp_param_isp_segments {
	struct ia_css_isp_data  params[IA_CSS_NUM_PARAM_CLASSES][IA_CSS_NUM_ISP_MEMORIES];
};

/* Memory offsets in binary info */
struct ia_css_isp_param_memory_offsets {
	uint32_t offsets[IA_CSS_NUM_PARAM_CLASSES];  /**< offset wrt hdr in bytes */
};

/** Offsets for ISP kernel parameters per isp memory.
 * Only relevant for standard ISP binaries, not ACC or SP.
 */
union ia_css_all_memory_offsets {
	struct {
		CSS_ALIGN(struct ia_css_memory_offsets	      *param, 8);
		CSS_ALIGN(struct ia_css_config_memory_offsets *config, 8);
		CSS_ALIGN(struct ia_css_state_memory_offsets  *state, 8);
	} offsets;
	struct {
		CSS_ALIGN(void *ptr, 8);
	} array[IA_CSS_NUM_PARAM_CLASSES];
};

#define IA_CSS_DEFAULT_ISP_MEM_PARAMS \
		{ { { { 0, 0 } } } }

#define IA_CSS_DEFAULT_ISP_CSS_PARAMS \
		{ { { { 0, 0 } } } }

#define IA_CSS_DEFAULT_ISP_ISP_PARAMS \
		{ { { { 0, 0 } } } }

#endif /* _IA_CSS_ISP_PARAM_TYPES_H_ */

