#include "control.hpp"
#include "Controller.hpp"
#include <string>


static void initLocals();
static void analyseMediaControl(media_control_t *, Controller *);
static bool isPlaying = false; 

// Lokaler Datenhalter
static media_control_t local_media_control;
static string local_mnt_point;

void *control (void* val){
	PipeControl* pout = PipeControl::getInstance();
	
	control_daten_intern *control_daten=(control_daten_intern *) val;
  
	bool my_new; //true, wenn sich daten geändert haben. Wird wieder auf falsegesetzt, wenn die neue Daten an die View übermittelt wurden.
	int kmh = control_daten->kmh; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	int rpm = control_daten->rpm; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	int gear = control_daten->gear; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	unsigned int tank = control_daten->tank; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	int temp = control_daten->temp; //Zwischenspeicherung, der zuletzt an View gesendeten Daten

	Controller *c = Controller::getInstance();

	initLocals();
	while(1){
    
    
		if(control_daten->my_new == true){ //Überprüfung, ob es im Model neue Daten gibt
      
		if(kmh != control_daten->kmh){ //Prüfen, ob sich die Geschwindigkeit geändet hat.
		std::cout << "? 0 " << control_daten->kmh*3 << std::endl; //Geschwindigkeitswert wird mit 3 multipliziert, da die Werte aus der Motorsimulation als Hexwerte für das Originaldisplay berechnet werden.
		kmh = control_daten->kmh;
	
		}
		if( rpm != control_daten->rpm){ //Prüfen, ob sich die Drehzahl geändet hat.
		std::cout << "? 1 " << control_daten->rpm*60 << std::endl; //Drehzahlswert wird mit 60 multipliziert, da die Werte aus der Motorsimulation als Hexwerte für das Originaldisplay berechnet werden.
		rpm = control_daten->rpm;
	
		}
		if(control_daten->x == true){ //Prüfen, ob Button "x" (Blinker linbks) betätig wurde.
			std::cout << "? 2 " << control_daten->x << std::endl;
			control_daten->x = false; //Button zuzücksetzen
		}
		if(control_daten->b == true){ //Prüfen, ob Button "b" (Blinker rechts) betätig wurde.
			std::cout << "? 3 " << control_daten->b << std::endl;
			control_daten->b = false; //Button zuzücksetzen
		}
		if(control_daten->up == true){ //Prüfen, ob Button "up" (Menu up) betätig wurde.
			//std::cout << "? 4 " << control_daten->up << std::endl;
			c->sendEvent(BUTTON_UP);
			control_daten->up = false; //Button zuzücksetzen
	
		}
		if(control_daten->down == true){ //Prüfen, ob Button "down" (Menu down) betätig wurde.
			//std::cout << "? 5 " << control_daten->down << std::endl;
			c->sendEvent(BUTTON_DOWN);
			control_daten->down = false; //Button zuzücksetzen
	
		}
		if(control_daten->right == true){ //Prüfen, ob Button "right" (left side up / Phonemenu) betätig wurde.
			//std::cout << "? 6 " << control_daten->right << std::endl;
			c->sendEvent(BUTTON_RIGHT);
			control_daten->right  = false; //Button zuzücksetzen
		}
      
		if(control_daten->left == true){ //Prüfen, ob Button "left" (left side down  / Phonemenu) betätig wurde.
			//std::cout << "? 7 " << control_daten->left << std::endl;
			c->sendEvent(BUTTON_RIGHT);
			control_daten->left = false; //Button zuzücksetzen	
		}
		if(gear != control_daten->gear){ //Prüfen, ob sich der Gang bzw. Fahrmodus geändet hat.
			std::cout << "? 8 " << control_daten->gear << std::endl;
			gear = control_daten->gear; //Button zuzücksetzen
		}
      
		if(temp != control_daten->temp)
		{ //Prüfen, ob sich die Temperatur geändet hat.
			std::cout << "? 9 " << control_daten->temp << std::endl;
			temp = control_daten->temp;
		}
		if(control_daten->xbox == true)
		{ //Prüfen, ob Button "xbox" (Fehlermeldungen) betätig wurde.
			std::cout << "? 10 " << control_daten->xbox << std::endl;
			control_daten->xbox = false;
		}

		if(control_daten->rsb_top == true)
		{ //Prüfen, ob Button "rsb_top" (Warnblinker) betätig wurde.
			//std::cout << "? 11 " << control_daten->rsb_top << std::endl;
			c->sendEvent(RSB_TOP);
			control_daten->rsb_top = false;
		}  
		if(tank != control_daten->tank){ //Prüfen, ob sich der Tankwert geändet hat.
			std::cout << "? 12 " << control_daten->tank << std::endl;
			tank = control_daten->tank;
		}
		if(control_daten->a == true)
		{ //Prüfen, ob Button "a" (Volume Down) Button betätig wurde.
			c->sendEvent(BUTTON_A);
			control_daten->a = false; //Button zuzücksetzen
		}
		if(control_daten->y == true){ //Prüfen, ob Button "y" (Volume Up) betätig wurde.
			c->sendEvent(BUTTON_Y);
			control_daten->y = false; //Button zuzücksetzen
		} 
		
		control_daten->my_new = false;
	
		} // endif my_new
		
		if(local_mnt_point != *(control_daten->my_mnt_point))
		{
			if(*(control_daten->my_mnt_point) != "") 
			{
				c->setMountpoint(*(control_daten->my_mnt_point));
				c->sendEvent(USB_PLUGGED_IN);
				local_mnt_point = *(control_daten->my_mnt_point);
			}
			else 
			{
				local_mnt_point = "";
				c->setMountpoint("");
				c->sendEvent(USB_PLUGGED_OUT);
				std::cout << "USB_PLUGGED_OUT" << std::endl;
			}
		}
		//std::cout << *control_daten->my_mnt_point << std::endl;
		analyseMediaControl(control_daten->media_control, c);
		PipeControl::getInstance()->popAll();
	}
}

