#ifndef IIRSCRAM_LEFT_ATTRIBUTE_HH
#define IIRSCRAM_LEFT_ATTRIBUTE_HH

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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Attribute.hh"
#include "IIRBase_LeftAttribute.hh"

class IIRScram_Declaration;
class IIRScram_TextLiteral;
class IIRScram_TypeDefinition;

class IIRScram_LeftAttribute : public virtual IIRScram_Attribute, public virtual IIRBase_LeftAttribute{

public:
  IIRScram_LeftAttribute() {}
  virtual ~IIRScram_LeftAttribute();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIRScram_TypeDefinition *_get_subtype();

  IIRScram_Declaration *_get_implicit_declaration( const string &, IIRScram_TypeDefinition * );

  IIR_Boolean has_suffix(){ return TRUE; }
  void _set_suffix( IIRScram *new_suffix ){ IIRBase_LeftAttribute::set_suffix( new_suffix ); }

  virtual savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0); 

protected:
  void _resolve_suffix_special();    
private:
};
#endif
