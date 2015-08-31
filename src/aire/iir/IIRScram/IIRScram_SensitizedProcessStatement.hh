#ifndef IIRSCRAM_SENSITIZED_PROCESS_STATEMENT_HH
#define IIRSCRAM_SENSITIZED_PROCESS_STATEMENT_HH
// Copyright (c) 1996-2000 The University of Cincinnati.  
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
//          Malolan Chetlur     mal@ececs.uc.edu
//          Timothy J. McBrayer tmcbraye@ececs.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ececs.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRBase_SensitizedProcessStatement.hh"

class IIRScram_SensitizedProcessStatement : public virtual IIRScram_ProcessStatement,
					    public virtual IIRBase_SensitizedProcessStatement{
public:
  IIRScram_SensitizedProcessStatement();
  ~IIRScram_SensitizedProcessStatement();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  void _type_check();
  IIRScram *_resolve_signal_name( IIRScram * );

  // Wrappers for IIRBase functions
  IIRScram_DesignatorList *     _get_sensitivity_list();

protected:
private:
};
#endif
