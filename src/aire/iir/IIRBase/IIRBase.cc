
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

#include "IIRBase.hh"
#include "IIRBase_DesignFile.hh"
#include "IIRBase_List.hh"
#include "IIRBase_Operator.hh"
#include "IIRBase_TypeDefinition.hh"
#include "IIR_Identifier.hh"
#include "StandardPackage.hh"
#include "savant.hh"
#include "error_func.hh"
#include "plugin_class_factory.hh"
#include <sstream>
#include <typeinfo>
using std::ostringstream;

IIRBase::IIRBase() : converted_node( NULL ),
                     _my_design_file( NULL ),
		     iir_line_number( 0 ),
                     already_entered( false ),
                     subtype( NULL)
{
#ifdef EXTRA_LOCATERS
  iir_column_offset = -1;
  iir_character_offset = -1;
#endif

#ifdef SCHEMATIC_INFO
  iir_sheet_name = NULL;  
  iir_x_coordinate = -1;
  iir_y_coordinate = -1;
#endif
}

string
IIRBase::get_implementation_class() const {
  return typeid(*this).name();
}

void 
IIRBase::set_file_name( IIR_Identifier *file_name, plugin_class_factory *factory ){
  ASSERT(factory != NULL);
  _my_design_file = factory->new_IIR_DesignFile();
  _my_design_file->set_name( file_name );
}

IIR_Identifier *
IIRBase::get_file_name(){
  if( _my_design_file == NULL ){
    return NULL;
  }
  else{
    return _my_design_file->get_name();
  }
}


IIRBase::~IIRBase() {}

IIR *
IIRBase::get_value() {
  return NULL;
}

void 
IIRBase::set_base_info( IIR_DesignFile    *design_file,
                        int               line_number,
                        int               column_offset, 
                        int               character_offset ) {
  ASSERT( design_file != NULL );
  
  set_design_file( design_file );
  set_line_number( line_number );
  
#ifdef EXTRA_LOCATERS
  set_column_offset( column_offset );
  set_character_offset( character_offset );
#else
  (void)column_offset;
  (void)character_offset;
#endif
}

void 
IIRBase::copy_location(const IIR *source, IIR *dest) {
  ASSERT( source != NULL || parse_error == true  );
  ASSERT( dest != NULL || parse_error == true );
  ASSERT( source->get_design_file() != NULL || parse_error == true );
  ASSERT( source->get_line_number() != -1 || parse_error == true );
  
#ifdef EXTRA_LOCATERS
  ASSERT( source->get_column_offset() != -1 || parse_error == true );
  ASSERT( source->get_character_offset() != -1 || parse_error == true );
#endif
  
#ifdef EXTRA_LOCATERS
  dest->set_base_info( source->get_design_file(), source->get_line_number(),
                       source->get_column_offset(), source->get_character_offset() );
#else
  dest->set_base_info( source->get_design_file(), source->get_line_number(), 0 ,0 );
#endif        
}
       
void
IIRBase::copy_location(IIR *dest) {
  copy_location(this, dest);
}

IIR* 
IIRBase::convert_tree(plugin_class_factory *factory) {
  //   The basic approach is to check for an existing copy.
  // Otherwise we create a new version of whatever we are, 
  // and add it to the reference list
  IIRBase* new_node = converted_node;
  
  if (new_node == NULL) {
    // Special case for Standard Packages, since there is no Standard Package kind
    if( dynamic_cast<StandardPackage *>(this) != NULL ){
      new_node = dynamic_cast<IIRBase *>(factory->new_StandardPackage());
    } else {
      new_node = dynamic_cast<IIRBase *>(factory->get_new_class(get_kind()));
    }

    converted_node = new_node;

    // Process the variables
    // Lists don't have a design file or subtype associated with them
    if (_my_design_file != NULL) 
      new_node->_my_design_file = dynamic_cast<IIR_DesignFile *>(convert_node(_my_design_file, factory));
    if (subtype != NULL)
      new_node->subtype = dynamic_cast<IIR_TypeDefinition *>(convert_node(subtype, factory));

    new_node->iir_line_number = iir_line_number;

#ifdef SCHEMATIC_INFO
    new_node->iir_x_coordinate = iir_x_coordinate;
    new_node->iir_y_coordinate = iir_y_coordinate;
    new_node->iir_sheet_name = dynamic_cast<IIR_Identifier *>(iir_sheet_name->convert_node(factory));
#endif

#ifdef EXTRA_LOCATERS
    new_node->iir_column_offset = iir_column_offset;
    new_node->iir_character_offset = iir_character_offset;    
#endif
  }

  return new_node;
}

