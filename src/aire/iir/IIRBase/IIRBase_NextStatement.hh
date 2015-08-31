
#ifndef IIRBASE_NEXT_STATEMENT_HH
#define IIRBASE_NEXT_STATEMENT_HH

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
#include "IIRBase_SequentialStatement.hh"
#include "IIR_NextStatement.hh"

class IIR_SequentialStatement;

class IIRBase_NextStatement : public virtual IIRBase_SequentialStatement, public virtual IIR_NextStatement{

public:

  IIR_Kind get_kind() const {return IIR_NEXT_STATEMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_NextStatement";}

  void set_enclosing_loop( IIR_SequentialStatement* loop);
  IIR_SequentialStatement* get_enclosing_loop();
  void set_condition( IIR* condition);
  IIR* get_condition();

  IIR_Boolean is_above_attribute_found();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &);
protected:
  
  IIRBase_NextStatement();
  virtual ~IIRBase_NextStatement() = 0;
    
private:
  
  IIR* condition;
  IIR_SequentialStatement* loop;

};
#endif
