#include "client_handler.h"
#include "protocol.h"
#include "os.h"
#include "s_echos.h"

static void handle_message(event_handler* self, struct message* m)
{
	//int result = -1;
	//maybe result is useless? 
	//result from send_message .. 0 is sended -1 is error;
	// takes struct message and invoke foo depends on enum

	switch(m->z)
	{
		case TEST :
			printf("Test \n");
			send_test_interface(self->fd);
			break;
			
		case AVAILABLE_INTERFACES:
			printf("Av interfaces\n");
			send_available_interfaces(self->fd );
			break;
	
		case SHOW_ALL_INTERFACES:
			printf("All interfaces \n");
			send_all_interfaces(self->fd );
			break;
		
		case SHOW_INTERFACE:
			printf("Show interface\n");
			send_interface(self->fd, m->values);
			break;
		
		case SET_MAC:
			printf("SET MAC\n");
			set_interface_MAC(self->fd, m->values );
			break;
			
		case SET_IP_NETMASK:
			printf("SET IP NETMASK\n");
			set_interface_IP_MASK(self->fd, m->values );
			break;

		case REMOVE_CLIENT:
			printf("REMOVE CLIEN\n");
			self->r->remove_event_handler(self->r , self->fd);
			break;

		case ERROR:
			printf("Footype Error\n" );
			send_errormsg(self->fd , "Doesnt Recognize func" , 21 );
			break;

		default:
			printf("Undefined Protocol\n");
			send_errormsg(self->fd , "CRITIC ERROR" , 12);
			break;
	}

	//if( result <= 0 )
		//send_errormsg();
}

static void handle_client(event_handler* self, uint32_t event)//
{
	struct message* m = 0;
	
	if(event & EPOLLIN){
		//printf("I got msg ch \n");
		m = receive_message(self->fd);
		
		if(m){
			handle_message(self,m);
			delete_message(m);
		}

	}
}

event_handler* create_client_eh(int fd, reactor* r)//
{
	event_handler* eh = os_malloc(sizeof(event_handler));
	
	if(eh == NULL )
		return NULL;

	eh->fd = fd;
	eh->r = r;
	eh->handle_event = &handle_client;

	return eh;
}
