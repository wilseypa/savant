#ifndef IIRSCRAM_OBJECT_DECLARATION_HH
#define IIRSCRAM_OBJECT_DECLARATION_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_ObjectDeclaration.hh"

class IIRScram_AttributeSpecificationList;
class IIRScram_Declaration;
class IIRScram_List;
class IIRScram_Name;
class IIRScram_TypeDefinition;

class IIRScram_ObjectDeclaration : public virtual IIRScram_Declaration, public virtual IIRBase_ObjectDeclaration{

public:
  IIRScram_ObjectDeclaration();

  /** Before you assume these are redundant, read the documentation in
      IIRScram.hh :-) */
  IIR_Boolean is_object(){ return TRUE; }
  IIR_Boolean _is_iir_object_declaration(){ return TRUE; }

  /** This returns how many dimensions an array object has.. (0 if it's not
      an array) */
  IIR_Int32 get_num_indexes();

  /** If this is an array variable, get the type definition of the object
      stored in the "nth" index... */
  IIRScram_TypeDefinition *_get_type_of_element( int index );

  /** Type check initializers and such... */
  virtual void _type_check();

  /** The only object declaration that doesn't have a value is a file type
      declaration... */
  virtual IIRScram *_get_value() { return NULL; }
  IIRScram_AttributeSpecificationList *_get_attribute_specification_list();
  /**  Doesn't need to do anything at all. */
  void _publish_cc_include( published_file & ){}

  const IIR_Char* _get_mangling_prefix();
  
  void _clone( IIRScram * );


  IIRScram_Declaration* _get_package_declaration() { return NULL; }

  // Wrappers for IIRBase functions
  IIRScram_AttributeSpecificationList * _get_attributes();

protected:
  virtual ~IIRScram_ObjectDeclaration();
    
private:
};
#endif
