// main servera
#include"s_config.h"
#include"s_prep.h"
#include"reactor.h"
#include"acceptor.h"
#include"server.h"
#include<signal.h>

//T
int server(int argc, char * argv[] )
{
	//Default values
	int Port = 5555;
	int MaxClients = 100;
	
	//Read configuration file
	read_config_file("config.cfg", &Port, &MaxClients);
		
	// Socket server preparing
	int s_sock = -1;
	if(prepare_server_socket(&s_sock , &Port ))
		return -1;

	// Epoll instance preparing
	int epoll_sock = -1;
	if(prepare_epoll_instance(&epoll_sock, &s_sock, MaxClients))
		return -1;
	// initializing epoll_sock & serv_sock ended
  
	reactor * r = create_reactor(epoll_sock, MaxClients);

	if( r == NULL )
		return -1;
	
	//create acceptor -> eh to accept client connection
	event_handler* seh = create_acceptor(s_sock, r);

	if( seh == NULL)
		return -1;

	//first client is the server socket
	r->add_event_handler(r, seh);

	//run loop
	r->event_loop(r);
	//must end client_handler.c
   destroy_reactor(r);
	return 0;

}
