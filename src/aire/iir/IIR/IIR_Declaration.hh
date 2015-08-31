
#ifndef IIR_DECLARATION_HH
#define IIR_DECLARATION_HH

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

class IIR_Name;
class IIR_TextLiteral;
namespace savant {
  template <class type> class set;
}

class IIR_Attribute;

class IIR_Declaration : public virtual IIR{

public:
  virtual ~IIR_Declaration() {};

  virtual void set_declarator( IIR_TextLiteral *identifier ) = 0;
  virtual IIR_TextLiteral *get_declarator() = 0;

  /** This enumeration defines all of the types of declarations.  The
      enumeration LAST_TYPE is so that we can get the number of elements in
      the enumeration easily.  This is needed in the symbol_table. */
  enum declaration_type { ERROR = 0, UNDEFINED, VARIABLE, SHARED_VARIABLE,
                          TYPE, SUBTYPE, SIGNAL, PROCEDURE, INTERFACE, 
                          FUNCTION, S_FILE, ENTITY, CONSTANT, CONFIGURATION,
                          COMPONENT, ATTRIBUTE, ALIAS, ARCHITECTURE, 
                          PACKAGE_DT, PACKAGE_BODY, INTERFACE_VARIABLE,
                          INTERFACE_SIGNAL, INTERFACE_CONSTANT, 
                          INTERFACE_FILE, LABEL, LITERAL, UNITS, GROUP, 
                          GROUP_TEMPLATE, LIBRARY, ELEMENT, TERMINAL, 
                          INTERFACE_TERMINAL, NATURE, SUBNATURE, QUANTITY, 
                          LAST_DECLARATION_TYPE 
			};

  virtual declaration_type get_declaration_type() = 0;

  virtual IIR_Boolean is_element() = 0;

  /** These methods are referring to the region that this declaration is
      IN. */
  virtual IIR *get_declarative_region() = 0;
  virtual void set_declarative_region( IIR * ) = 0;

  /** Sometimes implicit declarations need to be visible in the symbol table
      and sometimes they should.  deallocate( foo : some_access_type )
      should be visible.  foo'quiet will create "foo_quiet" which definitely
      shouldn't. */
  virtual IIR_Boolean is_visible() = 0;
  virtual void set_is_visible( IIR_Boolean new_flag ) = 0;

  /** An implicit declaration is one that exists, but doesn't appear in the
      source. The two basic cases that this occurs in are declarations that
      represent the values of attributes, and implicit operators that go
      with their types. */
  virtual void set_is_implicit( IIR_Boolean new_flag ) = 0;
  virtual IIR_Boolean is_implicit_declaration() = 0;

  virtual IIR_Boolean contains_body() = 0;

  virtual savant::set<IIR_Declaration> *find_declarations( IIR_Name * ) = 0;
  virtual savant::set<IIR_Declaration> *find_declarations( IIR_TextLiteral *) = 0;

  /** Since we can now have implicit declarations due to attributes, we
      need to be able to tell if THIS declaration is the result of an
      attribute. */
  virtual IIR_Attribute *get_attribute_name() = 0;
  virtual void set_attribute_name( IIR_Attribute * ) = 0;

  /**
     Does this declaration represent the work library in some way?
  */
  virtual bool is_work_library() = 0;
};
#endif
