
#ifndef IIRBASE_FUNCTION_DECLARATION_HH
#define IIRBASE_FUNCTION_DECLARATION_HH

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
#include "IIRBase_SubprogramDeclaration.hh"
#include "IIR_FunctionDeclaration.hh"

class IIRBase_FunctionDeclaration : public virtual IIRBase_SubprogramDeclaration, public virtual IIR_FunctionDeclaration{
public:
  IIR_Kind get_kind() const {return IIR_FUNCTION_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_FunctionDeclaration";}

  void set_pure(IIR_Pure purity);
  IIR_Pure get_pure();

  IIR_Boolean is_locally_static();

  void set_return_type( IIR_TypeDefinition* return_type);
  IIR_TypeDefinition* get_return_type();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_function_declaration(){ return TRUE; }
  IIR_Boolean is_operator();

  declaration_type get_declaration_type();
  savant::set<IIR_Declaration> *find_declarations( IIR_Name *){ return NULL;  }
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_FunctionDeclaration();
  virtual ~IIRBase_FunctionDeclaration() = 0;
    
private:
  IIR_Pure purity;
};
#endif
