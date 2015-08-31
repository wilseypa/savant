
#ifndef IIRSCRAM_ARRAY_NATURE_DEFINITION_HH
#define IIRSCRAM_ARRAY_NATURE_DEFINITION_HH

// Copyright (c) 2002-2003 The University of Cincinnati.
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Author: Sivakumar Gowrisankar             gowriss@ececs.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_NatureDefinition.hh"
#include "IIRBase_ArrayNatureDefinition.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "error_func.hh"
#include "set.hh"
#include <stdlib.h>

class IIRScram_NatureDeclaration;
class IIRScram_NatureDefinition;
class IIRScram_ArraySubnatureDefinition;
class IIRScram_ScalarTypeDefinition;

class IIRScram_ArrayNatureDefinition : public virtual IIRScram_NatureDefinition, public virtual IIRBase_ArrayNatureDefinition {
    friend class StandardPackage;
public:
  IIRScram_ArrayNatureDefinition();
  virtual ~IIRScram_ArrayNatureDefinition();


  /** Used to identify if the object is of type Array Nature */
  IIR_Boolean _is_iir_array_type_definition() { return TRUE; }

  /** Used to construct constrained and unconstrained arrays */
  static IIRScram_ArrayNatureDefinition *
  _construct_array_type( IIRScram_ScalarTypeDefinition *index_subtype,
                         IIRScram_NatureDefinition *, 
                         IIRScram_NatureDeclaration *);

  IIRScram_TypeDefinition *
  _construct_new_subtype( IIRScram_Name *,
                          IIRScram_ScalarTypeDefinition *);

  IIRScram_TypeDefinition *
  _index_constrain_array( IIRScram_ScalarTypeDefinition * );

  /** Gets the element subtype of a given index object */
  IIRScram_TypeDefinition *_get_element_subtype();        

  /** Gets the index subtype of a base object */
  IIRScram_ScalarTypeDefinition *_get_index_subtype();

  IIRScram_TypeDefinition *_get_new_subtype();

  IIRScram *_clone();
  virtual void _clone( IIRScram *my_clone );

  /** Gets number of indexes in an array */
  IIR_Int32 get_num_indexes();

protected:
private:
  static IIRScram_ArraySubnatureDefinition *_construct_unconstrained( IIRScram_ScalarTypeDefinition *, 
                                                                      IIRScram_NatureDefinition *, 
                                                                      IIRScram_NatureDeclaration *);

  static IIRScram_ArraySubnatureDefinition *_construct_constrained( IIRScram_ScalarTypeDefinition *,
                                                                    IIRScram_NatureDefinition *,
                                                                    IIRScram_NatureDeclaration *);
};
#endif
