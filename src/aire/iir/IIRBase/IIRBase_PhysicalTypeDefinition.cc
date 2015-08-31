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

#include "savant.hh"
#include "plugin_class_factory.hh"
#include "IIRBase_PhysicalTypeDefinition.hh"
#include "IIR_TextLiteral.hh"
#include "IIR_UnitList.hh"

IIRBase_PhysicalTypeDefinition::IIRBase_PhysicalTypeDefinition()  :
  units(0),
  primary_unit(0){}

IIRBase_PhysicalTypeDefinition::~IIRBase_PhysicalTypeDefinition(){
  delete units;
  units = 0;
  delete primary_unit;
  primary_unit = 0;
}

void 
IIRBase_PhysicalTypeDefinition::set_primary_unit( IIR_PhysicalUnit *unit) {
  ASSERT( !is_subtype() );
  primary_unit = unit;
}


IIR_PhysicalUnit *
IIRBase_PhysicalTypeDefinition::get_primary_unit() {
  if( is_subtype() ){
    ASSERT( primary_unit == 0 );
    return dynamic_cast<IIR_PhysicalTypeDefinition *>(get_base_type())->get_primary_unit();
  }
  else{
    ASSERT( primary_unit != 0 );
    return primary_unit;
  }
}

// List Accessor(s)
IIR_UnitList *
IIRBase_PhysicalTypeDefinition::get_units() {
  if( is_subtype() ){
    ASSERT( units == 0 );
    return dynamic_cast<IIR_PhysicalTypeDefinition *>(get_base_type())->get_units();
  }
  else{
    if( units == 0 ){
      units = get_class_factory()->new_IIR_UnitList();
    }
    return units;
  }
}


void
IIRBase_PhysicalTypeDefinition::set_units(IIR_UnitList *new_units) {
  ASSERT( !is_subtype() );
  ASSERT(new_units != NULL);
  delete units;
  units = new_units;
}

IIR *
IIRBase_PhysicalTypeDefinition::convert_tree(plugin_class_factory *factory) {
  // Get the node itself
  IIRBase_PhysicalTypeDefinition *new_node =
    dynamic_cast<IIRBase_PhysicalTypeDefinition *>
    (IIRBase_ScalarTypeDefinition::convert_tree(factory));

  // Process the variables
  new_node->units = dynamic_cast<IIR_UnitList *>(convert_node(units, factory));
  new_node->primary_unit = dynamic_cast<IIR_PhysicalUnit *>(convert_node(primary_unit, factory));

  return new_node;
}

void 
IIRBase_PhysicalTypeDefinition::publish_vhdl_type_decl(ostream &vhdl_out) {
  vhdl_out << " range ";
  get_base_type_left()->publish_vhdl(vhdl_out);

  ASSERT(get_direction()->get_kind() == IIR_ENUMERATION_LITERAL);

  if( is_ascending_range() == TRUE ){
    vhdl_out << " to ";
  }
  else{
    vhdl_out << " downto ";
  }

  get_base_type_right()->publish_vhdl(vhdl_out);
  vhdl_out << "\n";
  vhdl_out << "  units\n    ";
  get_primary_unit()->get_declarator()->publish_vhdl(vhdl_out);
  vhdl_out << ";\n";
  get_units()->publish_vhdl(vhdl_out);
  vhdl_out << "  end units";
}
