
#ifndef VISITOR_RETURN_TYPE_HH
#define VISITOR_RETURN_TYPE_HH

// Copyright (c) 2000 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
// $Author: dnshirl $
// $Revision: 1.2 $

//---------------------------------------------------------------------------
// 
// $Id: visitor_return_type.hh,v 1.2 2008/06/24 19:21:46 dnshirl Exp $
// 
//---------------------------------------------------------------------------

#include "savant_config.hh"

/** This class defines the base type for return values of IIR visitors.
    Any visitor with a return value should build a class derived from this
    class for the return type.  
    @see node_visitor */
class visitor_return_type {

public: 

  /// Constructor.
  visitor_return_type() {};

  /** The destructor is pure virtual to define this as an abstract and to
      prevent direct instantiation.  */
  virtual ~visitor_return_type() = 0;

};

#endif
