
#ifndef IIRBASE_ACCESS_TYPE_DEFINITION_HH
#define IIRBASE_ACCESS_TYPE_DEFINITION_HH

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
#include "IIRBase_TypeDefinition.hh"
#include "IIR_AccessTypeDefinition.hh"

class IIR_TypeDefinition;
class IIR_AccessTypeDefinition;
class IIR_ScalarTypeDefinition;

namespace savant {
  template <class type> class set;
}

class IIRBase_AccessTypeDefinition : public virtual IIRBase_TypeDefinition, public virtual IIR_AccessTypeDefinition{

public:
  IIR_Kind get_kind() const {return IIR_ACCESS_TYPE_DEFINITION;}
  const IIR_Char *get_kind_text() const {return "IIR_AccessTypeDefinition";}

  static IIR_AccessTypeDefinition *get( IIR_TypeDefinition *designated_type );

  void set_designated_type( IIR_TypeDefinition *designated_type);

  IIR_TypeDefinition *get_designated_type();
  IIR_ScalarTypeDefinition *get_resolved_index_subtype();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_element();
  IIR_Boolean is_access_type() { return TRUE; }
  IIR_Boolean is_scalar_type();
  IIR_Boolean is_array_type();
  IIR_Boolean is_unconstrained_array_type();
  IIR_Boolean is_record_type();
  
  IIR_TypeDefinition *get_element_subtype();
  void set_element_subtype( IIR_TypeDefinition * );

  savant::set<IIR_Declaration> *find_declarations( IIR_Name *);

  void publish_vhdl_decl(ostream &);
  void publish_vhdl_subtype_decl(ostream &);

protected:
  IIRBase_AccessTypeDefinition();
  virtual ~IIRBase_AccessTypeDefinition() = 0;
    
private:
  IIR_TypeDefinition *access_for_type;
};
#endif
