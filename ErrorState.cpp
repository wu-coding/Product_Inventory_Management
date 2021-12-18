#include <iostream>
#include <cstring>
#include "ErrorState.h"

using std::endl;
using std::strncpy;
using std::strlen;

namespace AMA {
  
  ErrorState::ErrorState(const char* errorMessage)
  {
    if (errorMessage != nullptr)
    {
    errorStore = new char[strlen(errorMessage)+1];
    strcpy(errorStore, errorMessage);
    }
    else {
      errorStore = nullptr;
    }
  }

  ErrorState::~ErrorState()
  {
    clear();
  }
  void ErrorState::clear()
  {
    delete [] errorStore;
    errorStore = nullptr;
  }
  bool ErrorState::isClear() const
  {
    return (errorStore == nullptr) ? true : false;
  }
  void ErrorState::message(const char* str)
  {
    clear();
    errorStore = new char[strlen(str)+1];
    strcpy(errorStore, str);
    
  }
  const char* ErrorState::message()const {
    return errorStore;
  }
  std::ostream& operator<<(std::ostream& os, const ErrorState& passError)
  {
    if (!passError.isClear()) {
      os<< passError.message();
    }
    return os;
  }
}
