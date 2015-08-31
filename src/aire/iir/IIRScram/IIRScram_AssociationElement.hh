#ifndef IIRSCRAM_ASSOCIATION_ELEMENT_HH
#define IIRSCRAM_ASSOCIATION_ELEMENT_HH

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
//          Umesh Kumar V. Rajasekaran urajase@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Tuple.hh"
#include "IIRBase_AssociationElement.hh"

class IIRScram_List;
class IIRScram_Declaration;

class IIRScram_AssociationElement : public virtual IIRScram_Tuple, public virtual IIRBase_AssociationElement{

public:
  IIRScram_AssociationElement() {}
  virtual ~IIRScram_AssociationElement();

  IIR_Boolean _is_association(){ return TRUE; }
  IIR_Boolean _is_positional();

  IIRScram* _get_formal();
  IIRScram* _get_actual();

  IIRScram_Declaration *_find_formal_declaration();

protected:    
private:
};
#endif
