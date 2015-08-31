#include "BaseStandardPackage.hh"
#include "IIR_Identifier.hh"
#include "IIR_LibraryDeclaration.hh"
#include "IIR_AccessSubtypeDefinition.hh"
#include "IIR_IntegerSubtypeDefinition.hh"
#include "IIR_FloatingSubtypeDefinition.hh"

IIR *
BaseStandardPackage::convert_tree( plugin_class_factory *factory ){
  // Get the node itself
  StandardPackage *new_node =
    dynamic_cast<StandardPackage *>(IIRBase_PackageDeclaration::convert_tree(factory));

  new_node->set_declarator( 
    dynamic_cast<IIR_Identifier *>(convert_node( get_declarator(), factory ) )
    );
  
  new_node->set_std_decl(
    dynamic_cast<IIR_LibraryDeclaration *>(convert_node(get_std_decl(),
							  factory))
    );

  new_node->set_savant_null_type_definition(
    dynamic_cast<IIR_AccessSubtypeDefinition *>(convert_node(get_savant_null_type_definition(),
							       factory))
    );

  new_node->set_savant_universal_integer(
    dynamic_cast<IIR_IntegerSubtypeDefinition *>(convert_node(get_savant_universal_integer(),
								factory))
    );

  new_node->set_savant_universal_real(
    dynamic_cast<IIR_FloatingSubtypeDefinition *>(convert_node(get_savant_universal_real(),
								 factory))
    );

  return new_node;
}
