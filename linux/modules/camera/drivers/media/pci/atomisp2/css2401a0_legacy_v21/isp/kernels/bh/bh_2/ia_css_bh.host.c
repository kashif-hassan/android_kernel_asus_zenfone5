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

#if !defined(HAS_NO_HMEM)

#include "ia_css_memory_access.h"
#include "memory_access.h"
#include "ia_css_types.h"
#include "sh_css_internal.h"
#include "assert_support.h"
#include "sh_css_frac.h"

#include "ia_css_bh.host.h"

void
ia_css_bh_hmem_decode(struct ia_css_3a_rgby_output *out_ptr,
		      hrt_vaddress ddr_ptr)
{
	struct ia_css_bh_table *hmem_buf = sh_css_malloc(sizeof(*hmem_buf));
	int i;

	/*
	 * No weighted histogram, hence no grid definition
	 */	
	if(!hmem_buf)
		return;
	assert(sizeof_hmem(HMEM0_ID) == sizeof(*hmem_buf));
	mmgr_load(ddr_ptr, (void *)hmem_buf, sizeof(*hmem_buf));

	/* Deinterleave */
	for (i = 0; i < HMEM_UNIT_SIZE; i++) {
		out_ptr[i].r = hmem_buf->hmem[BH_COLOR_R][i];
		out_ptr[i].g = hmem_buf->hmem[BH_COLOR_G][i];
		out_ptr[i].b = hmem_buf->hmem[BH_COLOR_B][i];
		out_ptr[i].y = hmem_buf->hmem[BH_COLOR_Y][i];
		/* sh_css_print ("hmem[%d] = %d, %d, %d, %d\n",
			i, out_ptr[i].r, out_ptr[i].g, out_ptr[i].b, out_ptr[i].y); */
	}
	sh_css_free(hmem_buf);
}

void
ia_css_bh_encode(struct sh_css_isp_bh_params *to,
	 const struct ia_css_3a_config *from)
{
	/* coefficients to calculate Y */
	to->y_coef_r =
	    uDIGIT_FITTING(from->ae_y_coef_r, 16, SH_CSS_AE_YCOEF_SHIFT);
	to->y_coef_g =
	    uDIGIT_FITTING(from->ae_y_coef_g, 16, SH_CSS_AE_YCOEF_SHIFT);
	to->y_coef_b =
	    uDIGIT_FITTING(from->ae_y_coef_b, 16, SH_CSS_AE_YCOEF_SHIFT);
}

void
ia_css_bh_hmem_encode(struct sh_css_isp_bh_hmem_params *to,
		  const struct ia_css_3a_config *from)
{
	(void)from;
	(void)to;
}

#endif
