


#include "can_read.hpp"
#include "can_data.hpp"
#include "datentypen.hpp"
#include <stdint.h>

void *can_read(void* val){
  
	can_struct *help=(can_struct *) val;
	can_frame *help_can_frame = help->my_can_frame;
	can_data *help_can_data = help->my_can_data;
  
	//Endlosschleife, die prüft ob neue Daten am CAN-BUS anliegen
	while(1){ 
    
    
   	 	help_can_data->read_canframe(help_can_frame);
    // int bytes_read = help_can_data->read( s, &help_can_frame->frame, sizeof(help_can_frame->frame) );
    //printf("Data: %x %x %x %x %x\n", help_can_frame->can_id, help_can_frame->data[0],help_can_frame->data[1], help_can_frame->data[2], help_can_frame->data[3]);
    	uint32_t data = 0;

		for(int i = 0; i<4; ++i)
			data |= (((uint32_t)help_can_frame->data[i])<<(24-i*8));
		
		// Switch device
		switch(help_can_frame->can_id)
		{
			case 0x7f1:
				switch(data & 0xffff0000)
				{
					case 0x36020000:
					{
						int8_t turnCount = 0;
						if(help_can_frame->data[2] >= 0x80) turnCount =-(~help_can_frame->data[2])+1;
						printf("Wheel turned %d times!\n", turnCount);
						break;
					}
					default:
						printf("Something happened: %d\n", data);
						break;
				}
				break;
			default:
				printf("UNSUPPORTED DEVICE SENT MSG\n");
				break;
		}
	}
  
}
