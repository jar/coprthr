/* cmdcall_atigpu.c 
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

#include <string.h>
#include <CL/cl.h>

#include "xcl_structs.h"
#include "cmdcall.h"
#include "util.h"


static void* ndrange_kernel(cl_device_id devid, void* p)
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:ndrange_kernel");

#if(0)

	int i;

	struct cmdcall_arg* argp = (struct cmdcall_arg*)p;

/* XXX do not create local copy on stack, fix -DAR */
//	struct cmdcall_arg arg = *(struct cmdcall_arg*)p;

	DEBUG(__FILE__,__LINE__,"argp->flags %x\n",argp->flags);
	DEBUG(__FILE__,__LINE__,"argp->k.krn %p\n",argp->k.krn);
	DEBUG(__FILE__,__LINE__,"argp->k.krn->narg %d\n",argp->k.krn->narg);
	DEBUG(__FILE__,__LINE__,"argp->k.krn->narg %d\n",argp->k.krn->narg);
	

	DEBUG(__FILE__,__LINE__,"argp->k.word_dim %d\n",argp->k.work_dim);
	DEBUG(__FILE__,__LINE__,"argp->k.global_work_offset[] %d %d %d\n",
		argp->k.global_work_offset[0],
		argp->k.global_work_offset[1],
		argp->k.global_work_offset[2]);
	DEBUG(__FILE__,__LINE__,"argp->k.global_work_size[] %d %d %d\n",
		argp->k.global_work_size[0],
		argp->k.global_work_size[1],
		argp->k.global_work_size[2]);
	DEBUG(__FILE__,__LINE__,"argp->k.local_work_size[] %d %d %d\n",
		argp->k.local_work_size[0],
		argp->k.local_work_size[1],
		argp->k.local_work_size[2]);

/* XXX TESTING ONLY! */
//cl_mem* pbufa = argp->k.pr_arg_vec[0];
//int* aa = (*pbufa)->host_ptr;
//	DEBUG(__FILE__,__LINE__,"pbufa bufa %p %p %p %d\n",pbufa,*pbufa,aa,aa[10]);

	/* fix pointers */

/*
DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:ndrange_kernel: fix pointers %p",argp->k.arg_kind);
	for(i=0;i<argp->k.krn->narg;i++) {

DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:ndrange_kernel: fix pointers %d",i);

DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:ndrange_kernel: arg_kind=%d",argp->k.arg_kind[i]);

		switch(argp->k.arg_kind[i]) {

			case CLARG_KIND_GLOBAL:

DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:ndrange_kernel: argp->k.pr_arg_vec[i]=%p",argp->k.pr_arg_vec[i]);

DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:ndrange_kernel: *cl_mem=%p",(*(cl_mem*)argp->k.pr_arg_vec[i]));

//				argp->k.pr_arg_vec[i]=(*(cl_mem*)argp->k.pr_arg_vec[i])->host_ptr;
				*(void**)argp->k.pr_arg_vec[i]=(*(cl_mem*)argp->k.pr_arg_vec[i])->host_ptr;

				break;

			case CLARG_KIND_LOCAL:

DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:ndrange_kernel: __local argp->k.pr_arg_vec[i]=%p",argp->k.pr_arg_vec[i]);
DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:ndrange_kernel: *(size_t*)__local argp->k.pr_arg_vec[i]=%p",*(size_t*)argp->k.pr_arg_vec[i]);

				break;

			case CLARG_KIND_UNDEFINED:
			case CLARG_KIND_VOID:
			case CLARG_KIND_DATA:
			case CLARG_KIND_CONSTANT:
			case CLARG_KIND_SAMPLER:
			case CLARG_KIND_IMAGE2D:
			case CLARG_KIND_IMAGE3D:

			default: break;
		}
	}
*/

	vcproc_cmd(argp);

#endif

	return(0); 
}


static void* task(cl_device_id devid, void* argp)
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:task: unsupported");
	return(0); 
}


static void* native_kernel(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:native_kernel: unsupported");
	return(0); 
}


static void* read_buffer_safe(cl_device_id devid, void* p) 
{
	DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:read_buffer");

	struct cmdcall_arg* argp = (struct cmdcall_arg*)p;

	void* dst = argp->m.dst;
	void* src = ((cl_mem)argp->m.src)->host_ptr;
	size_t offset = argp->m.src_offset;
	size_t len = argp->m.len;

	if (dst==src+offset) return(0);

	else if (src+offset < dst+len || dst < src+offset+len) 
		memmove(dst,src+offset,len);
	
	else memcpy(dst,src+offset,len);

	return(0);
}

