#include "Car_status.hpp"



void Car_status::setKMH(unsigned int kmh){
  this->KMH = kmh;
  
}
void Car_status::setRPM(unsigned int rpm){
  this->RPM = rpm;
}
void Car_status::setTANK(unsigned int tank){
  this->TANK = tank;
}
void Car_status::setRANGE(unsigned int range){
  this->RANGE = range;
}
void Car_status::setGEAR(unsigned int gear){
  this->GEAR = gear;
}
void Car_status::setTEMP(unsigned int temp){
  this->TEMP = temp;
}

void Car_status::setTurnSignal(int turn){
  this->turnSignal = turn;
}

unsigned int Car_status::getKMH(){
  return KMH;
}
unsigned int Car_status::getRPM(){
  return RPM;
}
unsigned int Car_status::getTANK(){
  return TANK;
}
unsigned int Car_status::getRANGE(){
  return RANGE;
}
unsigned int Car_status::getGEAR(){
  return GEAR;
}
unsigned int Car_status::getTEMP(){
  return TEMP;
}
int Car_status::getTurnSignal(){
  return turnSignal;
}