static void initLocals()
{
	local_media_control.wheel_direction = NEUTRAL;
	local_media_control.wheel_turns = 0;
	local_media_control.wheel_pressed = false;
	local_media_control.menu_pressed = false;
	local_media_control.back_pressed = false;
	local_media_control.btn_right_pressed = false;
	local_media_control.btn_left_pressed = false;
	local_mnt_point = "";
}

static void analyseMediaControl(media_control_t *control_daten, Controller *c)
{
	if(control_daten->wheel_turns != 0)
	{
		//std::cout << "? 20 " << static_cast<int16_t>(control_daten->wheel_turns) << std::endl;
		if(control_daten->wheel_turns > 0)
			c->sendEvent(WHEEL_TURN_R);
		else c->sendEvent(WHEEL_TURN_L);
		control_daten->wheel_turns = 0;
	}
	if(control_daten->wheel_direction != local_media_control.wheel_direction)
	{
		//std::cout << "? 21 " << control_daten->wheel_direction << std::endl;
		switch(control_daten->wheel_direction)
		{
			case RECHTS:
				c->sendEvent(WHEEL_DIR_R);
				break;
			case LINKS:
				c->sendEvent(WHEEL_DIR_L);
				break;
			case HOCH:
				c->sendEvent(WHEEL_DIR_U);
				break;
			case RUNTER:
				c->sendEvent(WHEEL_DIR_D);
				break;
			case NEUTRAL:
				c->sendEvent(WHEEL_DIR_N);
				break;
		}
		local_media_control.wheel_direction = control_daten->wheel_direction;
	}
	if(control_daten->wheel_pressed != local_media_control.wheel_pressed)
	{
		std::cout << "Rad gedrückt! " << control_daten->wheel_pressed << std::endl;
		if(!local_media_control.wheel_pressed) c->sendEvent(WHEEL_PRESSED);
		//std::cout << "? 22 " << control_daten->wheel_pressed << std::endl;
		local_media_control.wheel_pressed = control_daten->wheel_pressed;
	}
	if(control_daten->menu_pressed != local_media_control.menu_pressed)
	{
		std::cout << "? 23 " << control_daten->menu_pressed << std::endl;
		local_media_control.menu_pressed = control_daten->menu_pressed;
	}
	if(control_daten->back_pressed != local_media_control.back_pressed)
	{
		std::cout << "? 24 " << control_daten->back_pressed << std::endl;
		local_media_control.back_pressed = control_daten->back_pressed;
	}
	if(control_daten->btn_left_pressed != local_media_control.btn_left_pressed)
	{
		//std::cout << "? 25 " << control_daten->btn_left_pressed << std::endl;
		if(!local_media_control.btn_left_pressed) c->sendEvent(MM_BTN_R);
		local_media_control.btn_left_pressed = control_daten->btn_left_pressed;
	}
	if(control_daten->btn_right_pressed != local_media_control.btn_right_pressed)
	{
		//std::cout << "? 26 " << control_daten->btn_right_pressed << std::endl;
		if(!local_media_control.btn_right_pressed) c->sendEvent(MM_BTN_L);
		local_media_control.btn_right_pressed = control_daten->btn_right_pressed;
	}
}
