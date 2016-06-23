/* implementacje funkcji do prawidlowej komunikacji client-server */
#include "client_kit.h"
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int send_message( int s_fd , char * message, size_t len )
{
	char slen[9];
	snprintf(slen ,8,"0.0.%zu", len);

	printf("%i %s\n", strlen(slen), slen);
	if( write(s_fd, slen, sizeof(char) * 9) > 0 )
		if( write(s_fd, message , len ) > 0 ) 
			return 0;

	perror(NULL);
	return -1;
}

int recv_length(int s_fd)
{
	int len, MSGLENGTHSIZE = sizeof(char) * 9;
	char slen[9];

	if( read(s_fd, slen ,MSGLENGTHSIZE) < 1 )
	{
		perror(NULL);
		return 0;
	}

	if( slen[0] == '0' )
		len = atoi(slen+4);
	else
		len = 0;
	
	return len;
}

int recv_message( int s_fd )
{
	char * message = 0;
   int len;

	len = recv_length( s_fd);

	// Alocate exactly size = length of reading message
	message = malloc( len * sizeof(char));

		if( read(s_fd, message , len ) < 1 ) 
		{
			perror(NULL);
			free(message);
			return -1;
		}

	message[len] = '\0';
	printf("%s\n",message);

	free(message);
	return 0;
}

/* funkcje pozwalaja wyswietlic dane interfejsow i zmieniac ich parametry
 na maszynie dedykowanej */

enum OPTION firstparse( char * msg)
{
	char * str , * saveptr;
	
	str = strtok_r( msg , " ;-\n\t", &saveptr);

	if( str == NULL )
		return NOTHING;

	if( strncmp(str , "show" , 4) == 0 )
		return SHOW;
	else if( strncmp(str , "set" , 3) == 0 )
		return SET;
	else if( strncmp(str , "help" , 4) == 0 )
		return HELP;
	else if( strncmp(str , "exit" , 4) == 0 )
		return EXIT;

	//return NOCMD;
	return NOTHING;
}

int parse_show(char * msg , int socket)
{
	char * str,* saveptr;
	strtok_r(msg , " ;-\t\n" , &saveptr );
	
	str = strtok_r(NULL , " ;-\t\n", &saveptr);

	if( str == NULL )
		return -1;
	
	if( strncmp(str, "av" , 2 ) == 0 )
		return show_av_interfaces(socket);
	else if( strncmp(str , "all" , 3) == 0 )
		return show_all_interfaces(socket);
	else
		return show_interface(str,saveptr,socket);

}

int parse_set(char * msg , int socket)
{
	char * str, * saveptr;
	strtok_r(msg , " ;-", &saveptr );
	
	str = strtok_r(NULL , " ;-\t\n", &saveptr );
	
	if( str == NULL )
		return -1;
	
	if( strncmp(str, "ip" , 2) == 0 )
		return set_ip( saveptr,socket);
	else if( strncmp(str , "mac" , 3) == 0 )
		return set_mac( saveptr , socket);
 
		return -1;
}

void HowToUse()
{
	printf("How To Use: \n");
	printf("show av - show available interfaces\n");
	printf("show all - show all interfaces\n");
	printf("show <interface> [name | ip4 | ip6 | mac | status ]\n");
	printf("set mac <interface> <new_mac>\n");
	printf("set ip <interface> <ipv4> <netmask>\n");
}

int show_av_interfaces(int socket)
{
	return send_message( socket , "1.0.2" , 5 );
}

int show_all_interfaces(int socket)
{
	return send_message( socket , "1.0.3" , 5 );
}

int show_interface(char * interface , char * opt , int socket )
{
	char buffer[999] , * str;
	int flags = 0;
	
	memset( buffer , 0 , 999 );

	str = strtok( opt , " -;\t\n");
	
	while( str != NULL )
	{

		if( strncmp( str, "name" , 4 ) == 0 )
			flags |= 0x01;
		else if( strncmp( str, "ip4" , 3 ) == 0)
			flags |= 0x02;
		else if( strncmp( str, "ip6" , 3 ) == 0)
			flags |= 0x04;
		else if( strncmp( str, "mac" , 3 ) == 0)
			flags |= 0x08;
		else if( strncmp( str, "status" , 6 ) == 0)
			flags |= 0x10;
	
		str = strtok(NULL , " \t\n-;");
	}	

	if(flags == 0)
		flags = 31;

	sprintf( buffer , "%s%s;%i;" , "1.0.4;" , interface , flags);

	return send_message(socket , buffer , strlen(buffer));
}

int set_ip( char * str , int socket)
{
	char buffer[999];
	char * interface , * IP , * MASK;
	
	memset( buffer , 0 , 999 );

	interface = strtok( str , " -;\t\n");
	IP = strtok( NULL , " -;\t\n");
	MASK = strtok( NULL , " -;\t\n");

	sprintf( buffer , "%s%s;%s;%s;" , "1.0.6;" , interface , IP , MASK );

	return send_message(socket , buffer , strlen(buffer) );
}

int set_mac( char * str , int socket)
{

	char buffer[999];
	char * MAC, * interface;
	
	memset( buffer , 0 , 999 );
	
	interface = strtok( str , " -;\t\n");
	MAC = strtok( NULL , " -;\t\n");

	sprintf( buffer , "%s%s;%s;" , "1.0.5;" , interface , MAC );
	
	return send_message(socket , buffer , strlen(buffer) );
}

