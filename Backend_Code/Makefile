# Definition/Declarations of MAKE-Variables
OBJ			= model.o lenkrad.o can_data.o can_read.o Car_status.o Motor_simulation.o control.o
LIBEVDEV	= /home/pi/libevdev/libevdev/libevdev.o
CC			= g++
RM			= rm -f
LIBDEF		= -lpthread
INCPATH		= -I /home/pi/libevdev/libevdev

# targets:
all: HFUDashboard_backend

HFUDashboard_backend: $(OBJ)
	$(CC) -o HFUDashboard_backend $(INCPATH) $(LIBEVDEV) $(OBJ) $(LIBDEF) main.cpp
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

.PHONY: clean
clean:
	$(RM) *.o HFUDashboard_backend *.gch
