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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------


#include "IIRBase_UseClause.hh"
#include "IIRBase_LibraryDeclaration.hh"
#include "IIRBase_TextLiteral.hh"
#include "IIRBase_Name.hh"
#include "IIR_DesignFile.hh"
#include "savant.hh"

IIRBase_UseClause::IIRBase_UseClause() :
  selected_name(0){}

IIRBase_UseClause::~IIRBase_UseClause(){
  delete selected_name;
  selected_name = 0;
}


void
IIRBase_UseClause::set_selected_name(IIR_Name* name) {
  selected_name = name;
}


IIR_Name*
IIRBase_UseClause::get_selected_name() {
  return selected_name;
}

IIR *
IIRBase_UseClause::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_UseClause *new_node = dynamic_cast<IIRBase_UseClause *>(IIRBase_Declaration::convert_tree(factory));

  // Process the variables
  new_node->selected_name = dynamic_cast<IIR_Name *>(convert_node(selected_name, factory));

  return new_node;
}

void 
IIRBase_UseClause::publish_vhdl(ostream &vhdl_out) {
  ASSERT(get_selected_name() != NULL);
  ASSERT(get_selected_name()->is_resolved());

  IIR_LibraryDeclaration *library = dynamic_cast<IIRBase_Name *>
    (get_selected_name())->get_library_declaration();
  if( library != NULL ){
    if( library == get_design_file()->get_work_library() && 
	IIRBase_TextLiteral::cmp( library->get_declarator(), "work" ) != 0 ){
      // Then this is the work library, but it's not called work...  We need to
      // emit a library declaration.
      vhdl_out << "library ";
      library->publish_vhdl( vhdl_out );
      vhdl_out << "; -- inserted by analyzer due to library renaming.\n";
    }
  }

  vhdl_out << "use ";
  get_selected_name()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
}

void
IIRBase_UseClause::publish_vhdl_decl(ostream &vhdl_out) {
  ASSERT(get_selected_name() != NULL);
  ASSERT(get_selected_name()->is_resolved());

  publish_vhdl(vhdl_out);
}
