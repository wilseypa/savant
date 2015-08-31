
#ifndef IIRBASE_SUBTYPE_DECLARATION_HH
#define IIRBASE_SUBTYPE_DECLARATION_HH

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
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Declaration.hh"
#include "IIR_SubtypeDeclaration.hh"

class IIR_TypeDefinition;
class IIR_AttributeSpecificationList;

class IIRBase_SubtypeDeclaration : public virtual IIRBase_Declaration,
				   public virtual IIR_SubtypeDeclaration{
public:
  // List Accessor(s)
  IIR_AttributeSpecificationList *get_attributes();
  void                           set_attributes(IIR_AttributeSpecificationList *new_attributes);

  IIR_Kind get_kind() const {return IIR_SUBTYPE_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_SubtypeDeclaration";}

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_subtype_decl() { return TRUE; }
  IIR_Boolean is_type(){ return TRUE; }
  IIR_Boolean is_locally_static();

  declaration_type get_declaration_type();
  void publish_vhdl_decl(ostream &);
  void publish_vhdl_range(ostream &);
protected:
  IIRBase_SubtypeDeclaration();
  virtual ~IIRBase_SubtypeDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_AttributeSpecificationList *attributes;  
};

#endif
