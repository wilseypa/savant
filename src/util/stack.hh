#ifndef STACK_HH
#define STACK_HH

#include "savant_config.hh"

template < class element >
class stack {

public:
  inline stack() {
    handle = NULL;
  }

  inline ~stack(){
    // walk down the list and destroy all of the containers
    while (handle!=NULL){
      last = handle;
      handle = handle->next;
      delete last;
    }
  }

  inline element *pop( );
  inline void push( element * );

  element *get_top_of_stack(){
    if( handle == NULL ){
      return NULL;
    }
    else{
      return (element *)handle->data;
    }
  };
  
private:
  struct container {
    ~container(){};
    void *data;
    container *next;
    container( void *new_data, container *next_ptr ) : data( new_data ), next( next_ptr ) {};
  };

  container *last;
  container *handle;
  static container *freeList;
};

template < class element >
element *stack< element >::pop() {
  if (handle==NULL){
    return NULL;
  }
  else {
    register container  *temp = handle;
    register element *returnData = (element *)temp->data;

    handle=temp->next;
    delete temp;
    return returnData;
  }
}

template < class element >
void stack< element >::push(element *new_element) {
  if (handle==NULL){
    register container  *temp;
    temp = new container( new_element, NULL ) ;
    handle = temp;
  }
  else {
    register container  *temp;
    temp = new container( new_element, handle ) ;
    handle = temp;
  }
}

#endif
