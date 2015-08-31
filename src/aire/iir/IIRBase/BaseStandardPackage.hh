#ifndef BASE_STANDARD_PACKAGE_HH
#define BASE_STANDARD_PACKAGE_HH

#include "savant_config.hh"
#include "StandardPackage.hh"
#include "IIRBase_PackageDeclaration.hh"

class BaseStandardPackage : public virtual StandardPackage,
			    public virtual IIRBase_PackageDeclaration {
public:
  IIR *convert_tree(plugin_class_factory *factory);

protected:
  BaseStandardPackage(){}
  virtual ~BaseStandardPackage(){}
};

#endif
