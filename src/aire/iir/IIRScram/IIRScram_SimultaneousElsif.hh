#ifndef IIRSCRAM_SIMULTANEOUS_ELSIF_HH
#define IIRSCRAM_SIMULTANEOUS_ELSIF_HH

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

// Authors: Harish Venkataramani venkath@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "set.hh"
#include "IIRScram_ArchitectureStatement.hh"
#include "IIRBase_SimultaneousElsif.hh"
#include "IIRScram_Tuple.hh"

class IIRScram_Declaration;
class IIRScram_TypeDefinition;

/** This class selects for evaluation one of the enclosed simultaneous
    statement parts depending on the value of one or more conditions. */
class IIRScram_SimultaneousElsif : public virtual IIRBase_SimultaneousElsif, public virtual IIRScram_Tuple {
public:
  IIRScram_SimultaneousElsif();
  virtual ~IIRScram_SimultaneousElsif();

  /** @name Method for publishing VHDL code. */

  /** Function that calls the Simultaneous Statement's
      _publish_cc_ams_function_body for each of the
      statements in the If part and the else part.*/
  void _type_check( savant::set<IIRScram_TypeDefinition> *);

  // helper functions
  IIRScram                              *_get_condition();
  IIRScram_ArchitectureStatementList    *_get_then_sequence_of_statements();
  IIRScram_SimultaneousElsif            *_get_else_clause();

protected:
private:

};
#endif

