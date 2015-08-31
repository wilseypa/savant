#ifndef IIRSCRAM_FREE_QUANTITY_DECLARATION_HH
#define IIRSCRAM_FREE_QUANTITY_DECLARATION_HH

// Copyright (c) 2002-2003 The University of Cincinnati.
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
 
// Author: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_FreeQuantityDeclaration.hh"
#include "IIRScram_QuantityDeclaration.hh"
#include <vector>

using std::vector;

class IIRScram_FreeQuantityDeclaration : public virtual IIRScram_QuantityDeclaration, public virtual IIRBase_FreeQuantityDeclaration {

public:
  IIRScram_FreeQuantityDeclaration();
  virtual ~IIRScram_FreeQuantityDeclaration();
   
  IIR_Boolean _is_readable();
  void _type_check();

  // Helper functions
  IIRScram *_get_value();
  void set_value(IIRScram *);

protected:
  double ATOL;
  double RTOL;

private:
  double default_rtol;
  double default_atol;

};

#endif
