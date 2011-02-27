#include "OCL.hpp"

static OCL* OCL::getInstance() {
  if (OCL::oclInstance == NULL) {
    OCL::oclInstance = new OCL();
  }
  return OCL::oclInstance;
}

static int OCL::freeInstance() {
  return 0;
}

OCL::OCL() {
  // initialize platform_id
  // initialize device_id
  // initialize queue_id
  // initialize context
}
