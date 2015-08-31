
#ifndef IIR_DESIGN_FILE_HH
#define IIR_DESIGN_FILE_HH

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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR.hh"

// These are all instantiated, so they really need to be here.

class IIR_Identifier;
class IIR_CommentList;
class IIR_LibraryUnitList;
class IIR_LibraryDeclaration;
class StandardPackage;
class scram;

class IIR_DesignFile : public virtual IIR{

public:
  virtual ~IIR_DesignFile() {}
    
  // List accessor(s)
  virtual IIR_CommentList        *get_comments() = 0;
  virtual IIR_LibraryUnitList    *get_library_units() = 0;
  virtual void                   set_comments(IIR_CommentList *) = 0;
  virtual void                   set_library_units(IIR_LibraryUnitList *) = 0;

  virtual IIR_Identifier         *get_name() = 0;
  virtual void                   set_name( IIR_Identifier * ) = 0;

  virtual StandardPackage        *get_standard_package() = 0;
  virtual void                   set_standard_package(StandardPackage *) = 0;

  virtual plugin_class_factory   *get_class_factory() = 0;
  virtual void                   set_class_factory(plugin_class_factory *) = 0;

  virtual void                   set_parser( scram *new_parser ) = 0;

  /**
     Get the library declaration what was "work" when this file was analyzed.
  */
  virtual IIR_LibraryDeclaration *get_work_library() = 0;
};
#endif





