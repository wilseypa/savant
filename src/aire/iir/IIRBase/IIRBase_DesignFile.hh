
#ifndef IIRBASE_DESIGN_FILE_HH
#define IIRBASE_DESIGN_FILE_HH

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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase.hh"
#include "IIR_DesignFile.hh"

class IIR_Identifier;
class IIR_CommentList;
class IIR_LibraryUnitList;

class IIRBase_DesignFile : public virtual IIRBase, public virtual IIR_DesignFile{

public:
  // List Accessor(s)
  IIR_CommentList           *get_comments();
  IIR_LibraryUnitList       *get_library_units();
  void                      set_comments(IIR_CommentList *new_comments);
  void                      set_library_units(IIR_LibraryUnitList *new_library_units);

  IIR_Kind get_kind() const {return IIR_DESIGN_FILE;}
  const IIR_Char *get_kind_text() const {return "IIR_DesignFile";}

  IIR_Identifier *get_name();
  void set_name( IIR_Identifier * );

  IIR *convert_tree(plugin_class_factory *factory);

  StandardPackage               *get_standard_package();
  void                          set_standard_package(StandardPackage *);

  plugin_class_factory          *get_class_factory();
  void                          set_class_factory(plugin_class_factory *);

  void                          set_parser( scram *new_parser );
  IIR_LibraryDeclaration        *get_work_library();

  void publish_vhdl(ostream &);
protected:
  IIRBase_DesignFile();
  virtual ~IIRBase_DesignFile() = 0;
    
  StandardPackage               *my_std_package;
  plugin_class_factory          *my_factory;

  scram                         *my_parser;
private:
  // List Variable(s)
  IIR_CommentList               *comments;
  IIR_LibraryUnitList           *library_units;

  IIR_Identifier                *my_file_name;
};
#endif





