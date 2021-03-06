/* xcl_sampler.c 
 *
 * Copyright (c) 2009-2010 Brown Deer Technology, LLC.  All Rights Reserved.
 *
 * This software was developed by Brown Deer Technology, LLC.
 * For more information contact info@browndeertechnology.com
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3 (LGPLv3)
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* DAR */

#include <XCL/cl.h>

#include "xcl_structs.h"


// Sampler APIs


cl_sampler 
clCreateSampler(
	 cl_context ctx,
	 cl_bool norm_coords,
	 cl_addressing_mode amode,
	 cl_filter_mode fmode,
	 cl_int* err_ret
)
{
	WARN(__FILE__,__LINE__,"clCreateSampler: warning: unsupported");

	if (__invalid_context(ctx)) return(CL_INVALID_CONTEXT);


	struct _cl_sampler* sampler 
		= (struct _cl_sampler*)malloc(sizeof(struct _cl_sampler));


	if (sampler) {

		__init_sampler(sampler);

		sampler->refc = 1;
		sampler->ctx = ctx;
		sampler->norm_coords = norm_coords;
		sampler->amode = amode;
		sampler->fmode = fmode;

	}


	__success();

	return((cl_sampler)sampler);
}


cl_int 
clRetainSampler( cl_sampler sampler )
{
	WARN(__FILE__,__LINE__,"clRetainSampler: warning: unsupported");

	if (__invalid_sampler(sampler)) return(CL_INVALID_SAMPLER);

	++sampler->refc;

	return(CL_SUCCESS);
}


cl_int clReleaseSampler( cl_sampler sampler )
{
	WARN(__FILE__,__LINE__,"clReleaseSampler: warning: unsupported");

	if (__invalid_sampler(sampler)) return(CL_INVALID_SAMPLER);

	if (--sampler->refc == 0) {

		__do_release_sampler(sampler);

		__free_sampler(sampler);

	}

	return(CL_SUCCESS);
}


cl_int 
clGetSamplerInfo(
	 cl_sampler sampler,
	 cl_sampler_info param_name,
	 size_t param_sz,
	 void* param_val,
	 size_t* param_sz_ret
)
{
	WARN(__FILE__,__LINE__,"clGetSamplerInfo: warning: unsupported");

	if (__invalid_sampler(sampler)) return(CL_INVALID_SAMPLER);

	size_t sz;

	switch (param_name) {

		case CL_SAMPLER_REFERENCE_COUNT:

			__case_get_param(sizeof(cl_uint),&sampler->refc);

			break;

		case CL_SAMPLER_CONTEXT:

			__case_get_param(sizeof(cl_context),&sampler->ctx);

			break;

		case CL_SAMPLER_ADDRESSING_MODE;

			__case_get_param(sizeof(cl_addressing_mode),&sampler->amode);

			break;

		case CL_SAMPLER_FILTER_MODE:

			__case_get_param(sizeof(cl_filter_mode),&sampler->fmode);

			break;

		case CL_SAMPLER_NORMALIZED_COORDS:

			__case_get_param(sizeof(cl_bool),&sampler->norm_coords);

			break;

		default:

			return(CL_INVALID_VALUE);

	}
	
	return(CL_SUCCESS);
}

