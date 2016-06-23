#include "acceptor.h"
#include "client_handler.h"
#include "os.h"
#include "reactor.h"

//T
static void handle_event(event_handler* self, uint32_t event)//
{
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	os_memset(&client_addr, 0, sizeof(client_addr));
	
	client_fd = os_accept(self->fd, (struct sockaddr*) &client_addr,
&client_addr_len);

	if( client_fd == -1 )
		return;

	event_handler* ceh = create_client_eh(client_fd, self->r);

	if( ceh == NULL )
		return;

	self->r->add_event_handler(self->r, ceh);
}

event_handler* create_acceptor(int fd, reactor* r)//
{
	event_handler* eh = os_malloc(sizeof(event_handler));

	if( eh == NULL )
	{
		destroy_reactor(r);	
		return NULL;
	}

	eh->fd = fd;
	eh->r = r;
	eh->handle_event = &handle_event;

	return eh;
}
