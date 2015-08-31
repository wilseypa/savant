#ifndef FAKE_OSTRING_STREAM_H
#define FAKE_OSTRING_STREAM_H

#include "savant_config.hh"
#include <savant-config.h>
#include <strstream.h>
#include <string>
using std::string;

/** This class is a really really poor workaround for a missing
    "ostringstream".  It should only be used in the case where no <sstream>
    header is available as it probably is illegal and it most certainly
    leaks memory very badly. 

    The whole reason that this class exists is that sstream became available
    in g++ 2.95.4 and g++ 3.0, but it wasn't before then.  New code should use
    sstream/ostringstream, but if it's not available, this is a hacked workaround.
*/


class fake_ostringstream : public ostrstream {
public:
  fake_ostringstream(){}
  ~fake_ostringstream(){}

  string str () const {
    *(const_cast<fake_ostringstream *>(this)) << ends;
    char *foo = const_cast<fake_ostringstream *>(this)->ostrstream::str();
    return string(foo);
    // Note that we can't safely delete "foo" as str could get called multiple
    // times and we need to keep returning the same stream.
  }

private:
  
};

#endif
