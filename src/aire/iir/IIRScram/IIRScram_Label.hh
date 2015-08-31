#ifndef IIRSCRAM_LABEL_HH
#define IIRSCRAM_LABEL_HH

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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ececs.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_Label.hh"

class IIRScram_List;
class IIRScram_Name;
class IIRScram_TypeDefinition;

class IIRScram_Label : public virtual IIRScram_Declaration, public virtual IIRBase_Label{

public:
  IIRScram_Label();
  ~IIRScram_Label();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void _make_interface_visible( symbol_table * );

  IIRScram_Statement* _get_statement();
  IIRScram_List *_get_statement_list();

  IIRScram *_clone();

  IIR_Boolean is_label(){ return TRUE; }

  IIRScram_AttributeSpecificationList* _get_attribute_specification_list();

  // Wrappers for IIRBase functions
  IIRScram_AttributeSpecificationList * _get_attributes();

protected:    
private:
};
#endif
