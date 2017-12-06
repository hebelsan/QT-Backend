#ifndef MAIN_HPP
#define MAIN_HPP

#include "model.hpp"
#include "control.hpp"
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "lenkrad.hpp"

#include "can_data.hpp"
#include "can_read.hpp"
#include "datentypen.hpp"


int main ( int argc,const char* argv[]){
  
	int my_fail; //Um Fehler bei starten der Thread abzufangen 
  
  
  
	//CAN
	can_data can_bus; //CAN Objekt anlegen
	int t = can_bus.open_can(); //CAN-Schnittstelle öffnen
	media_control_t my_media_control;
  
  
	//Lenkrad Struct
	l_daten *lenkrad_daten = new l_daten();
  
	//Control infos
	control_daten_intern control_daten;
	control_daten.media_control = &my_media_control;
  
	//Übergabedaten für can_read;
	struct can_frame frame_read;
	can_struct my_can_frame_data;
	my_can_frame_data.my_can_frame = &frame_read;
	my_can_frame_data.my_can_data = &can_bus;
	my_can_frame_data.my_media_control = &my_media_control;
  
	//Übergabedaten für Modelthread  
	model_struct my_model_struct;
	my_model_struct.my_l_daten = lenkrad_daten;
	my_model_struct.my_can_data = &can_bus;
	my_model_struct.my_can_frame = &frame_read;
	my_model_struct.my_control_daten = &control_daten;
  
  
	//Pthreads Objekte für jeden Thread anlegen
	pthread_t th_lenkrad_lesen, th_model, th_can_read, th_control;
  
	//Thread Lenkrad starten
	my_fail = pthread_create(&th_lenkrad_lesen, NULL, &lenkrad_lesen, (void*) lenkrad_daten);
	if (my_fail != 0)
		std::cout << "my_fail= " << my_fail << std::endl;

	//Thread Model starten
	my_fail = pthread_create(&th_model, NULL, &model, (void*) &my_model_struct);
	if (my_fail != 0)
		std::cout << "my_fail= " << my_fail << std::endl;
  
	// Eigener Thread zum lesen des CAN-Bus --> wird momentan nicht verwendet 
	my_fail = pthread_create(&th_can_read, NULL, &can_read, (void*) &my_can_frame_data);
	if (my_fail != 0)
		std::cout << "my_fail= " << my_fail << std::endl;
  
	//Thread Control starten
	my_fail = pthread_create(&th_control, NULL, &control, (void*) &control_daten);
	if (my_fail != 0)
		std::cout << "my_fail= " << my_fail << std::endl;
  
  
  
	std::cout << "main ende"<< std::endl;
  
  
	//Warten bis alle Threads fertig sind
	pthread_join(th_lenkrad_lesen,0);
	pthread_join(th_model,0);
	pthread_join(th_can_read,0);
	pthread_join(th_control,0);
  
}


#endif
