
#ifndef IIRBASE_LIBRARY_CLAUSE_HH
#define IIRBASE_LIBRARY_CLAUSE_HH

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
#include "IIR_LibraryClause.hh"

class IIR_Identifier;

class IIRBase_LibraryClause : public virtual IIRBase_Declaration,
			      public virtual IIR_LibraryClause{

public:

  IIR_Kind get_kind() const {return IIR_LIBRARY_CLAUSE;}
  const IIR_Char *get_kind_text() const {return "IIR_LibraryClause";}

  void set_logical_name(IIR_Identifier* logical_name);
  IIR_Identifier* get_logical_name();

  void set_library_declaration( IIR_LibraryDeclaration *new_library_declaration );
  IIR_LibraryDeclaration *get_library_declaration();


  IIR *convert_tree(plugin_class_factory *factory);

  bool is_work_library();

  void publish_vhdl(ostream &);
  void publish_vhdl_decl(ostream &);
protected:
  
  IIRBase_LibraryClause();
  virtual ~IIRBase_LibraryClause() = 0;
    
private:
  IIR_Identifier *logical_name;
  IIR_LibraryDeclaration *library_declaration;
};
#endif
