#ifndef S_ECHOS_H
#define S_ECHOS_H
#include "reactor.h"

int send_test_interface(int fd);

int send_available_interfaces( int fd );
int send_all_interfaces(int fd );
int send_interface( int fd , char * msg);

int set_interface_MAC(int fd, char * msg);
int set_interface_IP_MASK( int fd, char * msg);

#endif
