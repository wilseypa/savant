
#ifndef IIR_LIBRARY_CLAUSE_HH
#define IIR_LIBRARY_CLAUSE_HH

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

class IIR_Identifier;
class IIR_LibraryDeclaration;

class IIR_LibraryClause : public virtual IIR_Declaration{

public:
  virtual ~IIR_LibraryClause() {}
    
  //@{
  /** Deal with the text of the logical name. */
  virtual void set_logical_name(IIR_Identifier* logical_name) = 0;
  virtual IIR_Identifier* get_logical_name() = 0;
  //@}

  //@{
  /** Post-resolution, get a handle to the actual library node.  Note that
      you will probably have to utlize the library_manager class to do much
      of interest with it. */
  virtual void set_library_declaration( IIR_LibraryDeclaration *new_library_declaration ) = 0;
  virtual IIR_LibraryDeclaration *get_library_declaration() = 0;
  //@}

};
#endif
