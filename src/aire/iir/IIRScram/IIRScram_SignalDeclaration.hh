
#ifndef IIRSCRAM_SIGNAL_DECLARATION_HH
#define IIRSCRAM_SIGNAL_DECLARATION_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Timothy J. McBrayer 
//          Krishnan Subramani  
//          Umesh Kumar V. Rajasekaran
//          Radharamanan Radhakrishnan
//          Narayanan Thondugulam

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_ObjectDeclaration.hh"
#include "IIRBase_SignalDeclaration.hh"

class IIRScram_Declaration;
class IIRScram_DesigantorList;
class IIRScram_List;
class IIRScram_SignalDeclaration;
class IIRScram_TypeDefinition;

class IIRScram_SignalDeclaration : public virtual IIRScram_ObjectDeclaration,
				   public virtual IIRBase_SignalDeclaration{
public:
  IIRScram_SignalDeclaration();
  ~IIRScram_SignalDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  
  //This function publishes the implicit signal attributes
  //that are in scope for "this" declaration
  //  void _publish_cc_implicit_signal_attributes( published_file &_cc_out );
  IIR_Boolean _is_iir_signal_declaration(){ return TRUE; }
  IIR_Boolean _is_readable(){ return TRUE; }
  IIR_Boolean _is_writable(){ return TRUE; }

  IIRScram *_clone();
  IIRScram *_get_value();

  /** For some reason, sometimes the code generate wants a fresh clone
     generated.  */
  void _clear_clone(){ _my_clone = 0; }
  
protected:
private:
  IIRScram_SignalDeclaration *_my_clone;
};
#endif
