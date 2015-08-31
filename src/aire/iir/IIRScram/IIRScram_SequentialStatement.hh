
#ifndef IIRSCRAM_SEQUENTIAL_STATEMENT_HH
#define IIRSCRAM_SEQUENTIAL_STATEMENT_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Malolan Chetlur    
//          Umesh Kumar V. Rajasekaran
//          Krishnan Subramani 
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Statement.hh"
#include "IIRBase_SequentialStatement.hh"

template <class type> class dl_list;

class IIRScram_AboveAttribute;
class IIRScram_List;
class IIRScram_Name;
class IIRScram_ProcedureCallStatement;
class IIRScram_SequentialStatement;
class IIRScram_SequentialStatementList;
class IIRScram_SubprogramDeclaration;
class IIRScram_TypeDefinition;
class IIRScram_WaitStatement;

class IIRScram_SequentialStatement : public virtual IIRScram_Statement, public virtual IIRBase_SequentialStatement{
public:
  IIRScram_SequentialStatement() {};

  /** This virtual method has the derived class check it's list of
      statements for return statements and type check them.  (Return
      statements are special in that the context they need to be type
      checked in is that of the declaration - not of the statement itself.)
      To do the actual cheking, the derived class calls into the second
      version of the method defined on the next line. */
  virtual IIR_Boolean _type_check_return_statements( savant::set<IIRScram_TypeDefinition> *,
                                                     IIRScram_SubprogramDeclaration * );
      
  /** Not virtual on purpose!  This is to reuse code instead of copying
      essentially the same code all of the place.  The only difference in
      how the derived classes type check their return statements is what
      the name of their list of statements is.  Therefore, we pass the list
      in. */
  static IIR_Boolean _type_check_return_statements( savant::set<IIRScram_TypeDefinition> *,
                                                    IIRScram_SequentialStatementList *,
                                                    IIRScram_SubprogramDeclaration * );

  virtual IIR_Boolean _is_iir_sequential_statement(){ return TRUE; }

  virtual IIRScram *_clone();
  virtual void _clone( IIRScram * );

  virtual void _set_process_stmt_label(IIR_Label *);
  virtual IIR_Label* _get_process_stmt_label();

protected:
  virtual ~IIRScram_SequentialStatement() = 0;
    
private:
};
#endif
