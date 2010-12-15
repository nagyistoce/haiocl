#ifndef DATA_ITEM_HPP
#define DATA_ITEM_HPP

#ifndef MAX_KERNEL_LEN
#define MAX_KERNEL_LEN 10240
#endif

class DataItem {
public:
  inline DataItem(uint32_t _ikey, uint32_t _okey,
		   const char* _kernel, bool isCompile):
	ikey_(_ikey), _okey(oKey_) {
	kernel_len = strlen(_kernel);
	if (kernel_len > MAX_KERNEL_LEN) {
	  // TODO: print error
	}

	memcpy(_kernel, kernel_src, sizeof(char) * kernel_len);
	if (isCompile)
	  if (compileKernel()) {
		// TODO: print error
	  }
  }
  
  inline ~DataItem() {};
  
  inline int compileKernel() {
	return 0;
  }
  
  inline int setIKey(uint32_t _ikey) {
	iKey_ = _ikey;
	return 0;
  }
  
  inline int setOKey(uint32_t _okey) {
	oKey_ = _okey;
  }
  
  inline char* getNextUnit(int *buf) {
	int ret = (buf_size > unit_size) ? unit_size : buf_size;
	return 0;
  }
  
private:  
  char kernel_src[MAX_KERNEL_LEN];
  uint32_t kernel_len;
  void* kernel_binary;

  uint32_t ikey_;
  uint32_t oKey_;
  uint32_t curPos;
  deque<char> data_;
};

#endif
