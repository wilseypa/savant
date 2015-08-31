
#ifndef IIRBASE_ENUMERATION_LITERAL_HH
#define IIRBASE_ENUMERATION_LITERAL_HH

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
#include "IIR_EnumerationLiteral.hh"

class IIR_EnumerationTypeDefinition;
class IIR_AttributeSpecificationList;

class IIRBase_EnumerationLiteral : public virtual IIRBase_Declaration,
				   public virtual IIR_EnumerationLiteral{
public:
  // List Accessor(s)
  IIR_AttributeSpecificationList *get_attributes();
  void                           set_attributes(IIR_AttributeSpecificationList *new_attributes);

  IIR_Kind get_kind() const {return IIR_ENUMERATION_LITERAL;}
  const IIR_Char *get_kind_text() const {return "IIR_EnumerationLiteral";}

  void set_position( IIR *position );
  IIR *get_position();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_ascending_range();
  IIR_Boolean is_resolved();
  IIR_Boolean is_character_literal();
  IIR_Boolean is_locally_static();

  IIR_TypeDefinition *get_subtype() { return IIRBase::get_subtype();}

  declaration_type get_declaration_type();

  ostream &print( ostream & );
  void publish_vhdl(ostream &);
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_EnumerationLiteral();
  virtual ~IIRBase_EnumerationLiteral() = 0;
    
private:
  // List Variable(s)
  IIR_AttributeSpecificationList *attributes;

  IIR *my_position;
};
#endif
