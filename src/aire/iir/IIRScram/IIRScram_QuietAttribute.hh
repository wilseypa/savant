#ifndef IIRSCRAM_QUIET_ATTRIBUTE_HH
#define IIRSCRAM_QUIET_ATTRIBUTE_HH

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

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Attribute.hh"
#include "IIRBase_QuietAttribute.hh"

class IIRScram_TextLiteral;
class IIRScram_TypeDefinition;

class IIRScram_QuietAttribute : public virtual IIRScram_Attribute, public virtual IIRBase_QuietAttribute{
public:
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  IIR_Boolean _is_readable();
  
  IIRScram_Declaration *_get_implicit_declaration( const string &decl_name,
					      IIRScram_TypeDefinition *decl_type );
  
  IIR_Boolean has_suffix(){ return TRUE; }
  void _set_suffix( IIRScram *new_suffix ){ IIRBase_QuietAttribute::set_suffix( new_suffix ); }

  IIRScram *_clone();
  virtual IIR_Boolean _is_quiet_attribute() { return TRUE; }
  IIR_Boolean _is_signal_attribute(){ return TRUE; }

protected:
  void _resolve_suffix_special();
private:
};
#endif
