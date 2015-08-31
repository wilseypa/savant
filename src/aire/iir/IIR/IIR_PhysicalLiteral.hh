
#ifndef IIR_PHYSICAL_LITERAL_HH
#define IIR_PHYSICAL_LITERAL_HH

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
#include "IIR_Expression.hh"

class IIR_PhysicalUnit;

class IIR_PhysicalLiteral : public virtual IIR_Expression{

public:
  virtual ~IIR_PhysicalLiteral() {}
    
  virtual void set_abstract_literal( IIR *abstract_literal ) = 0;
  virtual IIR *get_abstract_literal() = 0;
  virtual void set_unit_name( IIR_PhysicalUnit *unit ) = 0;
  virtual IIR_PhysicalUnit *get_unit_name() = 0;
  virtual IIR_Boolean is_locally_static() = 0;
};    
#endif
