
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



#include "IIRBase_SensitizedProcessStatement.hh"
#include "IIR_DesignatorList.hh"
#include "IIRBase_DeclarationList.hh"
#include "IIR_Label.hh"

IIRBase_SensitizedProcessStatement::IIRBase_SensitizedProcessStatement()  :
  sensitivity_list(0) { }

IIRBase_SensitizedProcessStatement::~IIRBase_SensitizedProcessStatement() {}

// List Accessor(s)
IIR_DesignatorList *
IIRBase_SensitizedProcessStatement::get_sensitivity_list() {
  ASSERT(sensitivity_list != NULL);
  return sensitivity_list;
}


void
IIRBase_SensitizedProcessStatement::set_sensitivity_list(IIR_DesignatorList *new_sensitivity_list) {
  ASSERT(new_sensitivity_list != NULL);
  delete sensitivity_list;
  sensitivity_list = new_sensitivity_list;
}

IIR *
IIRBase_SensitizedProcessStatement::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_SensitizedProcessStatement *new_node = dynamic_cast<IIRBase_SensitizedProcessStatement *>(IIRBase_ProcessStatement::convert_tree(factory));

  // Process the variables
  new_node->sensitivity_list = dynamic_cast<IIR_DesignatorList *>(convert_node(sensitivity_list, factory));

  return new_node;
}

void 
IIRBase_SensitizedProcessStatement::publish_vhdl(ostream &vhdl_out) {

  publish_vhdl_stmt_label(vhdl_out);

  if (get_postponed() == true) {
    vhdl_out << "postponed ";
  }
    
  vhdl_out << "process";

  if(get_sensitivity_list()->size() != 0) {
    vhdl_out << " (";
    get_sensitivity_list()->publish_vhdl(vhdl_out);
    vhdl_out << ")\n";
  }
    
  dynamic_cast<IIRBase_DeclarationList *>(get_process_declarative_part())->publish_vhdl_decl(vhdl_out);
  vhdl_out << "\nbegin\n";
  get_process_statement_part()->publish_vhdl(vhdl_out);
  vhdl_out << "end";
  if (get_postponed() == true) {
    vhdl_out << " postponed";
  }
  vhdl_out << " process";
  if (get_label() != NULL) {
    vhdl_out << " ";
    get_label()->publish_vhdl(vhdl_out);
  }
  vhdl_out << ";\n\n";
}
