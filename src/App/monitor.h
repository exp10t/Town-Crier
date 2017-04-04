#pragma once
#include "stdint.h"
#include "bookkeeping/database.hxx"
#include <sgx_edger8r.h>
#include <atomic>

#include "Constants.h"

enum MONITOR_EXCEPTION {
    EX_GET_BLOCK_NUM,
    EX_CREATE_FILTER,
    EX_GET_FILTER_LOG,
    EX_NOTHING_TO_DO,
    EX_SEND_TRANSACTION,
    EX_HANDLE_REQ,
};

class Monitor {
 private:
  OdbDriver &driver;
  const sgx_enclave_id_t eid;
  const int nonceOffset;

  const std::atomic_bool &quit;

  const static int maxRetry = 5;
  const static int nothingToDoSleepSec = 5;
  bool isSleeping;

 public:
  Monitor(OdbDriver &driver, sgx_enclave_id_t eid, int nonceOffset, std::atomic_bool &quit) :
      driver(driver), eid(eid), nonceOffset(nonceOffset), quit(quit), isSleeping(false) {}

  void loop();
};

class NothingTodoException : public std::exception {
 public:
  virtual char const * what() const noexcept {
    return "Nothing to do";
  }
};