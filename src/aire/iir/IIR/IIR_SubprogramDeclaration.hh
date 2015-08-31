
#ifndef IIR_SUBPROGRAM_DECLARATION_HH
#define IIR_SUBPROGRAM_DECLARATION_HH

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
class IIR_InterfaceList;
class IIR_DeclarationList;
class IIR_SequentialStatementList;
class IIR_AttributeSpecificationList;

class IIR_SubprogramDeclaration : public virtual IIR_Declaration{
public:
  virtual ~IIR_SubprogramDeclaration() {}    

  // List accessor(s)
  virtual IIR_InterfaceList                     *get_interface_declarations() = 0;
  virtual IIR_DeclarationList                   *get_subprogram_declarations() = 0;
  virtual IIR_SequentialStatementList           *get_subprogram_body() = 0;
  virtual IIR_AttributeSpecificationList        *get_attributes() = 0;
  virtual void                                  set_interface_declarations(IIR_InterfaceList *) = 0;
  virtual void                                  set_subprogram_declarations(IIR_DeclarationList *) = 0;
  virtual void                                  set_subprogram_body(IIR_SequentialStatementList *) = 0;
  virtual void                                  set_attributes(IIR_AttributeSpecificationList *) = 0;

  /** This method returns true if this method contained a body when it was parsed.
      We need this to differentiate between:
      procedure foo;
      and
      procedure foo is begin end foo;
      (Both are legal, and both could appear in a package body or entity's declarative
      region)
  */
  virtual IIR_Boolean contains_body() = 0;
  virtual void set_contains_body( IIR_Boolean ) = 0;
};

#endif
