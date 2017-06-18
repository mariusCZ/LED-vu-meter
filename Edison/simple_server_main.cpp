#include "mraa.hpp"
#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>

const int threshold = 5;
const int ledAmount = 10;
const int thread_num = 64;

typedef mraa::Gpio* gpioarray;

int getLeds(std::string data)
{
	unsigned char k;
	if (data.length() <= 2 && data.length() > 0) {
		k = std::stoi(data.c_str());
		//std::cout << data << std::endl;
	}
	if (k >= 0 && k <= 10)
		return k;
}

void flashy_flashy(gpioarray gpio[ledAmount], int k)
{
  for (int i = k; i < ledAmount; i++)
  {
	  gpio[i]->write(0);
	  //usleep(20000);
  }
  for (int i = 0; i < k; i++)
  {
	  gpio[i]->write(1);
	  //usleep(20000);
  }
}

int main ( int argc, char *argv[] )
{
  gpioarray gpio[ledAmount];
  for (int i = 4; i < ledAmount + 4; i++)
          gpio[i-4] = new mraa::Gpio(i);
  for (int i = 0; i < ledAmount; i++)
          gpio[i]->dir(mraa::DIR_OUT);
  double volume;
  std::thread t[thread_num];
  std::cout << "running....\n";

  try
    {
      // Create the socket
      ServerSocket server ( 30000 );

      while ( true )
        {

          ServerSocket new_sock;
          server.accept ( new_sock );

          try
            {
              while ( true )
                {
                  std::string data;
                  new_sock >> data;
		  int leds = getLeds(data);
		  if (leds >= 0 && leds <= 10) {
		  	std::cout << leds << std::endl;
		  	flashy_flashy(gpio, leds);
		  }
                }
            }
  catch ( SocketException& ) {}
	}
    }  
  catch ( SocketException& e )
  {std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";}
  return 0;
}
