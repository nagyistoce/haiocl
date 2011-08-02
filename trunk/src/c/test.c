#include <stdio.h>
#include <HAI/hai.h>

struct {
  void*     data;
  uint32_t  len;
  size_t    size;
} input_t;

typedef input_t output_t;

inline
size_t readTextFromFile(char* src, const char* filename) {
}

inline
size_t readInputFromFile(input_t* data, const char* filename) {
}

uint32_t setupSortKernelFromFile(int* input, int* output, size_t size) {
  const char* sort_src_filename = "sort.cl";
  char sort_src[10240];
  size_t sort_size = readTextFile(sort_src, sort_src_filename);
  uint32_t kid;
  HAI_kernel_prop_t sort_prop;
  sort_prop.global_work_size[0] = sort_prop.local_work_size[0] = 1;
  sort_prop.global_work_size[1] = sort_prop.local_work_size[1] = 1;
  sort_prop.global_work_size[2] = sort_prop.local_work_size[2] = 1;
  sort_prop.num_events_in_wait_list = 0;
  sort_prop.single_input_size = sort_prop.single_output_size = sizeof(uint32_t) * 100;
  sort_prop.max_input_size = sort_prop.single_output_size = sort_prop.single_input_size * 100;

  
  HAI_register_kernel(sort_src, sort_size, sort_prop, &kid);
  return kid;
}

int main(int argc, char **argv) {
  int i;
  int* sort_input;
  int* sort_output;
  uint32_t sort_id;
  size_t size;

  test_input = readInputData("testInput.txt", &size);
  test_output = (int*)malloc(size);
  
  sort_id = setupSortKernel(sort_input, sort_output, size);
  HAI_init();
  HAI_run();
  
  for (i = 0; i < 10; i ++) {
    HAI_enqueue_data(sort_id, test_input, input_size);
    HAI_wait();
    if (verify_output(test_output, test_output / sizeof(int)))
      printf("assertion failed.\n");
  }
  HAI_stop();
  HAI_release();

  free(test_output);
  free(test_input);
  return 0;
}
