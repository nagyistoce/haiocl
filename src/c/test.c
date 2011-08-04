#include <stdio.h>
#include <HAI/hai.h>

inline
size_t readInputFromFile(input_t* data, const char* filename) {
}

uint32_t setupSortKernelFromFile(hai_buffer_t* output) {
  const char* sort_src_filename = "sort.cl";
  char sort_src[10240];
  size_t sort_size = readTextFromFile(sort_src, sort_src_filename);
  
  // generate the notifier
  hai_notify_t notifier = HAI_notify_to_buffer(output);
 
  // setup kernel prop
  HAI_kernel_prop_t sort_prop;
  sort_prop.global_work_size[0] = sort_prop.local_work_size[0] = 1;
  sort_prop.global_work_size[1] = sort_prop.local_work_size[1] = 1;
  sort_prop.global_work_size[2] = sort_prop.local_work_size[2] = 1;
  sort_prop.num_events_in_wait_list = 0;
  sort_prop.single_input_size = sort_prop.single_output_size = sizeof(int) * 100;
  sort_prop.max_input_size = sort_prop.single_output_size = sizeof(int) * 100;

  // register the kernel
  HAI_register_kernel(sort_src, sort_size, sort_prop, notifier, &kid);
  return kid;
}

int main(int argc, char **argv) {
  int i;
  int* sort_input; 
  uint32_t sort_id;
  size_t nbyte;
  char* test_input;
  hai_buffer_t test_output;

  test_input = readInputFromFile("testInput.txt", &size);
  HAI_init_buffer(&test_output, size);
  
  sort_id = setupSortKernelFromFile(test_output, size);
  
  HAI_init();
  HAI_run();
  
  for (i = 0; i < 10; i ++) {
    HAI_enqueue_data(sort_id, test_input, input_size);
    HAI_wait();
    if (verify_output(test_output.data, size / sizeof(int)))
      printf("assertion failed.\n");
  }
  
  HAI_stop();
  HAI_release();

  HAI_release_buffer(&test_output);  
  free(test_input);
  return 0;
}
