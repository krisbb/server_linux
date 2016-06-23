#include"client_kit.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
// program przyjmuje kolejno IP i Port

int s_sock;

void sig_handler(int signum) // temporary solved
{
	send_message(s_sock, "1.0.9" , 5 );
	exit(0);
}

int main( int argc , char * argv[] )
{
	enum OPTION choice;
	int ret = -1;

	signal(SIGINT , sig_handler);
   //int s_sock;
   struct sockaddr_in serv;
   int Port = 9999;
   char * IP = "127.0.0.50";
   
   if(argc == 3)
   {
   IP = argv[1];
   Port = atoi(argv[2]);  
   }
   else if(argc == 2)IP = argv[1]; 
 
   char message[999];
	char tmp[999];

   s_sock = socket(AF_INET , SOCK_STREAM , 0 );
	if( s_sock < 0 )
	{
		perror(NULL);
		return -1;
	}

	memset(&serv , 0 , sizeof(serv));
   serv.sin_addr.s_addr = inet_addr(IP); // loopback
   serv.sin_family = AF_INET;
   serv.sin_port = htons( Port );

   if( connect(s_sock , (struct sockaddr*)&serv , sizeof(serv)) < 0 )
   {
      printf("Connection failed");
      return -1; 
   }

	//How to use client: 
   HowToUse();

	do
	{ 
		memset(message , 0 ,999 );

		printf("Please enter message: ");	
		fgets(message,999,stdin);
		
		strcpy(tmp, message); //strtok overriding pointer
		choice = firstparse(tmp);
		
		if( choice == NOTHING )
			continue;

		switch( choice )
		{

			case SHOW:
				ret = parse_show(message, s_sock);
				break;

			case SET:
				ret = parse_set(message, s_sock);
				break;

			case HELP:
				HowToUse();
				break;

			default:
				break;
		}

		if(ret == 0 )
			if(recv_message(s_sock))
				perror("Error Receive");

		ret = -1;
	}
	while( choice != EXIT );

	send_message( s_sock , "1.0.9" , 5 );
   close(s_sock);

	return 0;
}

