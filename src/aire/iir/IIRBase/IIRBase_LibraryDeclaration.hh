
#ifndef IIRBASE_LIBRARY_DECLARATION_HH
#define IIRBASE_LIBRARY_DECLARATION_HH

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
#include "IIR_LibraryDeclaration.hh"

class IIR_LibraryUnitList;
class IIR_TypeDefinition;

class IIRBase_LibraryDeclaration : public virtual IIRBase_Declaration, public virtual IIR_LibraryDeclaration{

public:
  // List Accessor(s)
  IIR_LibraryUnitList *get_primary_units();
  void                set_primary_units(IIR_LibraryUnitList *new_primary_units);

  IIR_Kind get_kind() const {return IIR_LIBRARY_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_LibraryDeclaration";}

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_TypeDefinition *get_subtype( ){ return NULL; }

  void set_path_to_directory( const string &new_path );
  const string &get_path_to_directory();

  bool is_work_library();

  declaration_type get_declaration_type();

  savant::set<IIR_Declaration> *find_declarations( IIR_Name * );
  void publish_vhdl_decl( ostream & );
protected:
  IIRBase_LibraryDeclaration();
  virtual ~IIRBase_LibraryDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_LibraryUnitList *primary_units;

  // This is a path (either relative or absolute, depending on how the
  // library manager was able to find it) to the directory that this declaration
  // is representing...
  string path_to_directory;
};
#endif
