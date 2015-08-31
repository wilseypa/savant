
#ifndef IIR_LIBRARY_UNIT_HH
#define IIR_LIBRARY_UNIT_HH

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

#include "savant_config.hh"
#include "IIR_Declaration.hh"
class IIR_DeclarationList;
class IIR_AttributeSpecificationList;
class IIR_LibraryDeclaration;

class IIR_LibraryUnit : public virtual IIR_Declaration{
public:
  virtual ~IIR_LibraryUnit() {}

  /**
     Return the IIR_LibraryDeclaration that this IIR_LibraryUnit belongs
     to.
  */
  virtual IIR_LibraryDeclaration *get_library() = 0;

  /**
     Is this a primary unit?
  */
  virtual IIR_Boolean is_primary_unit() = 0;
  /**
     Is this a secondary unit?
  */
  virtual IIR_Boolean is_secondary_unit() = 0;

  //@{ List accessor(s)
  virtual IIR_DeclarationList *get_context_items() = 0;
  virtual void set_context_items(IIR_DeclarationList *new_context_items) = 0;
  virtual IIR_AttributeSpecificationList *get_attributes() = 0;
  virtual void set_attributes(IIR_AttributeSpecificationList *new_attributes) = 0;
  //@}
};
#endif
