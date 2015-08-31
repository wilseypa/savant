#ifndef PROCESS_COMBINATION_HH
#define PROCESS_COMBINATION_HH
// Copyright (c) 1998-1999 The University of Cincinnati.  
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

// Author: Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "signal_set.hh"
class IIR_ProcessStatement;
class IIR_SequentialStatementList;
class IIR_WaitStatement;
class IIR_IfStatement;

// This class is used to pair a process and its initialization code.
// It is only used by process combination.
class ProcessCombiner {
public:
  ProcessCombiner();
  ProcessCombiner( ProcessCombiner& );
  ~ProcessCombiner();
  ProcessCombiner& operator=( ProcessCombiner& );
  IIR_ProcessStatement *get_process() { return process; }

  void combine( IIR_ProcessStatement* );
  void combine_uncondwait( IIR_ProcessStatement* );

  // For cone partitioning only
  signal_set<IIR_Declaration> outsigs;
  int num_elements() { return size; };

private:
  IIR_ProcessStatement *process;
  IIR_SequentialStatementList *init_stmt_list;
  IIR_SequentialStatementList *run_stmt_list;
  int size;
};
#endif
