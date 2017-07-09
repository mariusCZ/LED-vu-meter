#define PORT 3000
#define TRUE 1
#define FALSE 0

struct sockaddr_in address;
_Bool run = 0, loop = 0;

void* tcpServer();
