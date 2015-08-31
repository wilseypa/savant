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

#include "IIRScram_ArraySubtypeDefinition.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_FileTypeDefinition.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_ConstantInterfaceDeclaration.hh"
#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_ProcedureDeclaration.hh"
#include "resolution_func.hh"
#include "error_func.hh"
#include "symbol_table.hh"
#include "set.hh"
#include "StandardPackage.hh"
#include <sstream>

using std::ostringstream;

IIRScram_FileTypeDefinition::~IIRScram_FileTypeDefinition() {}

void 
IIRScram_FileTypeDefinition::_come_into_scope( symbol_table *sym_tab, 
					       IIRScram_TypeDeclaration *type_declaration){

  // Whenever a new file type is created, we need to build the
  // following declarations (shown in VHDL)  
  IIRScram_TypeDefinition *type_mark = _get_type_mark();
  
  // procedure file_open( file f : new_file_type;
  //                      external_name : in string;
  //                      open_kind : in file_open_kind := read_mode );

  if( type_declaration->get_implicit_declarations() == NULL ){
    type_declaration->set_implicit_declarations( new savant::set<IIR_Declaration> );
        
    const char *name = "file_open";
    IIRScram_ProcedureDeclaration *new_procedure_declaration = new IIRScram_ProcedureDeclaration();
    copy_location( this, new_procedure_declaration );
    new_procedure_declaration->set_declarator( IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_procedure_declaration->set_is_implicit( TRUE );

    type_declaration->get_implicit_declarations()->add( new_procedure_declaration );
    
    IIRScram_ConstantInterfaceDeclaration *new_interface_declaration;
    new_interface_declaration  = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    copy_location( this, new_interface_declaration );

    name = "f";
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( this );

    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    name = "external_name";
    StandardPackage *package = _get_design_file()->get_standard_package();
    IIRScram_TypeDefinition *string_type = dynamic_cast<IIRScram_TypeDefinition *>(package->get_string_type());
    
    new_interface_declaration  = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( string_type );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    name = "my_open_kind";
    IIRScram_TypeDefinition *file_open_type = dynamic_cast<IIRScram_TypeDefinition *>(package->get_file_open_kind_type());
    
    new_interface_declaration  = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( file_open_type );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    sym_tab->add_subprogram_declaration( new_procedure_declaration );

    
    // procedure file_open( status: out FILE_OPEN_STATUS;
    //                      file f : ft;
    //                      external_name: in string;
    //                      open_kind: in FILE_OPEN_KIND := READ_MODE );
    
    name = "file_open";
    new_procedure_declaration = new IIRScram_ProcedureDeclaration();
    new_procedure_declaration->set_is_implicit( TRUE );
    copy_location( this, new_procedure_declaration );
    new_procedure_declaration->set_declarator( IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );

    type_declaration->get_implicit_declarations()->add( new_procedure_declaration );
    
    name = "status";
    IIRScram_TypeDefinition *file_open_status_type = dynamic_cast<IIRScram_TypeDefinition *>(package->get_file_open_status_type());
    
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( file_open_status_type );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    name = "f";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( this );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    name = "external_name";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( string_type );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    name = "my_open_kind";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( file_open_type );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    sym_tab->add_subprogram_declaration( new_procedure_declaration );
    
    // procedure file_close( file f : ft );
    name = "file_close";
    new_procedure_declaration = new IIRScram_ProcedureDeclaration();
    new_procedure_declaration->set_is_implicit( TRUE );
    copy_location( this, new_procedure_declaration );
    new_procedure_declaration->set_declarator( IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    
    type_declaration->get_implicit_declarations()->add( new_procedure_declaration );
    
    name = "f";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( this );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    sym_tab->add_subprogram_declaration( new_procedure_declaration );

    // procedure read ( file f : ft; value : out tm );
    name = "read";
    new_procedure_declaration = new IIRScram_ProcedureDeclaration();
    new_procedure_declaration->set_is_implicit( TRUE );
    copy_location( this, new_procedure_declaration );
    new_procedure_declaration->set_declarator( IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    
    type_declaration->get_implicit_declarations()->add( new_procedure_declaration );
    
    name = "f";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( this );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    name = "value";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( type_mark );
    new_interface_declaration->set_mode( IIR_OUT_MODE );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    
    if( type_mark->is_unconstrained_array_type() == TRUE ){
      name = "length";
      new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
      new_interface_declaration->set_is_implicit( TRUE );
      new_interface_declaration->set_is_visible( FALSE );
      copy_location( this, new_interface_declaration );
      new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
      new_interface_declaration->set_subtype( package->get_natural_type() );
      new_interface_declaration->set_mode( IIR_OUT_MODE );
      new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );    
    }
    sym_tab->add_subprogram_declaration( new_procedure_declaration );
    
    // procedure write ( file f : ft; value in tm );
    name = "write";
    new_procedure_declaration = new IIRScram_ProcedureDeclaration();
    new_procedure_declaration->set_is_implicit( TRUE );
    copy_location( this, new_procedure_declaration );
    new_procedure_declaration->set_declarator( IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );

    type_declaration->get_implicit_declarations()->add( new_procedure_declaration );

    name = "f";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_procedure_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( this );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );

    name = "value";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( type_mark );
    new_interface_declaration->set_mode( IIR_IN_MODE );
    new_procedure_declaration->get_interface_declarations()->append( new_interface_declaration );
    sym_tab->add_subprogram_declaration( new_procedure_declaration );

    // function endfile ( file f : ft ) return boolean;
    name = "endfile";
    IIRScram_FunctionDeclaration *new_function_declaration = new IIRScram_FunctionDeclaration();
    new_function_declaration->set_is_implicit( TRUE );
    copy_location( this, new_function_declaration );
    new_function_declaration->set_declarator( IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    type_declaration->get_implicit_declarations()->add( new_function_declaration );

    name = "f";
    new_interface_declaration = new IIRScram_ConstantInterfaceDeclaration();
    new_interface_declaration->set_is_implicit( TRUE );
    new_interface_declaration->set_is_visible( FALSE );
    copy_location( this, new_interface_declaration );
    new_interface_declaration->set_declarator(  IIRScram_Identifier::get( name, strlen(name), get_design_file()->get_class_factory() ) );
    new_interface_declaration->set_subtype( this );
    new_function_declaration->get_interface_declarations()->append( new_interface_declaration );
  
    IIRScram_TypeDefinition *boolean_type = dynamic_cast<IIRScram_TypeDefinition *>(package->get_boolean_type());
    new_function_declaration->set_return_type( boolean_type );

    sym_tab->add_subprogram_declaration( new_function_declaration );
  }
  else{
    sym_tab->add_declaration( type_declaration->get_implicit_declarations()->convert_set<IIR_Declaration>() );
  }
}

void 
IIRScram_FileTypeDefinition::_set_resolution_function( IIRScram_FunctionDeclaration * ){
  ostringstream err;
  err << "Internal error - IIRScram_FileTypeDefinition::_set_resolution_function was "
      << "called.  Resolution functions can't be associated with a file type and this "
      << "should have been caught earlier.";
  report_error( this, err.str() );
}

visitor_return_type *
IIRScram_FileTypeDefinition::_accept_visitor( node_visitor *visitor,
					      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_FileTypeDefinition(this, arg);
}

IIRScram_TypeDefinition *
IIRScram_FileTypeDefinition::_get_type_mark() {
  return dynamic_cast<IIRScram_TypeDefinition *>(get_type_mark());
}
