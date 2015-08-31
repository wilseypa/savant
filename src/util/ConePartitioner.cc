#ifdef PROCESS_COMBINATION

#include <iostream>
#include "IIR_ArchitectureDeclaration.hh"
#include "IIR_ConcurrentStatementList.hh"
#include "IIR_EntityDeclaration.hh"
#include "IIR_IndexedName.hh"
#include "IIR_IntegerLiteral.hh"
#include "IIR_Label.hh"
#include "IIR_ProcessStatement.hh"
#include "IIR_PortList.hh"
#include "IIR_SignalInterfaceDeclaration.hh"
#include "IIR_TextLiteral.hh"
#include "ProcessCombiner.hh"
#include "signal_set.hh"

extern int num_partitions;

struct bitarray {
  bitarray() { data = NULL; size = 0; }
  bitarray(const int size) {
    setsize(size);
  }
  void setsize(const int size) {
    this->size = size;
    int numbytes = ((int)(size / 8)) + 1;
    data = new unsigned char[numbytes];
    for (--numbytes ; numbytes >= 0; --numbytes) {
      data[numbytes] = '\0';
    }
  }
  bool readbit(const int idx) const {
    ASSERT(idx < size);
    int byte = idx / 8;
    int bit = idx % 8;
    unsigned char mask = (unsigned char)1 << bit;
    return ( data[byte] & mask );
  }
  void setbit(const int idx) {
    ASSERT(idx < size);
    int byte = idx / 8;
    int bit = idx % 8;
    unsigned char mask = (unsigned char)1 << bit;
    data[byte] |= mask;
  }
  // Return the number of bits that this and to_intersect have in common
  int affinity(const bitarray& to_intersect ) const {
    ASSERT(to_intersect.size == size);
    int i, retval = 0;
    char bi;
    for (i = 0; i < (((int)(size / 8)) + 1); ++i ) {
      bi = to_intersect.data[i] & data[i];
      retval += ((bi & 0x1) + ((bi & 0x2)>>1) + ((bi & 0x4)>>2) +
		 ((bi & 0x8)>>3) + ((bi & 0x10)>>4) + ((bi & 0x20)>>5) +
		 ((bi & 0x40)>>6) + ((bi & 0x80)>>7));
    }
    return retval;
  }
  ~bitarray() {
    delete [] data;
  }

private:
  unsigned char *data;
  unsigned int size;
};


struct io_data {
  signal_set<IIR_Declaration> insigs;
  signal_set<IIR_Declaration> outsigs;
  bool cone_built;
  bool in_a_cone;
  bitarray conearray;
  io_data() { 
    in_a_cone = false;
    cone_built = false;
  }
};


static signal_set<IIR_Declaration> primary_outputs;
static signal_set<IIR_Declaration> primary_inputs;

/* This function is called recursively to build the cone for the process
   in process_data at index coneidx.  As each process in the cone is
   determined, create_cone is called with that gate's index in startidx.
   Recursion is stopped when a primary_input is found, or when a loop in
   the process graph is detected. */
