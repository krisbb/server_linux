#include<stdio.h>

enum errorbit {
 ISNOTSET = 0,
 ISSET
};

enum footype {
	TEST = 1,
	AVAILABLE_INTERFACES,
	SHOW_ALL_INTERFACES,
	SHOW_INTERFACE,
	SET_MAC,
	SET_IP_NETMASK,
	ERROR,
	REMOVE_CLIENT = 9
};

struct message {
	enum errorbit y;
	enum footype z;
	char * values;
};

int send_test(int fd);
struct message * receive_message(int fd);
int recv_length(int fd);
int send_message( int fd , char * message, size_t len );
void delete_message(struct message* m);
int send_errormsg(int fd , char * errormsg , size_t len);
