
#ifndef IIR_GROUP_DECLARATION_HH
#define IIR_GROUP_DECLARATION_HH

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

class IIR_Name;
class IIR_DesignatorList;
class IIR_AttributeSpecificationList;

class IIR_GroupDeclaration : public virtual IIR_Declaration{
public:
  virtual ~IIR_GroupDeclaration() {}    

  // List accessor(s)
  virtual IIR_DesignatorList                    *get_group_constituent_list() = 0;
  virtual IIR_AttributeSpecificationList        *get_attributes() = 0;
  virtual void                                  set_group_constituent_list(IIR_DesignatorList *) = 0;
  virtual void                                  set_attributes(IIR_AttributeSpecificationList *) = 0;

  virtual void set_group_template(IIR_Name* group_template_name) = 0;
  virtual IIR_Name* get_group_template_name() = 0;
};
#endif
