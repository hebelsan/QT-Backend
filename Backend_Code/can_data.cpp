
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "can_data.hpp"



//Sendemethode

void can_data::send_canframe(struct can_frame frame_tmp){

  nbytes = write(s, &frame_tmp, sizeof(frame_tmp)); //schreiben des can-frames auf den CAN-BUS
  //printf("Wrote %d bytes\n", nbytes); //Ausgeben, wieviel Bytes auf den CAN-BUS geschrieben wurden.
  //printf("Data: %x %x %x %x %x\n", frame_tmp.can_id, frame_tmp.data[0],frame_tmp.data[1], frame_tmp.data[2], frame_tmp.data[3]); //Ausgabe, der gesendeten daten (max. 5Byte, da ein Frame bei uns nie mehr hat)
  
} 



// Lesen wird im aktuellen Programm nicht genutzt, ist aber bereits implementiert.
// Dazu muss in Main.cpp der Kommentar entfernt werden
void can_data::read_canframe(can_frame* temp_frame){
  
  
  int bytes_read = read( s, temp_frame, sizeof(*temp_frame) ); //lesen der Daten des CAN-Bus
 
  
  
}


//Oeffnen der CAN-Schnittstelle
//hier wird immer can0 genutzt

int can_data::open_can(void){
  const char can_adresse[] = {"can0"}; 
  const char *ifname=can_adresse;
  
  
  if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) { 
    perror("Error while opening socket");
    return -1;
  }
  
  strcpy(ifr.ifr_name, ifname);
  ioctl(s, SIOCGIFINDEX, &ifr);
  
  addr.can_family  = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;
  
  //printf("%s at index %d\n", ifname, ifr.ifr_ifindex);
  
  if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Error in socket bind");
    return -2;
  }
  return 0;
  
} 

//Schließen der CAN-Schnittstelle
void can_data::close_can(void){ 
  
  close(s);
  
  
} 



