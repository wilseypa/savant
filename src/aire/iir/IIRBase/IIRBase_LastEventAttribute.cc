
// Copyright (c) The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

#include "IIRBase_Identifier.hh"
#include "IIRBase_LastEventAttribute.hh"
#include "IIR_DesignFile.hh"
#include "IIR_PhysicalSubtypeDefinition.hh"
#include "IIR_TypeDefinition.hh"
#include "StandardPackage.hh"

IIRBase_LastEventAttribute::IIRBase_LastEventAttribute() {}

IIRBase_LastEventAttribute::~IIRBase_LastEventAttribute() {}

IIR_TypeDefinition *
IIRBase_LastEventAttribute::get_subtype(){
  return get_design_file()->get_standard_package()->get_time_type();
}
  
IIR_TextLiteral *
IIRBase_LastEventAttribute::build_attribute_name() {
  const char *name = "last_event";
  return IIRBase_Identifier::get( name, strlen(name), get_design_file()->get_class_factory());
}

void 
IIRBase_LastEventAttribute::publish_vhdl(ostream &vhdl_out) {
  ASSERT( get_prefix() != NULL );
  ASSERT(get_prefix()->is_resolved() == TRUE );
  ASSERT(get_prefix()->is_signal() == TRUE );
  get_prefix()->publish_vhdl(vhdl_out);
  vhdl_out << "'LAST_EVENT ";
}
