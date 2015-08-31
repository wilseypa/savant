
#ifndef IIRBASE_LIBRARY_UNIT_HH
#define IIRBASE_LIBRARY_UNIT_HH

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
#include "IIRBase_Declaration.hh"
#include "IIR_LibraryUnit.hh"

class IIR_AttributeSpecificationList;
class IIR_DeclarationList;
class IIR_TypeDefinition;

class IIRBase_LibraryUnit : public virtual IIRBase_Declaration, public virtual IIR_LibraryUnit{

public:
  // List Accessor(s)
  IIR_DeclarationList                  *get_context_items();
  IIR_AttributeSpecificationList       *get_attributes();
  void                                 set_context_items(IIR_DeclarationList *new_context_items);
  void                                 set_attributes(IIR_AttributeSpecificationList *new_attributes);

  IIR *convert_tree(plugin_class_factory *factory);

  /**
     Library Units don't have subtypes.
  */
  IIR_TypeDefinition *get_subtype(){ return NULL; }
  /**
     Returns the library declaration that this unit is declared in.  Should
     never be NULL.  
  */
  IIR_LibraryDeclaration *get_library();
  IIR_Boolean is_primary_unit();
  IIR_Boolean is_secondary_unit();

  virtual void publish_vhdl_binding_name(ostream &);
  virtual void publish_vhdl_with_library_name(ostream &vhdl_out);
protected:
  
  IIRBase_LibraryUnit();
  virtual ~IIRBase_LibraryUnit() = 0;
    
private:
  // List Variable(s)
  IIR_DeclarationList                  *context_items;
  IIR_AttributeSpecificationList       *attributes;

};
#endif