static void* read_buffer(cl_device_id devid, void* p) 
{
	DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:read_buffer");

	struct cmdcall_arg* argp = (struct cmdcall_arg*)p;

	void* dst = argp->m.dst;
	void* src = ((cl_mem)argp->m.src)->host_ptr;
	size_t offset = argp->m.src_offset;
	size_t len = argp->m.len;

	if (dst==src+offset) return(0);
	else memcpy(dst,src+offset,len);

	return(0);
}


static void* write_buffer_safe(cl_device_id devid, void* p) 
{
	DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:write_buffer");

	struct cmdcall_arg* argp = (struct cmdcall_arg*)p;

	void* dst = ((cl_mem)argp->m.dst)->host_ptr;
	void* src = argp->m.src;
	size_t offset = argp->m.dst_offset;
	size_t len = argp->m.len;

	if (dst+offset == src) return(0);

	else if (src < dst+offset+len || dst+offset < src+len) 
		memmove(dst,src+offset,len);
	
	else memcpy(dst+offset,src,len);

	return(0); 
}

static void* write_buffer(cl_device_id devid, void* p) 
{
	DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:write_buffer");

	struct cmdcall_arg* argp = (struct cmdcall_arg*)p;

	void* dst = ((cl_mem)argp->m.dst)->host_ptr;
	void* src = argp->m.src;
	size_t offset = argp->m.dst_offset;
	size_t len = argp->m.len;

	if (dst+offset == src) return(0);
	else memcpy(dst+offset,src,len);

	return(0); 
}


static void* copy_buffer_safe(cl_device_id devid, void* p)
{
	DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:copy_buffer");

	struct cmdcall_arg* argp = (struct cmdcall_arg*)p;

	void* dst = ((cl_mem)argp->m.dst)->host_ptr;
	void* src = ((cl_mem)argp->m.src)->host_ptr;
	size_t dst_offset = argp->m.dst_offset;
	size_t src_offset = argp->m.src_offset;
	size_t len = argp->m.len;

	if (dst+dst_offset == src+src_offset) return(0);

	else if (src+src_offset < dst+dst_offset+len 
		|| dst+dst_offset < src+src_offset+len) 
			memmove(dst+dst_offset,src+src_offset,len);
	
	else memcpy(dst+dst_offset,src+src_offset,len);

	return(0); 
}

static void* copy_buffer(cl_device_id devid, void* p)
{
	DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:copy_buffer");

	struct cmdcall_arg* argp = (struct cmdcall_arg*)p;

	void* dst = ((cl_mem)argp->m.dst)->host_ptr;
	void* src = ((cl_mem)argp->m.src)->host_ptr;
	size_t dst_offset = argp->m.dst_offset;
	size_t src_offset = argp->m.src_offset;
	size_t len = argp->m.len;

	if (dst+dst_offset == src+src_offset) return(0);
	else memcpy(dst+dst_offset,src+src_offset,len);

	return(0); 
}


static void* read_image(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:read_image: unsupported");
	return(0); 
}


static void* write_image(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:write_image: unsupported");
	return(0); 
}


static void* copy_image(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:copy_image: unsupported");
	return(0); 
}


static void* copy_image_to_buffer(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:copy_image_to_buffer: unsupported");
	return(0); 
}


static void* copy_buffer_to_image(cl_device_id devid, void* argp)
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:copy_buffer_to_image: unsupported");
	return(0); 
}


static void* map_buffer(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:map_buffer: unsupported");
	return(0); 
}


static void* map_image(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:map_image: unsupported");
	return(0); 
}


static void* unmap_mem_object(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:unmap_mem_object: unsupported");
	return(0); 
}


static void* marker(cl_device_id devid, void* p) 
{
	DEBUG(__FILE__,__LINE__,"cmdcall_atigpu:marker");
	return(0); 
}


static void* acquire_gl_objects(cl_device_id devid, void* argp)
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:acquire_gl_objects: unsupported");
	return(0); 
}


static void* release_gl_objects(cl_device_id devid, void* argp) 
{
	WARN(__FILE__,__LINE__,"cmdcall_atigpu:acquire_gl_objects: unsupported");
	return(0); 
}



/* 
 * XXX The *_safe versions of read/write/copy_buffer should be used for
 * XXX careful treatment of memory region overlap.  This can be added as
 * XXX a runtime option that simply modifies the cmdcall table. -DAR
 */

cmdcall_t cmdcall_atigpu[] = {
	0,
	ndrange_kernel,
	task,
	native_kernel,
	read_buffer,	
	write_buffer,	
	copy_buffer,	
	read_image,
	write_image,
	copy_image,
	copy_image_to_buffer,
	copy_buffer_to_image,
	map_buffer,
	map_image,
	unmap_mem_object,
	marker,
	acquire_gl_objects,
	release_gl_objects
};


