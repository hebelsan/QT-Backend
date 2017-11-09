
#include "lenkrad.hpp"




void* lenkrad_lesen (void *val){
  //Attribute
  struct libevdev *dev = NULL;
  int i=0;
  int fd, my_fail, rc;
  //zu testende devices
  std::string eventList[]={"/dev/input/event0", "/dev/input/event1", "/dev/input/event2", "/dev/input/event3", "/dev/input/event4", "/dev/input/event5"};
  bool abfrage=false;
  //void pointer in Struct zurückwandeln
  //Globales Struct mit dem die empfangenen Daten an Model übergeben werden.
  l_daten *lenkrad_daten=(l_daten *) val;
  
  
  do{
    std::cout << "Zu testendes device: "<< eventList[i].c_str() <<  std::endl; 
    // open the device in reading only mode. 
    //return a non-negative integer representing the lowest numbered unused file descriptor. negative = error
    fd = open(eventList[i].c_str(), O_RDONLY);
    std::cout << "FD(>=0): "<< fd << std::endl;
    if (fd >= 0) {
      //Initialize a new libevdev device from the given fd. 
      //fd  ->	A file descriptor to the device
      //dev ->	The newly initialized evdev device. 
      //On success, 0 is returned and dev is set to the newly allocated struct. On failure, a negative errno is returned and the value of dev is undefined.
      rc = libevdev_new_from_fd(fd, &dev);
      std::cout << "RC(>=0): "<< rc <<  std::endl;
      if (rc >= 0) {
	std::cout << "libevdev_get_uniq(dev): "<< libevdev_get_uniq(dev) <<  std::endl;
	//checks the unique identifier for the given device
	if(strcmp(libevdev_get_uniq(dev),"000098ec3c968394" )==0){
	  //if it matches set abfrage true
	  abfrage=true;
	  std::cout << "abfrage: "<< abfrage <<  std::endl;
	}
	else{
	  // if not match clean up and free the libevdev struct and try with another device
	  libevdev_free(dev);
	}
      }
    }
    ++i;
  }while(abfrage==false);
  
  do {
    //input struct anlegen
    struct input_event ev;
    //Get the next event from the device.
    rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL|LIBEVDEV_READ_FLAG_BLOCKING, &ev);
    
    if (rc == LIBEVDEV_READ_STATUS_SYNC) {
      printf("::::::::::::::::::::: dropped ::::::::::::::::::::::\n");
      while (rc == LIBEVDEV_READ_STATUS_SYNC) {
	//print_sync_event(&ev);
	rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_SYNC, &ev);
      }
      printf("::::::::::::::::::::: re-synced ::::::::::::::::::::::\n");
    } else if (rc == LIBEVDEV_READ_STATUS_SUCCESS){
      //print_event(&ev);
      //Daten in globales Struct schreiben
      if (ev.type == 1 || ev.type == 3){
	lenkrad_daten->type = ev.type;
	lenkrad_daten->code = ev.code;
	lenkrad_daten->val = ev.value;
	//Wenn die Daten aus dem globalen Struct noch nicht weiterverarbeitet wurden von Model wird zu langsam ausgegeben.
	if(lenkrad_daten->my_new==true)
	  std::cout << "zu langsam" << std::endl;
	else
	  lenkrad_daten->my_new=true;
      }
    }	
    
  } while (rc == LIBEVDEV_READ_STATUS_SYNC || rc == LIBEVDEV_READ_STATUS_SUCCESS || rc == -EAGAIN);
  
  if (rc != LIBEVDEV_READ_STATUS_SUCCESS && rc != -EAGAIN)
    fprintf(stderr, "Failed to handle events: %s\n", strerror(-rc));
}
