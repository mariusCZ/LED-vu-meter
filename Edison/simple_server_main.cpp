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

// Filter out bad data
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

int main ( int argc, char *argv[] )
{
  // Init the UART
  mraa_uart_context uart;
  uart = mraa_uart_init(0);
  mraa_uart_set_baudrate(uart, 115200);
  double volume;
  std::thread t[thread_num];
  std::cout << "running....\n";
  
  // Create the server
  try {
    // Create the socket
    ServerSocket server ( 30000 );

    while ( true )
      {
        ServerSocket new_sock;
        server.accept ( new_sock );
        try {
            // Main loop
            while ( true ) {
              std::string data;
              new_sock >> data;
              data += "\n";
              //strncpy(buf, data.c_str(), sizeof(buf));
              const char *buf = data.c_str();
              mraa_uart_write(uart, buf, strlen(buf));
            }
        }
  catch ( SocketException& ) {}
    }
  }  
  catch ( SocketException& e )
  {std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";}
  return 0;
}
