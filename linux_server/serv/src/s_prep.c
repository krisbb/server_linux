#include "os.h"
#include "s_prep.h"

//check T
// validate this functions
int prepare_server_socket( int* serv_sock , int* port )
{
	// server socket preparing
	if( serv_sock == NULL )
			return -1;

	struct sockaddr_in s_addr;

	os_memset(&s_addr , 0 ,sizeof(struct sockaddr_in));

	*serv_sock = os_socket(AF_INET , SOCK_STREAM , 0 );

	if(*serv_sock < 0 )
   {
		printf("Create Socket Failed\n");
		return -1; 
	}

	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = os_htonl(INADDR_ANY);
	s_addr.sin_port = os_htons(*port);

if( os_bind(*serv_sock , (struct sockaddr*) &s_addr , sizeof(s_addr)) < 0 )
	{
		printf("Bind Socket Failed\n");
		os_close(*serv_sock);
		return -1;
	}		

	if( os_listen(*serv_sock, 1) < 0 )
	{
		printf("Listen on server socket failed\n");
		os_close(*serv_sock);
		return -1;
	}

 return 0;
}

int prepare_epoll_instance(int* epoll_sock ,int* serv_sock, int MaxClients )
{
	// epoll preparing
	struct epoll_event ev_epoll;

	os_memset(&ev_epoll, 0 , sizeof(struct epoll_event));

	*epoll_sock = os_epoll_create(MaxClients+1);

	if( *epoll_sock < 0 )
	{
		printf("Create epoll failed\n");
		os_close(*serv_sock);
		return -1;
	}	
	
	ev_epoll.events = EPOLLIN;
	ev_epoll.data.fd = *serv_sock;

	if( os_epoll_ctl(*epoll_sock, EPOLL_CTL_ADD, *serv_sock , &ev_epoll ) < 0 )
	{
		printf("Adding serv socket to epoll failed\n");
		os_close(*epoll_sock);
		os_close(*serv_sock);
		return -1;
	}	

 return 0;
}
