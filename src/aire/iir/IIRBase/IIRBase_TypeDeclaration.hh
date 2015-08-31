
#ifndef IIRBASE_TYPE_DECLARATION_HH
#define IIRBASE_TYPE_DECLARATION_HH

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
#include "IIR_TypeDeclaration.hh"

class IIR_AttributeSpecificationList;
 
class IIRBase_TypeDeclaration : public virtual IIRBase_Declaration, public virtual IIR_TypeDeclaration{
public:
  // List Accessor(s)
  IIR_AttributeSpecificationList        *get_attributes();
  void                                  set_attributes(IIR_AttributeSpecificationList *new_attributes);

  IIR_Kind get_kind() const {return IIR_TYPE_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_TypeDeclaration";}

  void set_type(IIR_TypeDefinition* type);
  IIR_TypeDefinition* get_type();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_incomplete_type_declaration();
  IIR_Boolean is_type(){ return TRUE; }
  IIR_Boolean is_type_declaration(){ return TRUE; }
  IIR_Boolean is_locally_static();

  IIR_TypeDefinition *get_subtype();

  declaration_type get_declaration_type();

  savant::set<IIR_Declaration> *find_declarations( IIR_Name * );
  savant::set<IIR_Declaration> *find_declarations( IIR_TextLiteral * );

  // This varies depending on the definition.  For Scalar types the get/set operators
  // for AccessTypeDeclaration it builds the deallocate functions, etc.
  savant::set<IIR_Declaration> *get_implicit_declarations();
  void set_implicit_declarations( savant::set<IIR_Declaration> *);
  void publish_vhdl_decl(ostream &);
  void publish_vhdl_range(ostream &);
protected:
  IIRBase_TypeDeclaration();
  virtual ~IIRBase_TypeDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_AttributeSpecificationList *attributes;  
  IIR_TypeDefinition* type;

  savant::set<IIR_Declaration>  *implicit_declarations;
};

#endif
