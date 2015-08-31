#ifndef IIRSCRAM_CHOICE_HH
#define IIRSCRAM_CHOICE_HH
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

// Authors: Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Tuple.hh"
#include "IIRBase_Choice.hh"

class IIRScram_TypeDefinition;
class IIRScram_DesignatorList;
class IIRScram_List;

class IIRScram_Choice : public virtual IIRScram_Tuple, public virtual IIRBase_Choice{

public:
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor=0); 
  IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );
  savant::set<IIRScram_Declaration> *_symbol_lookup();
  void _type_check( savant::set<IIRScram_TypeDefinition> * );

  IIRScram *_get_value();

  IIRScram *_clone();

protected:
private:
};
#endif
