/* xcl_profile.c 
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


// Profiling APIs

cl_int clGetEventProfilingInfo(
	cl_event event,
	cl_profiling_info param_name,
	size_t param_sz,
	void* param_val,
	size_t* param_sz_ret
)
{
	WARN(__FILE__,__LINE__,"clGetEventProfilingInfo: warning: unsupported");


	size_t sz;

	switch (param_name) {

		case CL_PROFILING_COMMAND_QUEUED:

			__case_get_param(sizeof(cl_ulong),&event->tm_queued);

			break;
			
		case CL_PROFILING_COMMAND_SUBMIT:

			__case_get_param(sizeof(cl_ulong),&event->tm_submit);

			break;
			
		case CL_PROFILING_COMMAND_START;

			__case_get_param(sizeof(cl_ulong),&event->tm_start);

			break;
			
		case CL_PROFILING_COMMAND_END;

			__case_get_param(sizeof(cl_ulong),&event->tm_end);

			break;

		default:

			return(CL_INVALID_VALUE);

	}

	return(CL_SUCCESS);
}
