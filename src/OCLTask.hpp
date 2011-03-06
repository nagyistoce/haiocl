#ifndef HAI_TASK_HPP
#define HAI_TASK_HPP

namespace Hai {
  namespace OCL {
	// -- OCLTask -------------------------------------
	struct OCLTask {
	  // -- NDRange parameters ----------------------------
	  cl_kernel* kernel;
	  cl_uint work_dim;
	  size_t* global_work_offset;
	  size_t* global_work_size;
	  size_t* local_work_size;
	  cl_uint num_events_in_wait_list;
	  const cl_event* event_wait_list;
	  cl_event *event;
	
	  // --inputs and outputs memory objects ------------------------------
	  cl_mem in_binary;
	  cl_mem in_schema;
	  cl_mem in_size;
	
	  cl_mem out_binary;
	  cl_mem out_schema;
	  cl_mem out_size;
	
	  OCLTask();
	};
  }
}
#enidif
