#ifndef WRAPPER_CONTAINER_HH
#define WRAPPER_CONTAINER_HH

#include "savant_config.hh"
#include "list_object.hh"

class wrapper_container : public list_object {
public:
  wrapper_container(){}
  wrapper_container( void *new_data ){
    data_ptr = new_data;
  }
  
  ~wrapper_container(){}

  inline void *get_data(){
    return data_ptr;
  }

  inline void set_data( void *new_data ){
    data_ptr = new_data;
  }

  void *operator new( size_t my_size ){
    if( free_list == NULL ){
      return ::new wrapper_container;
    }
    else{
      wrapper_container *retval = free_list;

      free_list = (wrapper_container *)retval->get_next();
      return retval;
    }
  }

  void operator delete ( void *temp_delete, size_t ){
    wrapper_container *to_delete = (wrapper_container *)temp_delete;

    to_delete->set_next( free_list );
    free_list = to_delete;
  }
  
private:
  void *data_ptr;
  static wrapper_container *free_list;
};

#endif
