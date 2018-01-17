# Definition/Declarations of MAKE-Variables
OBJCNTRL	= StartView.o UsbView.o PhoneView.o CarCamView.o InfoView.o GstPlayer.o FileManager.o State.o Controller.o GlobalParams.o
OBJ			= model.o lenkrad.o can_data.o can_read.o Car_status.o Motor_simulation.o control.o Mount.o $(OBJCNTRL)
LIBEVDEV	= /home/pi/libevdev/libevdev/libevdev.o
CC			= g++ -g
RM			= rm -f
LIBDEF		= `pkg-config --cflags --libs gstreamer-1.0` -ludev
TAGLIB		= `pkg-config --cflags --libs taglib` -lz
INCPATH		= -I /home/pi/libevdev/libevdev

# targets:
all: HFUDashboard_backend

HFUDashboard_backend: $(OBJ) GstPlayer.o
	$(CC) -o HFUDashboard_backend $(INCPATH) $(LIBEVDEV) $(OBJ) $(LIBDEF) main.cpp $(TAGLIB)
	@echo HFUDashboard_backend erfolgreich gebaut!
TestController: TestController.cpp $(OBJCNTRL)
	$(CC) -o TestController TestController.cpp $(OBJCNTRL) $(LIBDEF) $(TAGLIB) -std=gnu++11
	@echo TestController erfolgreich gebaut!
can_data.o: can_data.cpp can_data.hpp
	$(CC) -c can_data.cpp can_data.hpp
can_read.o: can_read.cpp
	$(CC) -c can_read.cpp can_read.hpp
CarCamView.o: CarCamView.hpp CarCamView.cpp
	$(CC) -c $(LIBDEF) CarCamView.hpp CarCamView.cpp -std=gnu++11
Car_status.o: Car_status.cpp
	$(CC) -c Car_status.cpp
model.o: model.hpp model.cpp can_data.o
	$(CC) -c model.cpp model.hpp
lenkrad.o: lenkrad.hpp lenkrad.cpp
	$(CC) -c $(INCPATH) $(LIBEVDEV) lenkrad.hpp lenkrad.cpp $(LIBDEF)
FileManager.o: FileManager.hpp FileManager.cpp
	$(CC) -c $(LIBDEF) FileManager.hpp FileManager.cpp $(TAGLIB) -std=gnu++11
GlobalParams.o: GlobalParams.hpp GlobalParams.cpp
	$(CC) -c $(LIBDEF)  State.hpp GlobalParams.cpp -std=gnu++11
GstPlayer.o: GstPlayer.hpp GstPlayer.cpp
	$(CC) -c $(LIBDEF) GstPlayer.hpp GstPlayer.cpp -std=gnu++11
InfoView.o: InfoView.hpp InfoView.cpp
	$(CC) -c $(LIBDEF) InfoView.hpp InfoView.cpp -std=gnu++11
PhoneView.o: PhoneView.cpp PhoneView.hpp InfoView.o
	$(CC) -c $(LIBDEF) PhoneView.hpp PhoneView.cpp -std=gnu++11
State.o: State.hpp State.cpp GstPlayer.o
	$(CC) -c $(LIBDEF) State.hpp State.cpp -std=gnu++11
StartView.o: StartView.hpp StartView.cpp PhoneView.o CarCamView.o
	$(CC) -c $(LIBDEF) StartView.hpp StartView.cpp -std=gnu++11
UsbView.o: UsbView.hpp UsbView.cpp
	$(CC) -c $(LIBDEF) UsbView.hpp UsbView.cpp -std=gnu++11
control.o: control.hpp control.cpp
	$(CC) -c control.hpp $(LIBDEF) control.cpp -std=gnu++11
Controller.o: Controller.hpp Controller.cpp StartView.o UsbView.o
	$(CC) -c $(LIBDEF) Controller.hpp Controller.cpp -std=gnu++11
Mount.o: Mount.hpp Mount.cpp Controller.cpp
	$(CC) -c $(LIBDEF) Mount.hpp Mount.cpp -std=gnu++11

.PHONY: clean
clean:
	$(RM) *.o HFUDashboard_backend *.gch
