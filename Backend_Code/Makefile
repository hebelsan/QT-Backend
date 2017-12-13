# Definition/Declarations of MAKE-Variables
OBJ		= model.o lenkrad.o can_data.o can_read.o Car_status.o Motor_simulation.o control.o Mount.o Controller.o State.o UsbView.o StartView.o
LIBEVDEV	= /home/pi/libevdev/libevdev/libevdev.o
CC		= g++
RM		= rm -f
LIBDEF		= `pkg-config --cflags --libs gstreamer-1.0` -ludev
INCPATH		= -I /home/pi/libevdev/libevdev

# targets:
all: HFUDashboard_backend

HFUDashboard_backend: $(OBJ) GstPlayer.o
	$(CC) -o HFUDashboard_backend $(INCPATH) $(LIBEVDEV) $(OBJ) GstPlayer.o $(LIBDEF) main.cpp
	@echo Erfolg!
can_data.o: can_data.cpp can_data.hpp
	$(CC) -c can_data.cpp can_data.hpp
can_read.o: can_read.cpp
	$(CC) -c can_read.cpp can_read.hpp
Car_status.o: Car_status.cpp
	$(CC) -c Car_status.cpp
model.o: model.hpp model.cpp can_data.o
	$(CC) -c model.cpp model.hpp
lenkrad.o: lenkrad.hpp lenkrad.cpp
	$(CC) -c $(INCPATH) $(LIBEVDEV) lenkrad.hpp lenkrad.cpp $(LIBDEF)
GstPlayer.o: GstPlayer.hpp GstPlayer.cpp
	$(CC) -c $(LIBDEF) GstPlayer.hpp GstPlayer.cpp -std=gnu++11
State.o: State.hpp State.cpp GstPlayer.o
	$(CC) -c $(LIBDEF) State.hpp State.cpp -std=gnu++11
StartView.o: StartView.hpp StartView.cpp
	$(CC) -c $(LIBDEF) StartView.hpp StartView.cpp -std=gnu++11
UsbView.o: UsbView.hpp UsbView.cpp
	$(CC) -c $(LIBDEF) UsbView.hpp UsbView.cpp -std=gnu++11
control.o: control.hpp control.cpp
	$(CC) -c control.hpp $(LIBDEF) control.cpp -std=gnu++11
Controller.o: Controller.hpp Controller.cpp
	$(CC) -c $(LIBDEF) Controller.hpp Controller.cpp -std=gnu++11
Mount.o: Mount.hpp Mount.cpp Controller.cpp
	$(CC) -c $(LIBDEF) Mount.hpp Mount.cpp -std=gnu++11

.PHONY: clean
clean:
	$(RM) *.o HFUDashboard_backend *.gch
