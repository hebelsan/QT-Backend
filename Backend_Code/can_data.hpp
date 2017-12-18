#ifndef CAN_DATA_HPP
#define CAN_DATA_HPP

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


class can_data {
  
private:
  
  
  int s; //CAN-Schnittstelle
  int nbytes;
  struct sockaddr_can addr;
  struct can_frame frame;
  struct ifreq ifr;
  
  
  
public:
  void send_canframe(struct can_frame);
  int open_can(void);
  void close_can(void);
  void read_canframe(can_frame*);
  
  
};

#endif
