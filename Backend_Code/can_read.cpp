


#include "can_read.hpp"
#include "can_data.hpp"
#include "datentypen.hpp"


void *can_read(void* val){
  
  
  
  can_struct *help=(can_struct *) val;
  can_frame *help_can_frame = help->my_can_frame;
  can_data *help_can_data = help->my_can_data;
  
  
  
  //Endlosschleife, die prüft ob neue Daten am CAN-BUS anliegen
  while(1){ 
    
    
    help_can_data->read_canframe(help_can_frame);
    // int bytes_read = help_can_data->read( s, &help_can_frame->frame, sizeof(help_can_frame->frame) );
    //printf("Data: %x %x %x %x %x\n", help_can_frame->can_id, help_can_frame->data[0],help_can_frame->data[1], help_can_frame->data[2], help_can_frame->data[3]);
    
  }
  
}
