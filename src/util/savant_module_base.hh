#ifndef SAVANT_MODULE_BASE
#define SAVANT_MODULE_BASE


#include "savant_config.hh"
#include <clutils/PluginBase.h>

class savant_module_base : public PluginBase {
public:
  ~savant_module_base();

protected:
  savant_module_base();

};


#endif
