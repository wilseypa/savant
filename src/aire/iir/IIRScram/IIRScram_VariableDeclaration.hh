#ifndef IIRSCRAM_VARIABLE_DECLARATION_HH
#define IIRSCRAM_VARIABLE_DECLARATION_HH

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
//          Malolan Chetlur     mal@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ObjectDeclaration.hh"
#include "IIRBase_VariableDeclaration.hh"

class IIRScram_List;
class IIRScram_VariableDeclaration;

class IIRScram_VariableDeclaration : public virtual IIRScram_ObjectDeclaration, public virtual IIRBase_VariableDeclaration{
public:
  IIRScram_VariableDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  
  IIR_Boolean _is_readable(){ return TRUE; }
  IIR_Boolean _is_writable(){ return TRUE; }

  /** For some reason, sometimes the code generate wants a fresh clone
     generated.  */
  void _clear_clone(){ _my_clone = 0; }

  IIRScram *_clone();

  IIRScram *_get_value();

protected:
private:
  IIRScram_VariableDeclaration *_my_clone;
};
#endif
