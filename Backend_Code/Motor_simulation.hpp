#ifndef Motor_simulation_hpp
#define Motor_simulation_hpp

#include <stdio.h>
#include <iostream>
#include "Car_status.hpp"
#include <fstream>
#include <string>
#include <stdlib.h>
class Motor_simulation
{
public:
  void calcRPM(int status);
  void calc(int gesch, int bremse); 
  int get_gas_ist(void);
  int get_bremse_ist(void);
  bool get_chagend(void);
  void set_chagend_fasle(void);
  void get_Temp(void);
  void decTank(void);
  
  Motor_simulation(Car_status *i) : fahrzeugstatus(i){
    
    count=0;
    level=300000;
    gas_ist=255;
    bremse_ist=255;
    gear =1;
    changed = false;
  }
  
private:
  
  Car_status *fahrzeugstatus;
  bool changed; 
  int count;
  int level;
  int gas_ist;
  int bremse_ist;
  float my_bremse;
  float my_gesch;
  double rpm;
  double kmh;
  int gear;
  unsigned int tank;
  unsigned int range;
  //Kraftfaktor pro Gang. Durch Berechnung festgelegt
  static const double kg1 = 0.2375;
  static const double kg2 = 0.475;
  static const double kg3 = 0.7125;
  static const double kg4 = 0.9375;
  static const double kg5 = 1.1625;
  static const double kg6 = 1.4;
  
  void calcKMH(double rpm);
  void Tankstatus();
  void Rangestatus();
  void Gearstickstatus(unsigned int gear);
  void writeMsg();
  
  std::ifstream datei;
  int temperatur;
  std::string text;
  
  
  
  
  
  
};



#endif /* Motor_simulation_hpp */