void
create_cone(io_data *process_data, const int numprocs, int startidx, 
	    int coneidx) {
  int i, j;
  IIR_Declaration *sig, *port;

  if ( process_data[coneidx].conearray.readbit( startidx ) == true ) {
    // If process startidx is already in my cone, I've been here before,
    // either directly or through incorporating another processes cone.
    // End the recursion.
    return;
  }

  // Put the start process in the cone
  process_data[coneidx].conearray.setbit( startidx );
  process_data[coneidx].cone_built = true;

  for ( sig = process_data[startidx].insigs.getElement();
	sig != NULL;
	sig = process_data[startidx].insigs.getNextElement() ) {
    for ( port = primary_inputs.getElement();
	  port != NULL;
	  port = primary_inputs.getNextElement()) {
      IIR_Declaration *localsig = sig, *localport = port;
      // for each sig, check to see if it's a primary input
      if ( sig->get_kind() == IIR_INDEXED_NAME ) {
	localsig = (IIR_Declaration*)((IIR_IndexedName*)sig)->get_prefix();
	ASSERT( localsig->get_kind() == IIR_SIGNAL_DECLARATION ||
		localsig->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION );
      }
      if ( port->get_kind() == IIR_INDEXED_NAME ) {
	localport = (IIR_Declaration*)((IIR_IndexedName*)port)->get_prefix();
	ASSERT( localport->get_kind() == IIR_SIGNAL_DECLARATION ||
		localport->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION );
      }
      if (! IIR_TextLiteral::_cmp( localsig->get_declarator(), 
				   localport->get_declarator())) {
	// move on to next signal if this is a primary input
	break;
      }
    }

    if ( port == NULL ) {
      // if sig is not a primary input, build its cone
      for ( i = 0; i < numprocs; ++i ) {
	if ( process_data[i].outsigs.intersects( sig )) {
	  // proc[i] is an input to proc[coneidx]
	  if ( process_data[i].cone_built == true ) {
	    // proc[i] already has its cone.  Don't recurse, and add
	    // proc[i]'s cone to proc[coneidx]'s cone
	    for ( j = 0; j < numprocs; ++j ) {
	      if ( process_data[i].conearray.readbit( j ) == true ) {
		process_data[coneidx].conearray.setbit( j );
	      }
	    }
	  }
	  else {
	    // proc[i] does not yet have its cone.
	    create_cone(process_data, numprocs, i, coneidx);
	  }
	} // end if proc[i] is an input to proc[coneidx]
      }
    } // end if not a primary input
  } // end for each sig in proc[coneidx]
}


