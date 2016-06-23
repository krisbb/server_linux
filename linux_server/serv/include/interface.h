#ifndef INTERFACE_H
#define INTERFACE_H

enum status{
	DOWN = 0,
	UP
};

// think about it //what if i change sth in interfaces ?
struct interface {

	char name[128]; //name is up to 1024 chars .. 
	char IPv4[16]; //15 chars + \0
	char IPv6[40]; // 8 hex digits + 7 dots + \0
	char Mac[18]; // 17 + \0
	char Netmask[16]; // the same as IPv4
	enum status Status; // int 0 || 1 
	struct interface * next;
};

char * get_available_interfaces();
char * get_all_interfaces();
char * get_interface(char * name , int flags);
char * set_MAC( char * name , char * MAC );
char * set_IP_MASK(char * name , char * IP , char * MASK);

#endif
