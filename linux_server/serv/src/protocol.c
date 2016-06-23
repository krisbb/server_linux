#include"protocol.h"
#include"os.h"

//T without send_errormsg ,, and default case .. 
int send_message( int fd , char * message, size_t len ) //
{
	char slen[9];
	snprintf(slen ,sizeof(slen),"0.0.%zu", len);

	if( os_write(fd, slen, sizeof(slen)) > 0 )
		if( os_write(fd, message , len ) > 0 ) 
			return 0;

	perror(NULL);
	return -1;
}

int recv_length(int fd)//
{
	int len, MSGLENGTHSIZE = sizeof(char) * 9;
	char slen[9];
	
	if(os_read(fd ,slen ,MSGLENGTHSIZE) < 1){
		perror(NULL);
		return 0;
	}

	len = slen[0] == '0' ? atoi(slen+4) : 0 ;

	return len;
}

struct message * receive_message(int fd)//
{
	int len = recv_length( fd );	

	char *msg = os_malloc( sizeof(char) * (len+1));
	
	if( msg == NULL )
		return NULL;

	if( os_read(fd ,msg ,len) < 1){
		 perror("error read");
		 os_free(msg);
		 return NULL;
	}
 
	msg[len] = '\0';// solved all problems

	if(strlen(msg) < 4 ) //if header doesnt appear 
	{
		os_free(msg);
		return NULL;
	}

	if( msg[0] != '1' || msg[2] == '1') //if header is wrong
	{
		os_free(msg);
		return NULL;	
	}

	struct message * m = os_malloc(sizeof(struct message));

	if(m == NULL ){
		 perror(NULL);
		 os_free(msg);
		 return NULL;
	}

	// 1.0.FOOTYPE.MSG
	switch(msg[4])
	{
		case '1':
		 m->y = ISNOTSET;
		 m->z = TEST;
		 m->values = 0;
		 break;

		case '2':
		 m->y = ISNOTSET;
		 m->z = AVAILABLE_INTERFACES;
		 m->values = 0;
		 break;

		case '3':
		 m->y = ISNOTSET;
		 m->z = SHOW_ALL_INTERFACES;
		 m->values = 0;
		 break;

		case '4':
		 m->y = ISNOTSET;
		 m->z = SHOW_INTERFACE;
		 m->values = os_malloc(strlen(msg + 6) * sizeof(char));
		 strcpy(m->values, msg + 6 );	
		 break;	

		case '5':
		 m->y = ISNOTSET;
		 m->z = SET_MAC;
		 m->values = os_malloc(strlen(msg + 6) * sizeof(char));
		 strcpy(m->values, msg + 6 );	
		 break;

		case '6':
		 m->y = ISNOTSET;
		 m->z = SET_IP_NETMASK;	 
		 m->values = os_malloc(strlen(msg + 6) * sizeof(char));
		 strcpy(m->values, msg + 6 );	
		 break;

		case '9':
		 m->y = ISNOTSET;
		 m->z = REMOVE_CLIENT;
		 m->values = 0 ;
		 break;

		default: // should be REMOVE CLIENT 
		 printf("doesnt recognize footype\n");
		 m->y = ISSET;
		 m->z = REMOVE_CLIENT;
		 //m->z = ERROR;
		 m->values = 0;
		break;
	}

   os_free(msg);	
	return m;		
}

void delete_message(struct message* m) //
{
	if(m->values != 0)
		os_free(m->values);

	os_free(m);
}

int send_errormsg( int fd , char * errormsg , size_t len ) //?
{
	char slen[9];
	snprintf(slen ,8,"0.1.%zu", len);

	// add 1.1.errormsg
	if( os_write(fd, slen, sizeof(char) * 9) > 0 )
		if( os_write(fd, errormsg , len ) > 0 ) 
			return 0;

	perror(NULL);
	return -1;
}
