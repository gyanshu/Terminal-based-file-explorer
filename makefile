CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = skeleton.h screensize.h input.h printdir.h getdir.h command.h operate.h
OBJ = skeleton.o screensize.o input.o printdir.o getdir.o command.o operate.o driver.o
%.o: %.cpp $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

driver: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^
