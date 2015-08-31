
#ifndef IIR_DISCONNECT_SPECIFICATION_HH
#define IIR_DISCONNECT_SPECIFICATION_HH

// Copyright (c) 1996-1999 The University of Cincinnati.  
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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_Declaration.hh"

class IIR_TypeDefinition;
class IIR_DesignatorList;

class IIR_DisconnectSpecification : public virtual IIR_Declaration{

public:
  virtual ~IIR_DisconnectSpecification() {}
    
  // List accessor(s)
  virtual void set_guarded_signal_list(IIR_DesignatorList *) = 0;
  virtual IIR_DesignatorList *get_guarded_signal_list() = 0;

  virtual void set_type_mark( IIR_TypeDefinition *type_definition ) = 0;
  virtual IIR_TypeDefinition *get_type_mark() = 0;

  virtual void set_time_expression( IIR* time_expression) = 0;
  virtual IIR *get_time_expression() = 0;
};
#endif
