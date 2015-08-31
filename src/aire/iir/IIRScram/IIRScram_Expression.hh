#ifndef IIRSCRAM_EXPRESSION_HH
#define IIRSCRAM_EXPRESSION_HH

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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram.hh"
#include "IIRBase_Expression.hh"

class IIRScram_DesignatorList;
class IIRScram_Expression;
class IIRScram_TypeDefinition;

class IIRScram_Expression : public virtual IIRScram, public virtual IIRBase_Expression{

public:
  IIRScram_Expression() {};
  
  virtual IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );
  void _clone( IIRScram * );

  IIR_Boolean _is_iir_expression(){ return TRUE; }

  IIR_Boolean _is_readable(){ return TRUE; }
  IIR_Boolean _is_writable(){ return FALSE; }

protected:
  virtual ~IIRScram_Expression() = 0;
    
private:
};
#endif
