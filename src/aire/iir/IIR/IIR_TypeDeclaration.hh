
#ifndef IIR_TYPE_DECLARATION_HH
#define IIR_TYPE_DECLARATION_HH

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
#include "IIR_Declaration.hh"

class IIR_TypeDefinition;
class IIR_AttributeSpecificationList;
 
class IIR_TypeDeclaration : public virtual IIR_Declaration{
public:
  virtual ~IIR_TypeDeclaration() {}    

  // List accessor(s)
  virtual IIR_AttributeSpecificationList        *get_attributes() = 0;
  virtual void                                  set_attributes(IIR_AttributeSpecificationList *) = 0;

  virtual void set_type(IIR_TypeDefinition* type) = 0;
  virtual IIR_TypeDefinition* get_type() = 0;

  // This varies depending on the definition.  For Scalar types the get/set operators
  // for AccessTypeDeclaration it builds the deallocate functions, etc.
  virtual savant::set<IIR_Declaration> *get_implicit_declarations() = 0;
  virtual void set_implicit_declarations( savant::set<IIR_Declaration> *) = 0;
};

#endif
