
#ifndef IIRBASE_PACKAGE_BODY_DECLARATION_HH
#define IIRBASE_PACKAGE_BODY_DECLARATION_HH

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
#include "IIRBase_LibraryUnit.hh"
#include "IIR_PackageBodyDeclaration.hh"

class IIR_DeclarationList;
class IIRBase_PackageBodyDeclaration : public virtual IIRBase_LibraryUnit, public virtual IIR_PackageBodyDeclaration{

public:
  // List Accessor(s)
  IIR_DeclarationList *get_package_declarative_part();
  void                set_package_declarative_part(IIR_DeclarationList *new_package_declarative_part);

  IIR_Kind get_kind() const {return IIR_PACKAGE_BODY_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_PackageBodyDeclaration";}

  IIR *convert_tree(plugin_class_factory *factory);
  
  declaration_type get_declaration_type();
  IIR_Boolean is_secondary_unit(){ return TRUE; }

  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_PackageBodyDeclaration();
  virtual ~IIRBase_PackageBodyDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_DeclarationList *package_declarative_part;

};
#endif
