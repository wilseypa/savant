
#ifndef IIR_ARRAY_NATURE_DEFINITION_HH
#define IIR_ARRAY_NATURE_DEFINITION_HH

// Copyright (c) 2002-2003 The University of Cincinnati.
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S., and
// the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2, June
// 1991. A copy of this license agreement can be found in the file "LGPL",
// distributed with this archive.

// Author: Sivakumar Gowrisankar             gowriss@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_NatureDefinition.hh"

class IIR_ScalarTypeDefinition;
class IIR_TypeDefinition;

class IIR_ArrayNatureDefinition : public virtual IIR_NatureDefinition {

public:
  IIR_ArrayNatureDefinition() {}
  virtual ~IIR_ArrayNatureDefinition() {}

  /** Sets the index subtype of the array nature definition */
  virtual void set_index_subtype(IIR_ScalarTypeDefinition* index_subtype) = 0;
  
  /** Gets the index subtype of the array nature definition */
  virtual IIR_ScalarTypeDefinition* get_index_subtype() = 0;
  
  /** Sets the element subtype in the array nature definition */
  virtual void set_element_subtype(IIR_TypeDefinition* element_subtype) = 0;
  
  /** Gets the element subtype in the array nature definition */
  virtual IIR_TypeDefinition* get_element_subtype() = 0;

  /** Gets the pointer to the final index in a multidimensional array */
  IIR_TypeDefinition *get_final_subtype() = 0;
  
  /** The Boolean variable is set TRUE if the object is of element type
      i.e. one of subnature_indication type */
  virtual void set_is_element(IIR_Boolean) = 0;
};
#endif
