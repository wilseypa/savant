#ifndef IIRBASE_INCOMPLETE_TYPE_DEFINITION_HH
#define IIRBASE_INCOMPLETE_TYPE_DEFINITION_HH
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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_IncompleteTypeDefinition.hh"
#include "IIRBase_TypeDefinition.hh"
#include <cstdlib>
using std::abort;

class IIR_Identifier;

/**
   This class is a SAVANT extension to the IIR.  It is used to be a
   placeholder type definition for an incomplete type declaration.
*/
class IIRBase_IncompleteTypeDefinition : public virtual IIRBase_TypeDefinition, public virtual IIR_IncompleteTypeDefinition {
public:
  IIRBase_IncompleteTypeDefinition() : my_designated_type_name( NULL ){}
  ~IIRBase_IncompleteTypeDefinition(){}

  IIR_Kind get_kind() const { return   IIR_INCOMPLETE_TYPE_DEFINITION; }
  const IIR_Char *get_kind_text() const { return "IIR_IncompleteTypeDefinition"; }

  IIR_Boolean is_subtype(){ return TRUE; }
  
  IIR_Identifier *get_designated_type_name(){
    return my_designated_type_name;
  }

  void set_designated_type_name( IIR_Identifier *new_type_name ){
    my_designated_type_name = new_type_name;
  }

  IIR_Boolean is_incomplete_type_definition(){
    return TRUE;
  }

  IIR *get_value() {ASSERT(0); return NULL;}

private:
  IIR_Identifier *my_designated_type_name;
};

#endif
