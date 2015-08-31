
#ifndef IIRSCRAM_FOR_LOOP_STATEMENT_HH
#define IIRSCRAM_FOR_LOOP_STATEMENT_HH

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

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_SequentialStatement.hh"
#include "IIRBase_ForLoopStatement.hh"

class IIRScram_Attribute;
class IIRScram_DesignatorList;
class IIRScram_Name;
class IIRScram_List;
class IIRScram_TypeDefinition;
class IIR_ScalarTypeDefinition;

class IIRScram_ForLoopStatement : public virtual IIRScram_SequentialStatement,
				  public virtual IIRBase_ForLoopStatement{

public:
  IIRScram_ForLoopStatement();
  virtual ~IIRScram_ForLoopStatement();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void _type_check();
  IIR_Boolean _type_check_return_statements( savant::set<IIRScram_TypeDefinition> *,
					     IIRScram_SubprogramDeclaration *subprogram_decl );
  IIRScram_List                         *_get_statement_list();
    
  // Wrappers for IIRBase functions
  IIRScram_SequentialStatementList      *_get_sequence_of_statements();
  IIRScram_ConstantDeclaration          *_get_iteration_scheme();

  /**
     The parser calls this to ask us to build our iterator.
  */
  void _build_iteration_scheme( IIR_TextLiteral *declarator,
				IIR_ScalarTypeDefinition *subtype );
 
protected:   
private:
  void _publish_cc_initialize_iterator( published_file & );
  void _publish_cc_while_loop_begin( published_file & );
};
#endif
