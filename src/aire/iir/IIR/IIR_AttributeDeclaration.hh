
#ifndef IIR_ATTRIBUTE_DECLARATION_HH
#define IIR_ATTRIBUTE_DECLARATION_HH

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

class IIR_TypeDefinition;
class IIR_Attribute;

class IIR_AttributeDeclaration : public virtual IIR_Declaration{

public:
  virtual ~IIR_AttributeDeclaration() {}
    
  /** An attribute declaration can refer to more than one instance of an
   attribute.  These methods refer to the FIRST instance of an attribute
   that caused this declaration to be created (if scram created it -
   user defined get_attributes() are a different matter) These methods are so
   the parser gan easily determine things like if this is a signal
   valued attribute and so forth. */
  virtual IIR_Attribute *get_attribute() = 0;
  virtual void set_attribute( IIR_Attribute * ) = 0;
};
#endif
