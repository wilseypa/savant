#ifndef IIRSCRAM_EVENT_ATTRIBUTE_HH
#define IIRSCRAM_EVENT_ATTRIBUTE_HH

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
//          Radharamanan Radhakrishnan ramanan@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Attribute.hh"
#include "IIRBase_EventAttribute.hh"

class IIRScram_Declaration;
class IIRScram_TextLiteral;
class IIRScram_TypeDefinition;

class IIRScram_EventAttribute : public virtual IIRScram_Attribute, public virtual IIRBase_EventAttribute{

public:
  IIRScram_EventAttribute() {}
  virtual ~IIRScram_EventAttribute();    

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIR_Boolean _is_readable();

  IIRScram_Declaration *_get_implicit_declaration( const string &, IIRScram_TypeDefinition * );
  
  IIR_Boolean _is_event_attribute() { return TRUE; }

  virtual IIRScram *_clone();

protected:
private:
  void _publish_cc_state_object_init_last_event( published_file &_cc_out );  
  void _publish_cc_state_object_init_event( published_file &_cc_out );  
  void _publish_cc_state_object_init_attr_var( published_file &_cc_out,
					       IIRScram::SignalAttribute type );
  IIR_VariableDeclaration *_build_implicit_variable( const string &declarator,
						     IIR_TypeDefinition *subtype );


};
#endif
