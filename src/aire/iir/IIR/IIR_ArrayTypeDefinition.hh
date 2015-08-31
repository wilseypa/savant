
#ifndef IIR_ARRAY_TYPE_DEFINITION_HH
#define IIR_ARRAY_TYPE_DEFINITION_HH

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
#include "IIR_TypeDefinition.hh"

class IIR_ScalarTypeDefinition;

class IIR_ArrayTypeDefinition : public virtual IIR_TypeDefinition{

public:
  virtual ~IIR_ArrayTypeDefinition() {}

  virtual void set_index_subtype( IIR_ScalarTypeDefinition *index_subtype ) = 0;
  virtual IIR_ScalarTypeDefinition *get_index_subtype() = 0;

  virtual void set_element_subtype( IIR_TypeDefinition *element_subtype ) = 0;
  virtual IIR_TypeDefinition *get_element_subtype() = 0;

  /** Due to the complexities of the IIR, sometimes
      _get_element_subtype() doesn't actually return the element
      subtype.  This is the case for multidimensional arrays, for
      instance.  _get_final_subtype() _will_ return the _real_ element
      subtype. */
  virtual IIR_TypeDefinition *get_final_subtype() = 0;

  // This method returns TRUE if the element_subtype is REALLY that of the
  // element, or FALSE if it's simply a placeholder for a mutlidimensional array.
  virtual IIR_Boolean is_element() = 0;
  virtual void set_is_element( IIR_Boolean ) = 0;

  virtual void set_declaration( IIR_Declaration *corresponding_decl ) = 0;
};
#endif
