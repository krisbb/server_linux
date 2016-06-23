#include"s_echos.h" 
#include"protocol.h" // send_msg
#include"interface.h"
#include"os.h"

//T what with ret? 
int send_test_interface( int fd )//
{
	char * msg = "TEST SERVERA";
	return send_message(fd , msg , strlen(msg));
}

int send_available_interfaces( int fd )//
{	
	char * buffer;
	int ret;
	
	buffer = get_available_interfaces();	
	ret = send_message(fd ,buffer , strlen(buffer) );
	os_free(buffer);
	
	return ret;	
}

int send_all_interfaces( int fd )//
{
	char * buffer ;
	int ret;

	buffer = get_all_interfaces();	
   ret = send_message(fd ,buffer , strlen(buffer) );
	os_free(buffer);
	
	return ret;	
}

int send_interface( int fd , char * msg )//
{
	char * name, * strflag, * buffer;
	int flags ,ret;

	name = strtok(msg , ";");
	strflag = strtok(NULL , ";");
	flags = atoi(strflag);

	if( name == NULL )
		return send_message(fd , "Error interface name" , 20 );
 
	buffer = get_interface(name , flags);
   ret = send_message(fd ,buffer , strlen(buffer) );
	os_free(buffer);
	
	return ret;	
}

int set_interface_MAC(int fd, char * msg )//
{
	char * name , * MAC, * buffer;
		
	name = strtok( msg , ";");// " ;-\t\n"
	MAC = strtok( NULL , ";");

	if( name == NULL )
		return send_message(fd , "Error interface name" , 20 );

	buffer = set_MAC( name , MAC );

	return send_message(fd ,buffer ,strlen(buffer));	
}

int set_interface_IP_MASK(int fd, char * msg )//
{
	char * name , * IP , * MASK, * buffer;	
	name = strtok( msg , ";");
	IP = strtok( NULL , ";");
	MASK = strtok( NULL , ";");

	if( name == NULL )
		return send_message(fd , "Error interface name" , 20 );

	buffer = set_IP_MASK(name , IP , MASK);	

	return send_message(fd ,buffer ,strlen(buffer) );
}
