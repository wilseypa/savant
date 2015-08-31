
#ifndef IIRBASE_CASE_STATEMENT_ALTERNATIVE_BY_CHOICES_HH
#define IIRBASE_CASE_STATEMENT_ALTERNATIVE_BY_CHOICES_HH

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

// Authors: Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_CaseStatementAlternative.hh"
#include "IIR_CaseStatementAlternativeByChoices.hh"

class IIR_ChoiceList;

class IIRBase_CaseStatementAlternativeByChoices : public virtual IIRBase_CaseStatementAlternative, public virtual IIR_CaseStatementAlternativeByChoices{

public:
  // List Accessor(s)
  IIR_ChoiceList *get_choices();
  void           set_choices(IIR_ChoiceList *new_choices);

  IIR_Kind get_kind() const { return IIR_CASE_STATEMENT_ALTERNATIVE_BY_CHOICES; }
  const IIR_Char *get_kind_text() const { return "IIR_CaseStatementAlternativeByChoices"; }

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_resolved();
  void publish_vhdl(ostream &);
protected:
  IIRBase_CaseStatementAlternativeByChoices();
  virtual ~IIRBase_CaseStatementAlternativeByChoices() = 0;
    
private:
  // List Variable(s)
  IIR_ChoiceList *choices;

};
#endif
