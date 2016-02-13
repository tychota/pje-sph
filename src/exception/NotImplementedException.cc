#include "exception/NotImplementedException.hh"


NotImplementedException::NotImplementedException(const char *error) : errorMessage(error) { };

NotImplementedException::NotImplementedException() : NotImplementedException("Functionality not yet implemented!"){ }

const char *NotImplementedException::what() const noexcept { return errorMessage.c_str(); }
