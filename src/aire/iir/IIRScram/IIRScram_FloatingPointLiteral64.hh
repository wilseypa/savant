#ifndef IIRSCRAM_FLOATING_POINT_LITERAL64_HH
#define IIRSCRAM_FLOATING_POINT_LITERAL64_HH
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Literal.hh"
#include "IIRBase_FloatingPointLiteral64.hh"

class IIRScram_FloatingPointLiteral64 : public virtual IIRScram_Literal, public virtual IIRBase_FloatingPointLiteral64{

public:
  IIRScram_FloatingPointLiteral64() {}
  virtual ~IIRScram_FloatingPointLiteral64();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIR_Boolean _is_floating_literal() { return TRUE; }

  IIRScram *_clone() { return this; }

  static IIRScram_FloatingPointLiteral64* get_value(IIR_FP64);

  /**
     Do nothing.
   */
  virtual void _type_check( savant::set<IIRScram_TypeDefinition> * ){}
  
protected:    
private:
};
#endif
