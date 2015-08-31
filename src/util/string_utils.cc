#include "string_utils.hh"
#include <sstream>
using std::ostringstream;

string ptr_to_string( const void *ptr ){
  string retval;
  ostringstream outstream;
  
  outstream << ptr;
  
  retval = outstream.str();

  return retval;
}