void 
cone_partition( IIR_ArchitectureDeclaration *arch,
		IIR_ConcurrentStatementList& onewaitlist, 
		ProcessCombiner* cproc) {
  IIR_Declaration *decl;
  IIR_ProcessStatement *proc, *child;
  io_data *process_data;
  int i, j;
  const int numprocs = onewaitlist.size();
  bitarray *block_content_array;

  cerr << "Performing output-cone partitioning of "
       << numprocs << " processes of flattened architecture\n\""
       << *arch->get_declarator() << "\" into " << num_partitions 
       << " partitions.\n";

  // Allocate content arrays for each process and for each partition
  process_data = new io_data[numprocs];
  for ( i = 0; i < numprocs; ++i) {
    process_data[i].conearray.setsize(numprocs);
  }
  block_content_array = new bitarray[num_partitions];
  for (i = 0; i < num_partitions; ++i) {
    block_content_array[i].setsize(numprocs);
  }

  // builds sets of primary inputs and outputs
  IIR_PortList *port_clause = &arch->get_entity()->port_clause;
  if ( port_clause->size() == 0 ) {
    cerr << "Cone partitioning error: specified entity/architecture pair has no ports.\n";
    cerr << "Cannot determine primary inputs/outputs for cone partitioning.\n";
    cerr << "Giving up!  Bye...\n";
    exit (1);
  }
  IIR_SignalInterfaceDeclaration *port = port_clause->first();
  while (port != NULL) {
    switch ( port->get_mode() ) {
    case IIR_IN_MODE:
      primary_inputs.add(port);
      break;
    case IIR_INOUT_MODE: // intentional fallthrough
      primary_inputs.add(port);
    case IIR_OUT_MODE:
      primary_outputs.add(port);
      break;
    default:
      cerr << "ERROR: ConePartitioner: unexpected port mode "
	   << port->get_mode() << "\n";
    }
    port = port_clause->successor(port);
  }

  // Build cone arrays for each process
  i = 0;
  proc = (IIR_ProcessStatement*)onewaitlist.first();
  while ( proc != NULL ) {
    ASSERT ( proc->get_kind() == IIR_PROCESS_STATEMENT );
#ifdef DEBUG_CONE
    cerr << "Building cone for process " << *proc->get_label() << "\n";
#endif
    
    proc->_get_list_of_input_signals( &process_data[i].insigs );
    proc->_get_signal_source_info( &process_data[i].outsigs );

#ifdef DEBUG_CONE
    // Print out input signals for debugging
    decl = process_data[i].insigs.getElement();    
    cerr << "Input signal set:\n"; 
    while ( decl != NULL ) {
      if ( decl->get_kind() == IIR_INDEXED_NAME ) {
	ASSERT( ((IIR_IndexedName*)decl)->get_prefix()->get_kind() == IIR_SIGNAL_DECLARATION ||
		((IIR_IndexedName*)decl)->get_prefix()->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION );
	ASSERT( ((IIR_IndexedName*)decl)->get_suffix()->get_kind() == IIR_INTEGER_LITERAL);
	
	cerr << "\t" << *((IIR_IndexedName*)decl)->get_prefix();
	cerr << "(" << *((IIR_IndexedName*)decl)->get_suffix() << ") ";
	cerr << " (an " << decl->get_kind_text() << ") " <<
	  ((IIR_IntegerLiteral*)((IIR_IndexedName*)decl)->get_suffix())->_get_value();
      }
      else {
	cerr << "\t" << *decl->get_declarator();
      }

      cerr << "\n";
      decl = process_data[i].insigs.getNextElement();
    }
    
    // Print out output signals for debugging
    decl = process_data[i].outsigs.getElement();
    cerr << "Output signal set:\n"; 
    while ( decl != NULL ) {
      cerr << "\t" << *decl->get_declarator();
      if ( decl->get_kind() == IIR_INDEXED_NAME ) {
	ASSERT( ((IIR_IndexedName*)decl)->get_prefix()->get_kind() == IIR_SIGNAL_DECLARATION ||
		((IIR_IndexedName*)decl)->get_prefix()->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION );
	ASSERT( ((IIR_IndexedName*)decl)->get_suffix()->get_kind() == IIR_INTEGER_LITERAL);
	cerr << "(" << *((IIR_IndexedName*)decl)->get_suffix() << ") ";
	cerr << " (a " << decl->get_kind_text() << ") " << 
	  ((IIR_IntegerLiteral*)((IIR_IndexedName*)decl)->get_suffix())->_get_value();
      }
      cerr << "\n";
      decl = process_data[i].outsigs.getNextElement();
    }
#endif
    proc = (IIR_ProcessStatement*)onewaitlist.successor( proc );    
    i++;
  }

  // determine the cone arrays
  int procidx = 0;
  proc = (IIR_ProcessStatement*)onewaitlist.first();
  while ( proc != NULL ) {
    // For each input, recurse back, adding previous nodes to its conearray
    create_cone(process_data, numprocs, procidx, procidx);
#ifdef DEBUG_CONE
    cerr << "Cone for process " << procidx << ":";
    for ( int j = 0; j < numprocs; j++) {
      if (process_data[procidx].conearray.readbit(j)) {
	cerr << " " << j;
      }
    }
    cerr << "\n";
#endif
    proc = (IIR_ProcessStatement*)onewaitlist.successor( proc );
    procidx++;
  }

  // let's make up a max processes per partition
  int max = (int)(0.5 + 1.25 * (float)numprocs / (float)num_partitions);
  int partition = 0;
  // Assign primary input processes to partitions
  proc = (IIR_ProcessStatement*)onewaitlist.first();
  procidx = 0;
  while ( proc != NULL ) {
    IIR_Declaration *sig, *port;
    for (sig = process_data[procidx].insigs.getElement();
	 sig != NULL;
	 sig = process_data[procidx].insigs.getNextElement()) {
      for ( port = primary_inputs.getElement();
	    port != NULL;
	    port = primary_inputs.getNextElement()) {
	// for each sig, check to see if it's a primary input
	if ( sig->get_kind() == IIR_INDEXED_NAME ) {
	  sig = (IIR_Declaration*)((IIR_IndexedName*)sig)->get_prefix();
	  ASSERT( sig->get_kind() == IIR_SIGNAL_DECLARATION ||
		  sig->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION );
	}
	if ( port->get_kind() == IIR_INDEXED_NAME ) {
	  port = (IIR_Declaration*)((IIR_IndexedName*)port)->get_prefix();
	  ASSERT( port->get_kind() == IIR_SIGNAL_DECLARATION ||
	          port->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION );
	}
	if ( !IIR_TextLiteral::_cmp( sig->get_declarator(), 
				    port->get_declarator())) {
#ifdef DEBUG_CONE
	  cerr << "Assigning primary input process " << procidx 
	       << " into partition " << partition << "\n";
#endif

	  // found a primary input process
	  ASSERT (process_data[procidx].in_a_cone == false );
	  block_content_array[partition].setbit( procidx );
	  process_data[procidx].in_a_cone = true;
	  cproc[partition].combine( (IIR_ProcessStatement*)onewaitlist.get_nth_element( procidx ));
	  partition = (partition + 1) % num_partitions;
	  // I hate using a goto, but it's the cleanest way to exit out of
	  // two nested for loops
	  goto done_with_process;
	}   // end found a primary input
      }   // end for every port
    }   // end for every signal
  done_with_process:
    proc = (IIR_ProcessStatement*)onewaitlist.successor( proc );
    procidx++;
  }

  // Assign the rest of the processes to partitions
  proc = (IIR_ProcessStatement*)onewaitlist.first();
  procidx = 0;
  while ( proc != NULL ) {
    if ( !process_data[procidx].in_a_cone ) {
      int affinity[num_partitions];
#ifdef DEBUG_CONE
	cerr << "Process\tPartition\tPrtSize\tAffinity\n";
	cerr << "========================================\n";
#endif
      // calculate original process affinity for each partition
      for ( i = 0; i < num_partitions; ++i ) {
	affinity[i] = block_content_array[i].affinity(process_data[procidx].conearray);
#ifdef DEBUG_CONE
	cerr << procidx << "\t" << i << "\t\t" << cproc[i].size() 
	     << "\t" << affinity[i] << "\n";
#endif
      }

      // assign process to partition with highest affinity, if max not reached
      int bestaffinity = -1;
      bool done = false;
      while ( !done ) {
	for ( i = 0; i < num_partitions; ++i ) {
	  // determine best partition
	  if ( affinity[i] > bestaffinity ) {
	    bestaffinity = affinity[i];
	    partition = i;
	  }
	}
#ifdef DEBUG_CONE
	cerr << "Considering assigning process " << procidx 
	     << " to partition " << partition << "\n";
#endif
	if ( cproc[partition].size() >= max ) {
	  // partition is full, don't use it
	  affinity[partition] = -1;
	  bestaffinity = -1;
#ifdef DEBUG_CONE
	  cerr << "Oops, it's full.  ";
#endif
	}
	else {
#ifdef DEBUG_CONE
	  cerr << "Assigning process " << procidx << " to partition "
	       << partition << "\n";
#endif
	  // assign to partition
	  IIR_ProcessStatement *jproc;
	  jproc = (IIR_ProcessStatement*)onewaitlist.first();
	   for ( j = 0; j < numprocs; ++j) {
	    // if a process is in this process's cone, and not yet in the
	    // partition, combine it into the partition
	    if ( process_data[procidx].conearray.readbit( j ) == true &&
		 process_data[j].in_a_cone == false ) {
	      if ( cproc[partition].size() < max ) {
#ifdef DEBUG_CONE
		cerr << "\tConing in process " << j << "\n";
#endif
		block_content_array[partition].setbit( j );
		process_data[j].in_a_cone = true;
		cproc[partition].combine( jproc );
	      }
	      else {
#ifdef DEBUG_CONE
		cerr << "\tNot coning in process " << j
		     << " due to partition size\n";
#endif
	      }
	    }
	    jproc = (IIR_ProcessStatement*)onewaitlist.successor( jproc );

	  }
	  done = true;
	}
      }
    }

    proc = (IIR_ProcessStatement*)onewaitlist.successor( proc );
    procidx++;
  }

  for (i = 0; i < num_partitions ; ++i ) {
    cerr << "Cone partition " << i << " has " << cproc[i].size()
	 << " processes.\n";
  }
  delete [] process_data;
}
#endif
