#ifndef CONSTRAINT_FUNCTOR_HH
#define CONSTRAINT_FUNCTOR_HH

// Copyright (c) 1996-1999 The University of Cincinnati.
// All rights reserved. 

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Author: Dale E. Martin          dmartin@cliftonlabs.com

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR.hh"

class constraint_functor {
public:
  virtual ~constraint_functor() { }

  virtual bool operator()( IIR *operate_on ) const = 0;

protected:
  constraint_functor(){}
};

class is_attribute_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_attribute_declaration();
  }
};

class is_array_type_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_array_type();
  }
};

class is_discrete_type_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_discrete_type();
  }
};

class is_character_type_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_character_type();
  }
};

class is_scalar_type_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_scalar_type();
  }
};

class is_integer_type_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_integer_type();
  }
};

class is_label_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_label();
  }
};

class is_component_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_component_declaration();
  }
};

class is_subprogram_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_subprogram();
  }
};

class is_type_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_type();
  }
};

class is_function_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_function_declaration();
  }
};

class is_signal_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_signal();
  }
};

class is_entity_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_entity_declaration();
  }
};

class is_architecture_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_architecture_declaration();
  }
};

class is_configuration_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_configuration_declaration();
  }
};

class is_procedure_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_procedure_declaration();
  }
};

class is_package_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_package_declaration();
  }
};

class is_subtype_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_subtype_declaration();
  }
};

class is_constant_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_constant();
  }
};

class is_variable_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_variable();
  }
};

class is_literal_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_literal();
  }
};

class is_file_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_file();
  }
};

class is_physical_unit_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_physical_unit();
  }
};

class is_group_declaration_functor : public constraint_functor {
  virtual bool operator()( IIR *operate_on ) const {
    return operate_on->is_group_declaration();
  }
};
#endif
