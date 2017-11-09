#ifndef Car_status_hpp
#define Car_status_hpp

#include <stdio.h>


class Car_status
{
  
private:
  unsigned int KMH;
  unsigned int RPM;
  unsigned int TANK;
  unsigned int RANGE;
  unsigned int GEAR;
  unsigned int TEMP;
  int turnSignal;
  
  
  
public:
  Car_status (unsigned int kmh, unsigned int rpm, unsigned int tank, unsigned int range, unsigned int gear): KMH(kmh), RPM(rpm), TANK(tank),RANGE(range), GEAR(gear) {
    
    GEAR = 1; 
    TANK = 0xFFFFFFFF;
    
    //Hier handelt es sich um ein exklusives Attribut, dass im Objekt Car_status nicht verwendet wird aber in der CAN_class zum Einsatz kommt
    //Blinker sind beim Start des Demonstrators aus, daher 0
    turnSignal = 0;
  }
  void setKMH(unsigned int kmh);
  void setRPM(unsigned int rpm);
  void setTANK(unsigned int tank);
  void setRANGE(unsigned int range);
  void setGEAR(unsigned int gear);
  void setTEMP(unsigned int temp);
  void setTurnSignal(int turn);
  
  unsigned int getKMH();
  unsigned int getRPM();
  unsigned int getTANK();
  unsigned int getRANGE();
  unsigned int getGEAR();
  unsigned int getTEMP();
  int getTurnSignal();
  
  
};




#endif /* Car_status_hpp */
