#ifndef __CLIENT_KIT_H
#define __CLIENT_KIT_H
#include<stdio.h>

enum OPTION {
	NOTHING = 0,
	SHOW,
	SET,
	HELP,
	EXIT
};

int send_message( int s_fd , char * message, size_t len );
int recv_message( int s_fd );
int recv_length(int s_fd);

enum OPTION firstparse( char * msg);
int parse_show(char * msg, int socket);
int parse_set(char * msg, int socket);
void HowToUse();

int show_av_interfaces(int socket);
int show_all_interfaces(int socket);
int show_interface(char * interface , char * opt , int socket );

int set_ip( char * str , int socket);
int set_mac( char * str , int socket);

#endif
