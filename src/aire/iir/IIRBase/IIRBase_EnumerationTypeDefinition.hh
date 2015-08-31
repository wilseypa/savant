
#ifndef IIRBASE_ENUMERATION_TYPE_DEFINITION_HH
#define IIRBASE_ENUMERATION_TYPE_DEFINITION_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_ScalarTypeDefinition.hh"
#include "IIR_EnumerationTypeDefinition.hh"

class IIRBase_EnumerationTypeDefinition : public virtual IIRBase_ScalarTypeDefinition,
					  public virtual IIR_EnumerationTypeDefinition{

public:
  // List Accessor(s)
  IIR_EnumerationLiteralList *get_enumeration_literals();
  void set_enumeration_literals(IIR_EnumerationLiteralList *new_enumeration_literals);

  IIR_Kind get_kind() const { return IIR_ENUMERATION_TYPE_DEFINITION; }
  const IIR_Char *get_kind_text() const { return "IIR_EnumerationTypeDefinition"; }
  IIR_FunctionDeclaration* get_resolution_function() { return NULL; }

  IIR *convert_tree(plugin_class_factory *factory);
  IIR_Boolean is_enumeration_type(){ return true; }

  savant::set<IIR_Declaration> *find_declarations( IIR_TextLiteral * );
  savant::set<IIR_Declaration> *find_declarations( IIR_Name *  );

  IIR_Boolean is_character_type();
  IIR_Boolean is_discrete_type(){ return true;  }
  
  ostream& print(ostream&);
  void publish_vhdl_type_decl(ostream &);
protected:
  IIRBase_EnumerationTypeDefinition();
  virtual ~IIRBase_EnumerationTypeDefinition() = 0;
    
private:
  // List Variable(s)
  IIR_EnumerationLiteralList *enumeration_literals;

};
#endif
