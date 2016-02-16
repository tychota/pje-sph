#pragma once

#include <stdexcept>

class NotImplementedException : std::exception {
  public:
    NotImplementedException(const char * error);
    NotImplementedException();

    const char * what() const noexcept;

  private:
    std::string errorMessage;
};
