#ifndef IIRSCRAM_INTERFACE_DECLARATION_HH
#define IIRSCRAM_INTERFACE_DECLARATION_HH

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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ObjectDeclaration.hh"
#include "IIRBase_InterfaceDeclaration.hh"

class IIRScram_AttributeSpecification;
class IIRScram_List;
class IIRScram_TypeDefinition;

class IIRScram_InterfaceDeclaration : public virtual IIRScram_ObjectDeclaration, public virtual IIRBase_InterfaceDeclaration{

public:
  IIRScram_InterfaceDeclaration() {}
  virtual ~IIRScram_InterfaceDeclaration();
    
  IIR_Boolean _attach_attribute_specification( IIRScram_AttributeSpecification * );

  
  IIR_Boolean is_object() { return TRUE;}
  IIR_Boolean _is_iir_interface_declaration(){ return TRUE; }

  IIRScram_TypeDefinition *_get_type_of_element( int );

  IIR_Int32 get_num_indexes();
  virtual void _clone( IIRScram * );

  IIR_Boolean _is_readable();
  IIR_Boolean _is_writable();
  IIR_Boolean _is_optional();

  virtual IIR_Mode _get_mode();

  virtual void _type_check( _InterfaceListType ) = 0;
  virtual void _type_check( );

  IIRScram * _get_value();

protected:
private:
};
#endif





