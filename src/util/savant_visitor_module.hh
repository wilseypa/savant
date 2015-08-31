#ifndef SAVANT_VISITOR_MODULE
#define SAVANT_VISITOR_MODULE


#include "savant_config.hh"
#include "savant_module_base.hh"

class HelloClass;
class WorldClass;

class savant_visitor_module : public savant_module_base {
public:
  //Visitor functions for every node type need to be declared here eventually.
  virtual void VisitHello(HelloClass* )=0;
  virtual void VisitWorld(WorldClass* )=0;
  virtual char* module_purpose()=0;
  virtual char* module_description()=0;

  virtual ~savant_visitor_module()=0;

protected:
  savant_visitor_module();
};

#endif
