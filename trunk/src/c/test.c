#include <stdio.h>
#include <HAI/hai.h>

inline
int* readInputFromFile(const char* filename, int* n) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("can't open the file.\n");
		return NULL;
	}
	
	struct stat fp_stat;
	fstat(fileno(fp), &fp_stat);
	*n = fp_stat.st_size / sizeof(int);
	int* buf = (int*)malloc(fp_stat.st_size);
	fread(buf, sizeof(int), n, fp);
	fclose(fp);
}

uint32_t setupSortKernelFromFile(hai_buffer_t* output) {
  const char* sort_src_filename = "sort.cl";
  size_t sort_len;
  char* sort_src = HAI_read_source_file(sort_src_filename, &sort_len);
  
  // generate the notifier
  hai_notify_t notifier = HAI_notify_buffer(output);
 
  // setup kernel prop
  HAI_kernel_prop_t sort_prop;
  sort_prop.global_work_size[0] = sort_prop.local_work_size[0] = 1;
  sort_prop.global_work_size[1] = sort_prop.local_work_size[1] = 1;
  sort_prop.global_work_size[2] = sort_prop.local_work_size[2] = 1;
  sort_prop.num_events_in_wait_list = 0;
  sort_prop.single_input_size = sort_prop.single_output_size = sizeof(int) * 100;
  sort_prop.max_input_size = sort_prop.single_output_size = sizeof(int) * 100;

  // register the kernel
  HAI_register_kernel(sort_src, sort_len, sort_prop, notifier, &kid);
  return kid;
}

int main(int argc, char **argv) {
  int i;
  int* sort_input; 
  uint32_t sort_id;
  size_t nbyte;
  hai_buffer_t test_output;

  char *test_input = readInputFromFile("testInput.txt", &nbyte);
  HAI_init_buffer(&test_output, size);
  
  sort_id = setupSortKernelFromFile(test_output);
  
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
