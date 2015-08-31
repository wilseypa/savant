
#ifndef IIRBASE_ALIAS_DECLARATION_HH
#define IIRBASE_ALIAS_DECLARATION_HH

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
#include "IIRBase_Declaration.hh"
#include "IIR_AliasDeclaration.hh"

class IIR_TypeDefinition;

class IIRBase_AliasDeclaration : public virtual IIRBase_Declaration,
				 public virtual IIR_AliasDeclaration{

public:
  IIR_Kind get_kind() const {return IIR_ALIAS_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_AliasDeclaration";}

  void set_name(IIR*);
  IIR *get_name();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_signal();
  IIR_Boolean is_locally_static();
  IIR_Boolean is_object();
  IIR_Boolean is_type();
  IIR_Boolean is_variable();

  IIR_Boolean is_access_type();
  IIR_Boolean is_array_type();
  IIR_Boolean is_enumeration_type();
  IIR_Boolean is_file_type();
  IIR_Boolean is_record_type();
  IIR_Boolean is_scalar_type();
 
  declaration_type get_declaration_type();
  IIR_Declaration *get_prefix_declaration() { return this; }
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_AliasDeclaration();
  virtual ~IIRBase_AliasDeclaration() = 0;
    
private:
  IIR *name;
};

#endif
