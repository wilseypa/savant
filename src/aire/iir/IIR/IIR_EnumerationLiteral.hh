
#ifndef IIR_ENUMERATION_LITERAL_HH
#define IIR_ENUMERATION_LITERAL_HH

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
#include "IIR_EnumerationTypeDefinition.hh"
class IIR_AttributeSpecificationList;

class IIR_EnumerationLiteral : public virtual IIR_Declaration{
public:
  virtual ~IIR_EnumerationLiteral() {}    

  // List accessor(s)
  virtual IIR_AttributeSpecificationList *get_attributes() = 0;

  virtual void set_position( IIR *position ) = 0;
  virtual IIR *get_position() = 0;

  virtual IIR_Boolean is_character_literal() = 0;
};
#endif
