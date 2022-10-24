# Makefile for f2022, ecs36b
#

CC = g++ -std=c++14
CFLAGS = -g

LDFLAGS = 	-L/Users/sfwu/vcpkg/installed/arm64-osx/lib -ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

INC	=	ecs36b_Common.h
INC_CL	=	GPS.h Network.h JvTime.h Person.h Thing.h IOT_Thing.h Shadow_Thing.h
OBJ	=	GPS.o Network.o JvTime.o Person.o Thing.o IOT_Thing.o Shadow_Thing.o

# rules.
all: 	hw4server hw4client

#
#

hw4client.h:		ecs36b_hw4.json
	jsonrpcstub ecs36b_hw4.json --cpp-server=hw4Server --cpp-client=hw4Client

hw4server.h:		ecs36b_hw4.json
	jsonrpcstub ecs36b_hw4.json --cpp-server=hw4Server --cpp-client=hw4Client

hw4client.o:		hw4client.cpp $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw4client.cpp

hw4server.o:		hw4server.cpp $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw4server.cpp

GPS.o:		GPS.cpp GPS.h $(INC)
	$(CC) -c $(CFLAGS) GPS.cpp

Network.o:	Network.cpp Network.h $(INC)
	$(CC) -c $(CFLAGS) Network.cpp

JvTime.o:	JvTime.cpp JvTime.h $(INC)
	$(CC) -c $(CFLAGS) JvTime.cpp

Person.o:	Person.cpp Person.h $(INC)
	$(CC) -c $(CFLAGS) Person.cpp

Shadow_Thing.o:	Shadow_Thing.cpp Shadow_Thing.h $(INC) hw4client.h
	$(CC) -c $(CFLAGS) Shadow_Thing.cpp

Thing.o:	Thing.cpp Thing.h $(INC)
	$(CC) -c $(CFLAGS) Thing.cpp

IOT_Thing.o:	IOT_Thing.cpp IOT_Thing.h Network.h $(INC)
	$(CC) -c $(CFLAGS) IOT_Thing.cpp

hw4server:	Shadow_Thing.o hw4server.o $(OBJ)
	$(CC) -o hw4server hw4server.o $(OBJ) $(LDFLAGS)

hw4client:	Shadow_Thing.o hw4client.o $(OBJ)
	$(CC) -o hw4client hw4client.o $(OBJ) $(LDFLAGS)

clean:
	rm -f *.o *~ core hw4client.h hw4server.h hw4client hw4server

