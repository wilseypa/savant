// Copyright (c) 1996-2000 The University of Cincinnati.  
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_ElementDeclaration.hh"
#include "IIRScram_ElementDeclarationList.hh"
#include "IIRScram_RecordTypeDefinition.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_TextLiteral.hh"
#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"

#include <sstream>
using std::ostringstream;

IIRScram_TypeDefinition *
IIRScram_ElementDeclaration::_determine_rval_in_set( savant::set<IIRScram_TypeDefinition> *look_in,
						     IIRScram_TypeDefinition *my_rval ){

  ASSERT( _get_subtype() == my_rval );

  IIRScram_SimpleName *temp_name = new IIRScram_SimpleName;
  copy_location( this, temp_name );
  temp_name->set_prefix( get_declarator() );

  IIRScram_TypeDefinition *current_prefix_rval = look_in->getElement();
  while( current_prefix_rval != NULL ){
    savant::set<IIRScram_Declaration> *found_declarations = 
      current_prefix_rval->find_declarations(temp_name)->convert_set<IIRScram_Declaration>();

    IIRScram_Declaration *current = found_declarations->getElement();
    while( current != NULL ){
      if( current == this ){
	delete temp_name;
	return current_prefix_rval;
      }
      current = found_declarations->getNextElement();
    }
    delete found_declarations;
    current_prefix_rval = look_in->getNextElement();
  }

  ostringstream err;
  err << "Internal error in IIRScram_ElementDeclaration::_determine_rval_in_set";
  report_error( this, err.str() );
  abort();
  return 0;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_ElementDeclaration::_get_rval_set( savant::set<IIRScram_TypeDefinition> *look_in,
					    constraint_functor * ){
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;

  IIRScram_SimpleName *temp_name = new IIRScram_SimpleName;
  copy_location( this, temp_name );
  temp_name->set_prefix( get_declarator() );

  // We need to scan the prefixes and make sure that our definition is in there
  // somewhere...

  IIRScram_TypeDefinition *current_prefix_rval = look_in->getElement();
  while( current_prefix_rval != NULL ){
    savant::set<IIRScram_Declaration> *found_declarations;

    if (current_prefix_rval->find_declarations( temp_name ) != NULL)
      found_declarations = 
        current_prefix_rval->find_declarations( temp_name )->convert_set<IIRScram_Declaration>();
    else
      found_declarations = NULL;

    if( found_declarations != NULL ){
      IIRScram_Declaration *current_declaration = found_declarations->getElement();
      while( current_declaration != NULL ){
	if( current_declaration == this ){
	  delete temp_name;
	  retval->add( _get_subtype() );
	  break;
	}
	current_declaration = found_declarations->getNextElement();
      }
    }
    current_prefix_rval = look_in->getNextElement();
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}

savant::set<IIRScram_TypeDefinition> *
IIRScram_ElementDeclaration::_get_rval_set( savant::set<IIRScram_Declaration> *look_in,
					    constraint_functor * ){
  savant::set<IIRScram_TypeDefinition> *retval = new savant::set<IIRScram_TypeDefinition>;

  IIRScram_SimpleName *temp_name = new IIRScram_SimpleName;
  copy_location( this, temp_name );
  temp_name->set_prefix( get_declarator() );

  // We need to scan the prefixes and make sure that our definition is in there
  // somewhere...

  IIRScram_Declaration *current_prefix_decl = look_in->getElement();
  while( current_prefix_decl != NULL ){
    savant::set<IIRScram_Declaration> *found;
    if ( current_prefix_decl->find_declarations( temp_name ) != NULL)
      found = current_prefix_decl->find_declarations( temp_name )->convert_set<IIRScram_Declaration>();
    else 
      found = NULL;

    if( found != NULL ){
      IIRScram_Declaration *current = found->getElement();
      while( current != NULL ){
	if( current == this ){
	  delete temp_name;
	  retval->add( _get_subtype() );
	  break;
	}
	current = found->getNextElement();
      }
    }
    current_prefix_decl = look_in->getNextElement();
  }

  if( retval->size() == 0 ){
    delete retval;
    retval = NULL;
  }

  return retval;
}
  
IIRScram *
IIRScram_ElementDeclaration::_rval_to_decl( IIRScram_TypeDefinition *,
					    IIRScram_TypeDefinition *suffix_rval ){
  ASSERT( suffix_rval == _get_subtype() );
  return this;
}

visitor_return_type *
IIRScram_ElementDeclaration::_accept_visitor(node_visitor *visitor, visitor_argument_type *arg) {
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ElementDeclaration(this, arg);
}

IIRScram_TypeDefinition *
IIRScram_ElementDeclaration::_get_type_of_element( int index_num ){
  ASSERT( _get_subtype() != NULL );
  return _get_subtype()->_get_type_of_element( index_num );
}

