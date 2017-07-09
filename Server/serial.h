#include <termios.h>

struct termios tty;
int fd, speed, parity, mcount;

void openComm();

