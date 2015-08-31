
#ifndef IIRBASE_ACCESS_SUBTYPE_DEFINITION_HH
#define IIRBASE_ACCESS_SUBTYPE_DEFINITION_HH

// Copyright (c) 1996-1999 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_AccessTypeDefinition.hh"
#include "IIR_AccessSubtypeDefinition.hh"

class IIR_TypeDefinition;
class IIR_FunctionDeclaration;
class IIR_AccessSubtypeDefinition;

class IIRBase_AccessSubtypeDefinition : public virtual IIRBase_AccessTypeDefinition,
					public virtual IIR_AccessSubtypeDefinition{
public:
  IIR_Kind get_kind() const {return IIR_ACCESS_SUBTYPE_DEFINITION;}
  const IIR_Char *get_kind_text() const {return "IIR_AccessSubtypeDefinition";}

  void set_designated_subtype( IIR_TypeDefinition *designated_type);
  IIR_TypeDefinition *get_designated_subtype();

  void set_resolution_function( IIR_FunctionDeclaration *resolution_function );
  IIR_FunctionDeclaration *get_resolution_function();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_subtype();
  IIR_Boolean is_locally_static(){ return TRUE; }

  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_AccessSubtypeDefinition();
  virtual ~IIRBase_AccessSubtypeDefinition() = 0;
    
private:
  IIR_FunctionDeclaration *my_resolution_function;
};
#endif
