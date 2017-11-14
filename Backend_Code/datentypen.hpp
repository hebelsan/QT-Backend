#ifndef DATENTYPEN_HPP
#define DATENTYPEN_HPP

#include "can_data.hpp"


struct l_daten_intern{ //Datentyp für Kommunikation zwischen Lenkradthread und Modelthread
  bool my_new;
  int type;
  int code;
  int val;
};

struct control_daten_intern{  //Datentyp für Kommunikation zwischen Modelthread und Controlthread
  bool my_new;
  int kmh;
  int rpm;
  unsigned int tank;
  int temp;
  int gear;
  bool x;
  bool y;
  bool b;
  bool a;
  bool rsb;
  bool rsb_top;
  bool lsb;
  bool lsb_top;
  bool up;
  bool down;
  bool right;
  bool left;
  bool gear_left;
  bool gear_right;
  bool xbox;
  media_control_t *media_control;
};

typedef struct l_daten_intern l_daten;
typedef struct control_daten_intern control_daten;


struct can_struct { // Datentyp für Kommunikation zwischen Mainthread und Modelthread. Übergabe der CAN-Schnittstelle 
  can_frame *my_can_frame; 
  can_data *my_can_data;
  media_control_t *my_media_control;
};



struct model_struct { //Wrapper für die die einzelen Datentypen
  l_daten *my_l_daten;
  can_data *my_can_data;
  can_frame *my_can_frame;
  control_daten_intern *my_control_daten;
};

enum steuerkreuz
{
	RECHTS = 0x3,
	LINKS = 0x7,
	HOCH = 0x1,
	RUNTER = 0x5,
	NEUTRAL = 0x0
};

typedef enum steuerkreuz steuerkreuz_t;

typedef struct media_control
{
	steuerkreuz_t wheel_direction;
	int8_t wheel_turns;
	bool wheel_pressed;
	bool menu_pressed;
	bool back_pressed;
	bool btn_right_pressed;
	bool btn_left_pressed;
} media_control_t;


#endif
