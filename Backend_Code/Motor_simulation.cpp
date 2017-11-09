
#include "Motor_simulation.hpp"


///<summary>Berechnung der Drehzahl
///Drehzahl ist abhÃ¤ngig von Speed (Gas - Bremse)
///Aufruf der Klassen calkKMH(), Tankstatus(), Rangestatus(), writeMsg(),SendCAN()
///</summary>


void Motor_simulation::calc(int gas_soll, int bremse_soll) {
  
  
  if(bremse_soll < 255){ //Prüfen ob Bremse betätigt ist
    
    if(count > 300000){  //Zeitverzögerung, um den Geschwindigkeitszeiger zu glätten
      
      gas_ist = gas_ist + ((255-bremse_soll)/25); //Bestimmung des Verhältnisses von Gas un Bremse
      
      if(gas_ist>255) gas_ist =255;
      
      if(gas_soll == 255){
	level=300000;} //Reduzierung der Beschleunigung in Abhäningkeit der Geschwindigkeit
	else{
	  level = level - 700;
	}
	
	changed = true;
	count = 0;
    }
    count ++;
  }
  
  
  else
  {
    
    if(gas_soll < gas_ist){ //Wenn weniger Gas gegeben wird
      
      if(count > level){  
	
	gas_ist = gas_ist - 1;
	
	level = level + 1300;
	changed = true;
	
	count = 0;
	
      }
      count ++;
      
      
    }
    
    if(gas_soll > gas_ist){ //Wenn mehr Gas gegeben wird
      
      if(count > 300000){  //Zeitverzögerung, um den Geschwindigkeitszeiger zu glätten
	
	gas_ist = gas_ist + 1;
	
	if(gas_soll == 255){
	  level=300000;}
	  else{
	    level = level - 300;
	  }
	  
	  changed = true;
	  count = 0;
      }
      count ++;
    }
    
    
  }
  
  
  
  
  if( changed == true) //True wenn nuer Werte vorhanden
  {
    
    //  std::cout << gesch<< "     " << bremse << std::endl;
    my_gesch = (float)gas_ist;
    my_gesch = (my_gesch/-2.55)+50.0; //Peadlwert auf Wertebereich des Tachos anpassen
    
    int status = (int) (float) my_gesch + 50;
    if(status <=0)
      status = 0;
    
    // std::cout << "Status:  "<< status << " Gescch: " << my_gesch << " Bremse: " << my_bremse << std::endl;
    
    
    rpm = status * 0.8;
    fahrzeugstatus->setRPM((unsigned int)rpm);
    calcKMH(status);
    Rangestatus();
    get_Temp(); //Lesen der aktuellen CPU Temperatur
    
    
    
  }
  
  
}
void  Motor_simulation::get_Temp(void){ //Lesen der aktuellen CPU Temperatur
  
  
  datei.open("/sys/class/thermal/thermal_zone0/temp", std::ios::in);
  if ((datei.fail()))
  {
    std::cout << "Konnte datei nicht öffnen!" << std::endl;
    
  }
  else{
    
    /* Zeiger Position immer auf 0, wir haben nur eine Zeile zum lesen ... */
    datei.seekg (0, datei.beg);
    
    getline(datei, text);
    
    temperatur = atoi(text.c_str());
    
    temperatur = temperatur / 1000;
    
    datei.close();
    
    fahrzeugstatus->setTEMP(temperatur);
    
  }
  
  decTank();
}



void Motor_simulation::decTank(void){
  
  unsigned int test = fahrzeugstatus->getTANK();
  
  test = test -900000; //100000
  //std::cout << "Tank2 " <<  test << std::endl;
  fahrzeugstatus->setTANK(test) ;
}


void Motor_simulation::set_chagend_fasle(void){
  
  changed = false;
}

bool Motor_simulation::get_chagend(void)  {
  
  return changed;
  
}   


int Motor_simulation::get_gas_ist(void)  {
  
  return gas_ist;
  
}   

int Motor_simulation::get_bremse_ist(void){
  
  return bremse_ist;
}    


void Motor_simulation::calcRPM(int status) {
  
  rpm = status * 0.8;
  fahrzeugstatus->setRPM((unsigned int)rpm);
  calcKMH(rpm);
  Tankstatus();
  Rangestatus();
  //writeMsg();
}

void Motor_simulation::calcKMH(double status) {
  
  
  int help = status/7;
  int help2= ((int)status)%15;
  fahrzeugstatus->setKMH((unsigned int)status * 1.1);
  fahrzeugstatus->setRPM((unsigned int)(help2 * help * 0.5)+11);
  
  
}

/// <summary>
/// Setzen der TankfÃ¼llanzeige manuell
/// </summary>
void Motor_simulation::Tankstatus()
{
  tank = 159;
  fahrzeugstatus->setTANK((unsigned int)tank);
}
/// <summary>
/// Setzten der Reichweite manuell
/// </summary>
void Motor_simulation::Rangestatus()
{
  range = 50;
  fahrzeugstatus->setRANGE((unsigned int)range);
}
/// <summary>
/// Wird von der HFUDashboard Klasse genutzt um den Ã„nderung bei der Gangstellung an die die Car_status Klasse zu Ã¼bermitteln
/// </summary>
void Motor_simulation::Gearstickstatus(unsigned int gear) {
  fahrzeugstatus->setGEAR(gear);
}
/// <summary>
/// Ausgabe der aktuellen Werte um Ã„nderungen exakt in der Konsole abzulesen
/// </summary>
void Motor_simulation::writeMsg() {
  std::cout << "--------------------------" << std::endl;
  std::cout <<"KMH:   " << fahrzeugstatus->getKMH() << std::endl;
  std::cout <<"RPM:   " << fahrzeugstatus->getRPM() << std::endl;
  std::cout <<"TANK:   " << fahrzeugstatus->getTANK() << std::endl;
  std::cout <<"RANGE: " << fahrzeugstatus->getRANGE() << std::endl;
  std::cout <<"GEARSTATUS:  " << fahrzeugstatus->getGEAR() << std::endl;
  std::cout <<"GEAR: " << gear << std::endl;
}






