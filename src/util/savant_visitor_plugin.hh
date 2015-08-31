#ifndef SAVANT_VISITOR_PLUGIN
#define SAVANT_VISITOR_PLUGIN


#include "savant_config.hh"
#include "savant_plugin_base.hh"

class HelloClass;
class WorldClass;

class savant_visitor_plugin : public savant_plugin_base {
public:
  //Visitor functions for every node type need to be declared here eventually.
  virtual void VisitHello(HelloClass* )=0;
  virtual void VisitWorld(WorldClass* )=0;
  virtual char* plugin_purpose()=0;
  virtual char* plugin_description()=0;

  virtual ~savant_visitor_plugin()=0;

protected:
  savant_visitor_plugin();
};

#endif
