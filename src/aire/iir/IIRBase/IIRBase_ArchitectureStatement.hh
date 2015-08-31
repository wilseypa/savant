
#ifndef IIRBASE_ARCHITECTURE_STATEMENT_HH
#define IIRBASE_ARCHITECTURE_STATEMENT_HH

// Copyright (c) 2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S., and
// the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2, June
// 1991. A copy of this license agreement can be found in the file "LGPL",
// distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_ArchitectureStatement.hh"
#include "IIRBase_Statement.hh"

class IIRBase_ArchitectureStatement : public virtual IIRBase_Statement,
				      public virtual IIR_ArchitectureStatement {
public:
  IIR_Kind      get_kind() const { return IIR_ARCHITECTURE_STATEMENT; }
  const IIR_Char *get_kind_text() const { return "IIR_ArchitectureStatement"; }

  void set_declarative_region(IIR *);
  IIR* get_declarative_region();
protected:
  IIRBase_ArchitectureStatement();
  virtual ~IIRBase_ArchitectureStatement() = 0;
    
  virtual void set_guard_signal( IIR_SignalDeclaration * );

  IIR *enclosingRegion;
private:
};
#endif