IIR*
IIRBase::convert_node(IIR* node, plugin_class_factory *factory) {
  IIR   *result = NULL;

  if (node != NULL) {
    if (dynamic_cast<IIRBase *>(node)->converted_node == NULL) {
      result =  node->convert_tree(factory);
    } else {
      result = dynamic_cast<IIRBase *>(node)->converted_node;
    }
  }

  return result;
}

IIR_Boolean
IIRBase::is_ascending_range() {
  ASSERT(0);
  return false;
}

IIR_Boolean 
IIRBase::is_locally_static(){
  _report_undefined_fn("is_locally_static()");
  return FALSE;
}

IIR_TypeDefinition *
IIRBase::get_subtype() {
  return subtype;
}

void
IIRBase::set_subtype(IIR_TypeDefinition *new_type) {
  subtype = new_type;
}

plugin_class_factory *
IIRBase::get_class_factory(){
  ASSERT( get_design_file() != 0 );
  ASSERT( get_design_file()->get_class_factory() != 0 );
  return get_design_file()->get_class_factory();
}

void 
IIRBase::_report_undefined_fn(const char *fn_name) {
  ostringstream os;
  os << fn_name << " not defined for node: " << get_kind_text();
  report_error( this, os.str() );
  abort();
}

IIR_SignalKind
IIRBase::get_signal_kind() {
  _report_undefined_fn("get_signal_kind()");
  return IIR_NO_SIGNAL_KIND;
}

IIR_Boolean
IIRBase::is_guard_signal() {
  if( is_signal() == TRUE && get_signal_kind() != IIR_NO_SIGNAL_KIND ){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

IIR_Boolean
IIRBase::is_access_type(){
  ASSERT( get_subtype() );
  return get_subtype()->is_access_type();
}

IIR_Boolean
IIRBase::is_array_type(){
  ASSERT( get_subtype() );
  return get_subtype()->is_array_type();
}

IIR_Boolean
IIRBase::is_enumeration_type(){
  ASSERT( get_subtype() );
  return get_subtype()->is_enumeration_type();
}

IIR_Boolean
IIRBase::is_file_type(){
  ASSERT( get_subtype() );
  return get_subtype()->is_file_type();
}

IIR_Boolean
IIRBase::is_record_type(){
  ASSERT( get_subtype() );
  return get_subtype()->is_record_type();
}

IIR_Boolean
IIRBase::is_scalar_type(){
  ASSERT( get_subtype() );
  return get_subtype()->is_scalar_type();
}

IIR_TextLiteral *
IIRBase::get_prefix_string( ) {
  _report_undefined_fn("get_prefix_string()");
  return NULL;
}

IIR_Int32 
IIRBase::get_num_indexes( ){
  _report_undefined_fn("get_num_indexes()");
  return -1;
}

ostream&
IIRBase::print(ostream& os) {
  _report_undefined_fn("ostream& print(ostream&)");
  return os;
}

IIR_TextLiteral *
IIRBase::get_declarator() {
  ASSERT( dynamic_cast<IIR_Declaration *>(this) != NULL || get_kind() == IIR_SIMPLE_NAME);
  _report_undefined_fn("get_declarator()");
  return NULL;
}

IIR_Declaration* 
IIRBase::get_prefix_declaration() {
  _report_undefined_fn("get_prefix_declaration()");
  return NULL;
}

void 
IIRBase::publish_vhdl_type_decl(ostream &vhdl_out) {
  publish_vhdl_decl(vhdl_out);
}

void
IIRBase::publish_vhdl_subtype_decl(ostream &vhdl_out) {
  publish_vhdl_decl(vhdl_out);
}

void 
IIRBase::publish_vhdl( ostream & ){
  _report_undefined_fn("publish_vhdl(ostream &)");
}

void 
IIRBase::publish_vhdl_range( ostream & ){
  _report_undefined_fn("publish_vhdl_range(ostream &)");
}

void 
IIRBase::publish_vhdl_decl(ostream & ){
  _report_undefined_fn("publish_vhdl_decl(ostream &)");
}

void
IIRBase::publish_vhdl_operator( ostream & ){
  _report_undefined_fn("publish_vhdl_operator(ostream &)");
}

IIRBase_Operator::Precedence
IIRBase::get_precedence(){
  return IIRBase_Operator::OTHERS;
}
