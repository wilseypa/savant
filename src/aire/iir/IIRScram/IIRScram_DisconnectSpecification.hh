#ifndef IIRSCRAM_DISCONNECT_SPECIFICATION_HH
#define IIRSCRAM_DISCONNECT_SPECIFICATION_HH

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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_DisconnectSpecification.hh"

class IIRScram_DeclarationList;
class IIRScram_List;

class IIRScram_DisconnectSpecification : public virtual IIRScram_Declaration, public virtual IIRBase_DisconnectSpecification{

public:
  IIRScram_DisconnectSpecification();  
  virtual ~IIRScram_DisconnectSpecification();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIR_Boolean _is_specification(){
    return TRUE;
  }

  IIR_Boolean _is_iir_disconnect_specification(){ return TRUE; }
  void _type_check( IIRScram_DeclarationList *declarative_region );
  
  // Wrappers for IIRBase functions
  IIRScram_DesignatorList *     _get_guarded_signal_list();
  IIRScram_TypeDefinition *     _get_type_mark();
  IIRScram *                    _get_time_expression();

protected:    
private:  
};

#endif
