/* implementacje funkcji do prawidlowej komunikacji client-server */
#include "client_kit.h"
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#include <stdio.h>

int send_message( int s_fd , char * message, size_t len )
{
   //char * slen = malloc(sizeof(char) * 9);
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
void Displaymenu()
{
   return;
}

int GetDeviceInfo()
{
   
   return 1;
}

int SetDeviceParams()
{
   return 1;
}
