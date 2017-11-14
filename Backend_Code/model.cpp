


#include "model.hpp"
#include "Car_status.hpp"
#include "Motor_simulation.hpp"


void *model(void* val){
  
  //globale Structs
  model_struct *help=(model_struct *) val;
  l_daten *help_l_daten = help->my_l_daten;
  can_data *help_can_data = help->my_can_data;
  can_frame *help_can_frame = help->my_can_frame;
  control_daten_intern *help_control_daten = help->my_control_daten;
  
  //Objekte anlegen
  Car_status *my_car_status = new Car_status(0,0,0,0,0);
  Motor_simulation *my_Motor_simulation = new Motor_simulation(my_car_status);
  
  //Attribute
  struct can_frame frame_send2;
  int checkCgui =1;
  int ccID =1;
  int checkWarning =1;
  int bremse_soll = 255;
  int bremse_ist;
  int gas_ist;
  int gas_soll =255;
  
  //Initialisierung des Controldatentyps
  help_control_daten->tank = 130;
  help_control_daten->rsb_top = false;
  help_control_daten->x = false;
  help_control_daten->y= false;
  help_control_daten->b= false;
  help_control_daten->a= false;
  help_control_daten->rsb= false;
  help_control_daten->rsb_top = false;
  help_control_daten->lsb= false;
  help_control_daten->lsb_top= false;
  help_control_daten->up= false;
  help_control_daten->down= false;
  help_control_daten->right= false;
  help_control_daten-> left= false;
  help_control_daten-> gear_left= false;
  help_control_daten-> gear_right= false;
  help_control_daten-> xbox= false;
  
  
  
  
  
  while(1){
    //Gedrückter Button wird ermittelt. Der dazugehörige Can Frame wird erstellt und verschickt.
    //Wenn nötig wird eine Mitteilung an den control Thread weitergegeben.
    
    
    if(help_l_daten->my_new==true){
      switch(help_l_daten->code){
	//Button A
	case(288):
	  if(help_l_daten->val == 1){
	    struct can_frame frame_send;
	    frame_send.can_id  = 0x7F0;
	    frame_send.can_dlc = 3;
	    frame_send.data[0] = 0x23;
	    frame_send.data[1] = 0x01;
	    frame_send.data[2] = 0xFF;
	    help_can_data->send_canframe(frame_send);
	    help_control_daten->a = true;
            help_control_daten->my_new = true;

	  }
	  break;
	  
	  //Button B Blinker rechts
	case(289):
	  if(help_l_daten->val == 1){
	    help_control_daten->b = true;
	    help_control_daten->my_new = true;
	  }
	  
	  
	  break;
	  
	  //Button X
	case(290):
	  if(help_l_daten->val == 1){
	    help_control_daten->x = true;
	    help_control_daten->my_new = true;
	  }
	  
	  
	  break;
	  
	  //Button Y
	case(291):
	  if(help_l_daten->val == 1){
	    struct can_frame frame_send; 
	    frame_send.can_id  = 0x7F0;
	    frame_send.can_dlc = 3;
	    frame_send.data[0] = 0x23;
	    frame_send.data[1] = 0x01;
	    frame_send.data[2] = 0x01;
	    help_can_data->send_canframe(frame_send);
	    help_control_daten->y = true;
            help_control_daten->my_new = true;

	  }
	  break;
	  
	  //Button LSB
	case(297):
	  if(help_l_daten->val == 1){
	    struct can_frame frame_send;  
	    if(checkCgui == 1){
	      
	      frame_send.can_id  = 0x7F0;
	      frame_send.can_dlc = 3;
	      frame_send.data[0] = 0x2A;
	      frame_send.data[1] = 0x00;
	      frame_send.data[2] = 0x01;
	      help_can_data->send_canframe(frame_send);
	      
	      checkCgui = 2; 
	      
	    }
	    
	    else if(checkCgui == 2){
	      
	      
	      frame_send.can_id  = 0x7F0;
	      frame_send.can_dlc = 3;
	      frame_send.data[0] = 0x2A;
	      frame_send.data[1] = 0x00;
	      frame_send.data[2] = 0x00;
	      help_can_data->send_canframe(frame_send);  
	      
	      checkCgui = 1; 
	      
	    }
	    
	  }  
	  break;
	  
	  //Button RSB
	case(296):
	  if(help_l_daten->val == 1){
	    struct can_frame frame_send;  
	    if(ccID == 1){
	      
	      frame_send.can_id  = 0x503;
	      frame_send.can_dlc = 1;
	      frame_send.data[0] = 0x01;
	      help_can_data->send_canframe(frame_send);
	      
	      ccID = 2; 
	      
	    }
	    
	    else if(ccID == 2){
	      
	      
	      frame_send.can_id  = 0x503;
	      frame_send.can_dlc = 1;
	      frame_send.data[0] = 0x00;
	      help_can_data->send_canframe(frame_send);
	      ccID = 1; 
	      
	    }
	    if(help_control_daten->tank <=0){
	      
	      help_control_daten->tank = 130;
	      my_car_status->setTANK(0xFFFFFFFF);
	      help_control_daten->my_new = true;
	    }
	    
	  }  
	  break;
	  
	  //Button LSB_TOP
	case(295):
	  if(help_l_daten->val == 1){
	    struct can_frame frame_send;
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x23;
	    frame_send.data[1] = 0x01;
	    help_can_data->send_canframe(frame_send);
	    
	    usleep(100000);
	    
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x23;
	    frame_send.data[1] = 0x00;
	    help_can_data->send_canframe(frame_send);  
	    
	  }	  
	  break;
	  
	  
	  //Button RSB_TOP
	case(294):
	  if(help_l_daten->val == 1){
	    struct can_frame frame_send;  
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x00;
	    frame_send.data[1] = 0x00;
	    help_can_data->send_canframe(frame_send);
	    
	    
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x07;
	    frame_send.data[1] = 0x01;
	    help_can_data->send_canframe(frame_send);  
	    
	    
	    help_control_daten->rsb_top = true;
	    help_control_daten->my_new = true;
	    
	    
	    
	    
	  }	  
	  break;
	  
	  //Button Xbox_Button
	case(298):
	  if(help_l_daten->val == 1){
	    struct can_frame frame_send;  
	    if(checkWarning == 1){
	      
	      frame_send.can_id  = 0x50A;
	      frame_send.can_dlc = 1;
	      frame_send.data[0] = 0xD3;
	      help_can_data->send_canframe(frame_send);
	      
	      checkWarning = 2; 
	      
	    }
	    
	    else if(checkWarning == 2){
	      
	      
	      frame_send.can_id  = 0x50A;
	      frame_send.can_dlc = 1;
	      frame_send.data[0] = 0x00;
	      help_can_data->send_canframe(frame_send);
	      
	      
	      checkWarning = 1; 
	      
	    }
	    help_control_daten->xbox = true;
	    help_control_daten->my_new = true;
	    
	  }  
	  break; 
	  
	  
	  //Button Steuerkrez_TOP_&_DOWN
	case(17):
	  //TOP
	  
	  if(help_l_daten->val == -1){
	    struct can_frame frame_send;
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x00;
	    frame_send.data[1] = 0x00;
	    help_can_data->send_canframe(frame_send);
	    
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x06;
	    frame_send.data[1] = 0x01;
	    help_can_data->send_canframe(frame_send);
	    
	    usleep(100000);
	    
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x00;
	    frame_send.data[1] = 0x00;
	    help_can_data->send_canframe(frame_send);
	    
	    help_control_daten->up = true;
	    help_control_daten->my_new = true;
	    
	  }
	  
	  //DOWN
	  if(help_l_daten->val == 1){
	    struct can_frame frame_send;
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x06;
	    frame_send.data[1] = 0x00;
	    help_can_data->send_canframe(frame_send); 
	    
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x06;
	    frame_send.data[1] = 0x0F;
	    help_can_data->send_canframe(frame_send);
	    
	    usleep(100000);
	    
	    frame_send.can_id  = 0x50F;
	    frame_send.can_dlc = 2;
	    frame_send.data[0] = 0x00;
	    frame_send.data[1] = 0x00;
	    help_can_data->send_canframe(frame_send); 
	    
	    help_control_daten->down = true;
	    help_control_daten->my_new = true;
	    
	  }
	  
	  break; 
	  
	  
	  //Button Steuerkrez_LEFT_RIGHT
	  case(16):
	    
	    //LEFT
	    if(help_l_daten->val == -1){
	      struct can_frame frame_send;
	      frame_send.can_id  = 0x50F;
	      frame_send.can_dlc = 2;
	      frame_send.data[0] = 0x03;
	      frame_send.data[1] = 0x00;
	      help_can_data->send_canframe(frame_send); 
	      
	      
	      frame_send.can_id  = 0x50F;
	      frame_send.can_dlc = 2;
	      frame_send.data[0] = 0x03;
	      frame_send.data[1] = 0x01;
	      help_can_data->send_canframe(frame_send);
	      
	      usleep(100000);
	      
	      
	      frame_send.can_id  = 0x50F;
	      frame_send.can_dlc = 2;
	      frame_send.data[0] = 0x00;
	      frame_send.data[1] = 0x00;
	      help_can_data->send_canframe(frame_send); 
	      
	      help_control_daten->left = true;
	      help_control_daten->my_new = true;
	      
	    }
	    
	    //RIGHT
	    if(help_l_daten->val == 1){
	      struct can_frame frame_send;
	      frame_send.can_id  = 0x50F;
	      frame_send.can_dlc = 2;
	      frame_send.data[0] = 0x02;
	      frame_send.data[1] = 0x00;
	      help_can_data->send_canframe(frame_send); 
	      
	      
	      frame_send.can_id  = 0x50F;
	      frame_send.can_dlc = 2;
	      frame_send.data[0] = 0x02;
	      frame_send.data[1] = 0x01;
	      help_can_data->send_canframe(frame_send);
	      
	      usleep(100000);
	      
	      frame_send.can_id  = 0x50F;
	      frame_send.can_dlc = 2;
	      frame_send.data[0] = 0x00;
	      frame_send.data[1] = 0x00;
	      help_can_data->send_canframe(frame_send);
	      
	      help_control_daten->right = true;
	      help_control_daten->my_new = true;
	      
	    }
	    
	    break; 
	    
	    case(1):
	      
	      gas_soll = help_l_daten->val;
	      break; 
	      
	      
	    case(2):
	      
	      
	      bremse_soll = help_l_daten->val;
	      break;
	      
	    case(292):
	      if(help_l_daten->val == 1){
		if(my_car_status->getGEAR()>= 11){
		}
		else{
		  my_car_status->setGEAR(my_car_status->getGEAR() + 1);
		}
		
		struct can_frame frame_send;
		frame_send.can_id  = 0x501;
		frame_send.can_dlc = 7;
		frame_send.data[0] = 0x00;
		frame_send.data[1] = (char) my_car_status->getKMH();
		frame_send.data[2] = 0x00;
		frame_send.data[3] = (char) my_car_status->getRPM();
		frame_send.data[4] = (char) my_car_status->getTANK();
		frame_send.data[5] = (char) my_car_status->getRANGE();
		frame_send.data[6] = (char) my_car_status->getGEAR();
		help_can_data->send_canframe(frame_send);
		help_control_daten->gear =  my_car_status->getGEAR();
		help_control_daten->my_new = true;
		
	      }
	      break;
	      
	    case(293):
	      if(help_l_daten->val == 1){
		if(my_car_status->getGEAR()<= 1){
		}
		else{
		  my_car_status->setGEAR(my_car_status->getGEAR() - 1);
		}
		
		struct can_frame frame_send;
		frame_send.can_id  = 0x501;
		frame_send.can_dlc = 7;
		frame_send.data[0] = 0x00;
		frame_send.data[1] = (char) my_car_status->getKMH();
		frame_send.data[2] = 0x00;
		frame_send.data[3] = (char) my_car_status->getRPM();
		frame_send.data[4] = (char) my_car_status->getTANK();
		frame_send.data[5] = (char) my_car_status->getRANGE();
		frame_send.data[6] = (char) my_car_status->getGEAR();
		help_can_data->send_canframe(frame_send); 
		help_control_daten->gear =  my_car_status->getGEAR();
		help_control_daten->my_new = true;
	      }
	      
	      break;
	      
      }
      
      help_l_daten->my_new=false;
      
      
    }
    if((gas_soll != my_Motor_simulation->get_gas_ist()) || (bremse_soll != my_Motor_simulation->get_bremse_ist()) ){
      
      my_Motor_simulation->calc(gas_soll ,bremse_soll); 
      
      if(my_Motor_simulation->get_chagend()){
	frame_send2.can_id  = 0x501;
	frame_send2.can_dlc = 7;
	frame_send2.data[0] = 0x00;
	frame_send2.data[1] = (char) my_car_status->getKMH();
	frame_send2.data[2] = 0x00;
	frame_send2.data[3] = (char) my_car_status->getRPM();
	frame_send2.data[4] = (char) my_car_status->getTANK();
	frame_send2.data[5] = (char) my_car_status->getRANGE();
	frame_send2.data[6] = (char) my_car_status->getGEAR();
	help_can_data->send_canframe(frame_send2);
	my_Motor_simulation->set_chagend_fasle();
	
	
	if(help_control_daten->tank >=1 ){
	  
	  help_control_daten->kmh = my_car_status->getKMH();
	  help_control_daten->rpm = my_car_status->getRPM();
	  help_control_daten->temp = my_car_status->getTEMP();
	  help_control_daten->tank = (my_car_status->getTANK()/33038210); //2^32 / 130
	  
	  
	  
	  
	}else{
	  
	  help_control_daten->kmh = 0;
	  help_control_daten->rpm =0;
	  
	}
	
	help_control_daten->my_new = true;
      }
      
    }
    
  }
}

